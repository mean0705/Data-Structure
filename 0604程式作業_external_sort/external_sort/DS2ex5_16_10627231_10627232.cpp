// 10627232 10627231 CodeBlocks 17.12

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
#include <list>


using namespace std;

typedef struct data {
    char putId[10];
    char getId[10];
    float weight;
} ; // data

typedef struct index {
    float weight;
    int offset;
} ;

static int clock_merge = 0, clock_internal = 0;
#define BLOCK_SIZE 200

class Mission{

    public:

    vector<data> read200, inputBuffer1, inputBuffer2, outputBuffer;
    vector<index> primary_index;
    string fileNum;
    fstream binFile;
    fstream outFile, tempFile1, tempFile2;

  int Text2Binary(string &fileName, int cd){
      fstream inFile;
      fstream outFile;
      int stNo = 0;

      do{
          cout << "Input a file number: ";
          cin >> fileNum;
          if (fileNum == "0")
            return false;
          inFile.open(("pairs" + fileNum + ".txt").c_str(), fstream::in);
          if (inFile.is_open())
            break;
          inFile.open(("pairs" + fileNum + ".bin").c_str(), fstream::in);
          if (inFile.is_open()){
             fileName = "pairs" + fileNum + ".bin";
             createExternal(fileName, fileNum);
             return true;
          }

      } while(true);
      cout << "here\n";
      fileName = "pairs" + fileNum + ".bin";
      outFile.open(fileName.c_str(), fstream::out | fstream::binary);
      if (outFile.is_open()){
          char rBuf[255];

          while(inFile.getline(rBuf, 255, '\n')){
              string temp;
              data oneSt;
              int cNo = 0, pre = 0, pos = 0;

              stNo++;
              temp.assign(rBuf);
              pos = temp.find_first_of('\t', pre);

              while (pos != string::npos){
                  switch (++cNo){
                      case 1: strcpy(oneSt.putId, temp.substr(pre, pos - pre).c_str());
                          break;
                      case 2: strcpy(oneSt.getId, temp.substr(pre, pos - pre).c_str());
                          break;
                      default: cout << "maybe have error\n";
                          break;
                  } // switch
                  pre = ++pos;
                  pos = temp.find_first_of('\t', pre);
              } // while

              pos = temp.find_last_of('\t');
              oneSt.weight = atof(temp.substr(pos+1).c_str());
              outFile.write((char *)&oneSt, sizeof(oneSt));
          } // while
          outFile.close();
      } // else
      inFile.close();
      createExternal(fileName, fileNum);
      return stNo;
  } // Text2Binary

  void createExternal(string fileName, string fileNum){
      data oneSt;
      int stNo = 0, count = 0, num = 0, blockNum = 0 ;
      string outName;
      clock_internal = clock();

      binFile.open(fileName.c_str(), fstream::in | fstream::binary);
      if ( binFile.is_open() ){
          binFile.seekg(0, binFile.end);
          stNo = binFile.tellg() / sizeof(oneSt);
          binFile.seekg(0, binFile.beg);

          if (stNo % BLOCK_SIZE == 0) blockNum = stNo / BLOCK_SIZE;
          else blockNum = stNo / BLOCK_SIZE + 1;

          for (int i = 0; i < stNo; i++ ){
              binFile.read((char *)&oneSt, sizeof(oneSt));
              count++;
              if (count == BLOCK_SIZE){
                  read200.push_back(oneSt);
                  count = 0;
                  Bubble_sort_read200();

                  outName = "sorted" + fileNum + "_" + to_string(blockNum) + "_" + to_string(num) + ".bin";
                  outFile.open(outName.c_str(), fstream::out | fstream::binary);
                  if (outFile.is_open()){
                      for(int i = 0; i < read200.size() ; i++) outFile.write((char *)&read200[i], sizeof(read200[i]));
                      read200.clear();
                      num++;
                      outFile.close();
                  }
                  else;
              }
              else{
                  read200.push_back(oneSt);
              }
          } // for

          if (!read200.empty()) {
              Bubble_sort_read200();
              outName = "sorted" + fileNum + "_" + to_string(blockNum) + "_" + to_string(num) + ".bin";
              outFile.open(outName.c_str(), fstream::out | fstream::binary);
              if (outFile.is_open()){
                  for(int i = 0; i < read200.size() ; i++) outFile.write((char *)&read200[i], sizeof(read200[i]));
                  read200.clear();
                  outFile.close();
              }
          }
      }
      binFile.close();
      outFile.close();
      clock_internal = clock() - clock_internal;

      cout << "The internal sort is completed. Check the initial sorted runs!" << endl << endl;
      clock_merge = clock();
      Merge(fileNum, blockNum, 1);
      //test(outName);
  }

