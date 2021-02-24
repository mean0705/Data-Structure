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

typedef struct studentType {
    char id[10];
    float weight;
    bool visit;
    int influence;
    vector<studentType> nextSuccessor;
} ; // sT

class Mission{

    public:

    vector<studentType> presuccessor;
    string fileNum;

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
             createAdjacencyList(fileName, fileNum);
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
      createAdjacencyList(fileName, fileNum);
      return stNo;
  } // Text2Binary

  void insertPresuccessor(char id[10]){
      studentType temptype;
      bool same = false;
      for(int i = 0; i<presuccessor.size(); i++){
          if ( strcmp( presuccessor[i].id, id ) == 0 ) same = true;
      }

      if (same == false) {
          strcpy( temptype.id, id );
          temptype.influence = 0;
          temptype.visit = false;
          temptype.weight = 0;
          temptype.nextSuccessor.clear();

          presuccessor.push_back(temptype);
      }
  }

  void insertSuccessor(char presuc[10], char suc[10], float weight){
      studentType temptype;
      for(int i = 0; i<presuccessor.size(); i++){
          if ( strcmp( presuccessor[i].id, presuc ) == 0 ){
              strcpy( temptype.id, suc );
              temptype.influence = 0;
              temptype.visit = false;
              temptype.weight = weight;

              presuccessor[i].nextSuccessor.push_back(temptype);
              break;
          }
      }
  }

  void Bubble_sort_successor( int num ){
      studentType temptype;
      int i, j;
      for (i = 0; i < presuccessor[num].nextSuccessor.size() - 1; i++) {
          for (j = 0; j < presuccessor[num].nextSuccessor.size() - 1 - i; j++){
              if (presuccessor[num].nextSuccessor[j].weight < presuccessor[num].nextSuccessor[j+1].weight){
                  swap( presuccessor[num].nextSuccessor[j], presuccessor[num].nextSuccessor[j+1] );
              }
          }
      }
  }

  void Bubble_sort_presuccessor(){
      studentType temptype;
      int i, j;
      for (i = 0; i < presuccessor.size() - 1; i++) {
          for (j = 0; j < presuccessor.size() - 1 - i; j++){
              if ( strcmp( presuccessor[j].id, presuccessor[j+1].id ) > 0 ){
                  swap( presuccessor[j], presuccessor[j+1] );
              }
          }
      }
  }

  void sortAdjacencyList(){
      for( int i = 0; i < presuccessor.size(); i++ )  Bubble_sort_successor( i );
      Bubble_sort_presuccessor();
  }

  void printAdjacencyList(string fileNum){
      ofstream tempout ;
      string fileName = "pairs" + fileNum + ".adj" ;
      tempout.open ( fileName ) ;

      for(int i = 0; i < presuccessor.size(); i++){
          tempout << "presuccessor" << i+1 << ":  " << presuccessor[i].id << "\t";
          tempout << "successor: ";
          for(int j = 0; j < presuccessor[i].nextSuccessor.size(); j++){
              tempout << presuccessor[i].nextSuccessor[j].id << "\t";
          }
          tempout << "\n";
      }
      tempout.close() ;
  }

  void createAdjacencyList(string fileName, string fileNum){
      fstream binFile;
      data oneSt;
      studentType temptype;
      int stNo = 0 ;

      binFile.open(fileName.c_str(), fstream::in | fstream::binary);
      if ( binFile.is_open() ){
          binFile.seekg(0, binFile.end);
          stNo = binFile.tellg() / sizeof(oneSt);
          binFile.seekg(0, binFile.beg);
          for (int i = 0; i < stNo; i++ ){
              binFile.read((char *)&oneSt, sizeof(oneSt));
              insertPresuccessor(oneSt.putId);
              insertPresuccessor(oneSt.getId);
              insertSuccessor(oneSt.putId, oneSt.getId ,oneSt.weight);
          } // for
      }
      sortAdjacencyList();
      printAdjacencyList(fileNum);
  }

  bool visited( char id[10] ){
      for( int i = 0; i < presuccessor.size() ; i++ ){
          if ( strcmp(id, presuccessor[i].id) == 0 && presuccessor[i].visit == true )return true;
      }
      return false;
  }

  int findWhichPresuccessor( string id ){
      for( int i = 0; i < presuccessor.size() ; i++ ){
          if ( id == presuccessor[i].id )  return i;
      }
  }

  void Bubble_sort_presuccessor_forInfluence(){
      studentType temptype;
      int i, j;
      for (i = 0; i < presuccessor.size() - 1; i++) {
          for (j = 0; j < presuccessor.size() - 1 - i; j++){
              if ( presuccessor[j].influence > presuccessor[j+1].influence ){
                  swap( presuccessor[j], presuccessor[j+1] );
              }
          }
      }
  }

  void printAdjacencyList_forInfluence(string fileNum){
      ofstream tempout ;
      string fileName = "pairs" + fileNum + ".cnt" ;
      tempout.open ( fileName ) ;

      for(int i = 0; i < presuccessor.size(); i++){
          tempout << "presuccessor" << i+1 << ":  " << presuccessor[i].id << "\t";
          tempout << "successor: ";
          for(int j = 0; j < presuccessor[i].nextSuccessor.size(); j++){
              tempout << presuccessor[i].nextSuccessor[j].id << "\t";
          }
          tempout << "\n";
      }
      tempout.close() ;
  }

  void BFS(){
      if ( presuccessor.empty() ) {
            cout << "excuse me, please complete mission1 first\n\n";
            return;
      }
      int influence = 0;
      for(int i = 0; i < presuccessor.size(); i++){
          vector<string> _queue;
          presuccessor[i].visit = true;
          _queue.push_back(presuccessor[i].id);
          while(!_queue.empty()){
              string temp;
              temp = _queue.front();
              int s = findWhichPresuccessor(temp);
              _queue.erase(_queue.begin());
              presuccessor[i].influence++;
              for(int j = 0; j < presuccessor[s].nextSuccessor.size() ; j++){
                  if (visited(presuccessor[s].nextSuccessor[j].id) == false){
                      _queue.push_back(presuccessor[s].nextSuccessor[j].id);
                      int h = findWhichPresuccessor(presuccessor[s].nextSuccessor[j].id);
                      presuccessor[h].visit = true;
                  }
              }
          }
          for(int x = 0; x < presuccessor.size(); x++) presuccessor[x].visit = false;

      }

      Bubble_sort_presuccessor_forInfluence();
      printAdjacencyList_forInfluence(fileNum);
      presuccessor.clear();
      fileNum = "\0";
  }

};

void PrintMenu(){
    cout << endl << "****        Adjacency List       *****";
    cout << endl << "* 0. QUIT                            *";
    cout << endl << "* 1. Make a Adjacency List           *";
    cout << endl << "* 2. Use influence to sort           *";
    cout << endl << "**************************************";
    cout << endl << "Input a choice(0, 1, 2): ";
} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission miss ;
    string fileName;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1) miss.Text2Binary(fileName,mission);
      else if ( mission == 2 ) miss.BFS();
      else if ( mission > 2 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      cin >> mission ;
    } // while end
}