  void Merge(string fileNum, int blockNum, int hhum){
      if (blockNum == 1) {
         clock_merge = clock() - clock_merge;
         print_Time();
         rename( ("sorted" + fileNum + "_1_0.bin").c_str(),  ("sorted" + fileNum + ".bin").c_str() );
         remove(("sorted" + fileNum + "_1_0.bin").c_str());
         createPrimaryIndex(fileNum);
         return;
      }
      int pastBlockNum = blockNum;
      blockNum = blockNum / 2 + blockNum%2 ;


      data temp1, temp2;
      int temp1No = 0, temp2No = 0;
      int num = -1, realNum = 0 ;
      while( num < pastBlockNum ){
          num++;
          string tempName1 = "sorted" + fileNum + "_" + to_string(pastBlockNum) + "_" + to_string(num) + ".bin";
          tempFile1.open(tempName1.c_str(), fstream::in | fstream::binary);
          if (tempFile1.is_open()){
              num++;
              string tempName2 = "sorted" + fileNum + "_" + to_string(pastBlockNum) + "_" + to_string(num) + ".bin";
              tempFile2.open(tempName2.c_str(), fstream::in | fstream::binary);
              if(tempFile2.is_open()){
                  string outName = "sorted" + fileNum + "_" + to_string(blockNum) + "_" + to_string(realNum) + ".bin";

                  realNum++;
                  outFile.open(outName.c_str(), fstream::out | fstream::binary);
                  int fnum = 0;
                  bool in1 = false, in2 = false;

                  if(outFile.is_open()){
                      while( tempFile1 || tempFile2 || !outputBuffer.empty() ){
                          if (tempFile1 && inputBuffer1.empty() && in1 == false ) {
                              cout << num << endl;
                              for(int i = 0 ; i < BLOCK_SIZE; i++) {
                                  if (!tempFile1) break;
                                  tempFile1.read((char *)&temp1, sizeof(temp1));
                                  inputBuffer1.push_back(temp1);
                             }
                          }
                          if (tempFile2 && inputBuffer2.empty() && in2 == false){
                              for(int i = 0 ; i < BLOCK_SIZE; i++) {
                                 if (!tempFile2) break;
                                 tempFile2.read((char *)&temp2, sizeof(temp2));
                                 inputBuffer2.push_back(temp2);
                              }
                          }
                          in1 = false;
                          in2 = false;

                          while(outputBuffer.size() < BLOCK_SIZE){
                              if ( inputBuffer1.empty() && tempFile1 ){
                                    in2 = true;
                                    break;
                              }
                              else if (inputBuffer2.empty() && tempFile2 ){
                                    in1 = true;
                                    break;
                              }
                              else if (inputBuffer1.empty() && !tempFile1){
                                  outputBuffer.push_back(inputBuffer2[0]);
                                  inputBuffer2.erase(inputBuffer2.begin());
                              }
                              else if (inputBuffer2.empty() && !tempFile2){
                                  outputBuffer.push_back(inputBuffer1[0]);
                                  inputBuffer1.erase(inputBuffer1.begin());
                              }
                              else if (inputBuffer1[0].weight >= inputBuffer2[0].weight){
                                  outputBuffer.push_back(inputBuffer1[0]);
                                  inputBuffer1.erase(inputBuffer1.begin());
                              }
                              else if (inputBuffer1[0].weight < inputBuffer2[0].weight){
                                  outputBuffer.push_back(inputBuffer2[0]);
                                  inputBuffer2.erase(inputBuffer2.begin());
                              }
                              else cout << "what??\n" ;
                          }

                          cout << num << " : " << outputBuffer.size() << endl;

                          if (outputBuffer.size() == BLOCK_SIZE){
                              for(int i = 0; i <outputBuffer.size(); i++){
                                  outFile.write((char *)&outputBuffer[i], sizeof(outputBuffer[i]));
                              }
                              outputBuffer.clear();
                          }


                      }

                      if (!outputBuffer.empty()){
                          cout << "end\n";
                          for(int i = 0; i <outputBuffer.size(); i++){
                                  outFile.write((char *)&outputBuffer[i], sizeof(outputBuffer[i]));
                          }
                      }
                      //inputBuffer1.clear();
                      //inputBuffer2.clear();

                      ////////////////////////////////////////////////////


                      /*tempFile1.read((char *)&temp1, sizeof(temp1));
                      tempFile2.read((char *)&temp2, sizeof(temp2));
                      while ( tempFile1 || tempFile2 ){
                          if(!tempFile1){
                              outFile.write((char *)&temp2, sizeof(temp2));
                              tempFile2.read((char *)&temp2, sizeof(temp2));
                          }
                          else if(!tempFile2){
                              outFile.write((char *)&temp1, sizeof(temp1));
                              tempFile1.read((char *)&temp1, sizeof(temp1));
                          }
                          else if(temp1.weight >= temp2.weight){
                              outFile.write((char *)&temp1, sizeof(temp1));
                              tempFile1.read((char *)&temp1, sizeof(temp1));
                          }
                          else{
                              outFile.write((char *)&temp2, sizeof(temp2));
                              tempFile2.read((char *)&temp2, sizeof(temp2));
                          }
                      }*/
                  } // if()
                  else ;

                  outputBuffer.clear();
                  tempFile1.close();
                  tempFile2.close();
                  outFile.close();
                  remove(tempName1.c_str());
                  remove(tempName2.c_str());
              }
              else{
                  string outName = "sorted" + fileNum + "_" + to_string(blockNum) + "_" + to_string(realNum) + ".bin";
                  outFile.open(outName.c_str(), fstream::out | fstream::binary);
                  if(outFile.is_open()){
                      for (int i = 0; tempFile1; i++ ){
                          tempFile1.read((char *)&temp1, sizeof(temp1));
                          outFile.write((char *)&temp1, sizeof(temp1));
                      }
                  }
                  else ;

                  tempFile1.close();
                  tempFile2.close();
                  outFile.close();
                  remove(tempName1.c_str());
                  remove(tempName2.c_str());
              }

          }
          else {
            break;
          }
      }
      cout << "Now there are " << blockNum <<" runs." << endl << endl;

      //system("PAUSE");
      hhum = hhum * 2;
      Merge(fileNum, blockNum, hhum);
  }

  void print_Time(){
      cout << "The execution time ..." << endl;
      cout << "Internal sort :" << (float)clock_internal * 1000 / CLOCKS_PER_SEC << " ms"  << endl;
      cout << "External sort :" << (float)clock_merge * 1000 / CLOCKS_PER_SEC << " ms"  << endl;
      cout << "Total Execution Time :" << (float)(clock_internal+ clock_merge) * 1000 / CLOCKS_PER_SEC << " ms"  << endl;
  }

  void createPrimaryIndex(string fileNum){
      system("PAUSE");
      data temp;
      index temp_index;
      int stNo = 0, count = 0, num = 2;
      float key;
      string fileName = "sorted" + fileNum + ".bin";
      binFile.open(fileName.c_str(), fstream::in | fstream::binary);
      if ( binFile.is_open() ){
          binFile.seekg(0, binFile.end);
          stNo = binFile.tellg() / sizeof(temp);
          binFile.seekg(0, binFile.beg);

          binFile.read((char *)&temp, sizeof(temp));
          key = temp.weight;
          cout << "[1] : (" << key << ", 0)" << endl;
          temp_index.weight = key;
          temp_index.offset = count;
          primary_index.push_back(temp_index);
          count++;
          for (int i = 1; i < stNo; i++ ){
              binFile.read((char *)&temp, sizeof(temp));
              if(temp.weight!=key) {
                    key = temp.weight;
                    temp_index.weight = key;
                    temp_index.offset = count;
                    primary_index.push_back(temp_index);
                    cout << "[" << num <<"] : (" << key << ", "<< count << ")" << endl;
                    num++;
              }
              count++;
          }
      }
      binFile.close();
      mission3();
      primary_index.clear();

  }

  void mission3(){

      float threshold ;
      data temp;
      cout << "\ninput a num as threshold :";
      cin >> threshold;
      cout << endl << endl;
      size_t i;
      for ( i = 0 ; i < primary_index.size() ; i++ ) if ( primary_index[i].weight < threshold ) break;

      int max = primary_index[i].offset ;
      string readname = "sorted" + fileNum + ".bin";
      fstream readfile( readname.c_str(), fstream::in | fstream::binary );

      cout << "threshold : " << threshold << endl;
      for ( int j = 0 ; j < max ; j++ ) {
        readfile.read( (char*)&temp, sizeof(temp) );
        cout << "[" << j << "] " << temp.getId << " " << temp.putId << " " << temp.weight << "\n";
      } // for

  }

  void test(string fileName){
      fstream binFile;
      data oneSt;
      int stNo = 0;
      binFile.open(fileName.c_str(), fstream::in | fstream::binary);
      if ( binFile.is_open() ){

          binFile.seekg(0, binFile.end);
          stNo = binFile.tellg() / sizeof(oneSt);
          binFile.seekg(0, binFile.beg);

          cout << stNo << endl;

          for (int i = 0; i < stNo; i++ ){
              binFile.read((char *)&oneSt, sizeof(oneSt));
              //cout << i+1 << ": " << oneSt.getId << " -> " << oneSt.putId << "  weight = " << oneSt.weight << endl;
          } // for
      }
      binFile.close();
  }

  void test2(){
         fstream out1( "out111.txt", fstream::out );
         fstream out2( "out222.txt", fstream::out );
         fstream in( "sorted501_95_95.bin", fstream::in | fstream::binary );
         in.seekg( 0, in.end );
         int stNO1 = in.tellg() / sizeof(data);
         in.seekg( 0, in.beg );

         for ( int i = 0 ; i < stNO1 ; i++ ) {
             data tmp;
             in.read( (char*)&tmp, sizeof(data) );
             out1 << tmp.putId << " " << tmp.getId << " " << tmp.weight<< endl;
         } // for

         in.close();
         cout << "\n\n\n";
         fstream in2( "sorted501_95_94.bin", fstream::in | fstream::binary );
         in2.seekg( 0, in2.end ); // find the end of file's address (file size)
         int stNO2 = in2.tellg() / sizeof(data); // count how many data
         in2.seekg( 0, in2.beg ); // change flag to begin
         for ( int i = 0 ; i < stNO2 ; i++ ) {
             data tmp;
             in2.read( (char*)&tmp, sizeof(tmp) );
             out2 << tmp.putId << " " << tmp.getId << " " << tmp.weight<< endl;
         } // for
         in2.close();
  }

  void Bubble_sort_read200(){
      int i, j;
      for (i = 0; i < read200.size() - 1; i++) {
          for (j = 0; j < read200.size() - 1 - i; j++){
              if ( read200[j].weight < read200[j+1].weight ){
                  swap( read200[j], read200[j+1] );
              }
          }
      }
  }

};

void PrintMenu(){
    cout << endl << "****              External Sort              *****";
    cout << endl << "* 0. QUIT                                        *";
    cout << endl << "* 1. Use External Sort and create primary index. *";
    cout << endl << "**************************************************";
    cout << endl << "Input a choice(0, 1): ";
} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission miss ;
    string fileName;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1) miss.Text2Binary(fileName,mission);
      //else if ( mission == 2 ) miss.BFS();
      else if ( mission > 1 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      cin >> mission ;
    } // while end
}
