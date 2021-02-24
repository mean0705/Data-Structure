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
 // clock_t, clock, CLOCKS_PER_SEC

using namespace std ;

typedef struct studentType {
  char sid[10];
  char sname[10];
  unsigned char score[6];
  float mean;
} ; // sT

typedef struct table {
  int id;
  char sid[10];
  char sname[10];
  float mean;
  int _hvalue;
} ; // store

static int gnum = 0 ;

class Mission{

  public:

  vector<table> linear, _double, quadratic;

  int Text2Binary(string &fileName, int cd){
      fstream inFile;
      fstream outFile;
      int stNo = 0;
      string fileNum;

      do{
          cout << "Input a file number: ";
          cin >> fileNum;
          if (fileNum == "0")
            return false;
          inFile.open(("input" + fileNum + ".txt").c_str(), fstream::in);
          if (inFile.is_open())
            break;
          inFile.open(("input" + fileNum + ".bin").c_str(), fstream::in);
          if (inFile.is_open()){
             fileName = "input" + fileNum + ".bin";
             if (cd==1)createLinear(fileName, fileNum);
             else if(cd==2)createDouble(fileName, fileNum);
             else if (cd==3)createQuadratic(fileName, fileNum);
             else;
             return true;
          }

      } while(true);
      fileName = "input" + fileNum + ".bin";
      outFile.open(fileName.c_str(), fstream::out | fstream::binary);
      if (outFile.is_open()){
          char rBuf[255];

          while(inFile.getline(rBuf, 255, '\n')){
              string temp;
              studentType oneSt;
              int cNo = 0, pre = 0, pos = 0;

              stNo++;
              temp.assign(rBuf);
              pos = temp.find_first_of('\t', pre);

              while (pos != string::npos){
                  switch (++cNo){
                      case 1: strcpy(oneSt.sid, temp.substr(pre, pos - pre).c_str());
                          break;
                      case 2: strcpy(oneSt.sname, temp.substr(pre, pos - pre).c_str());
                          break;
                      default: oneSt.score[cNo-3] = atoi(temp.substr(pre, pos - pre).c_str());
                          break;
                  } // switch
                  pre = ++pos;
                  pos = temp.find_first_of('\t', pre);
              } // while

              pos = temp.find_last_of('\t');
              oneSt.mean = atof(temp.substr(pos+1).c_str());
              outFile.write((char *)&oneSt, sizeof(oneSt));
          } // while
          outFile.close();
      } // else
      inFile.close();
      if(cd==1)createLinear(fileName, fileNum);
      else if (cd==2)createDouble(fileName, fileNum);
      else if (cd==3)createQuadratic(fileName, fileNum);
      else;
      return stNo;
  } // Text2Binary

  int prime( int num ){
    int b = num + 200;
    for(int x=num;x<=b;x++){
        for(int y=2;y<=x;y++){
            if      (x%y==0) break;
            else if (x==y+1) return x;
        } // for
    } // for
}

  void output_linear(string fileNum){
      ofstream linear_out;
      linear_out.open( "linear" + fileNum + ".txt");
      linear_out << " --- Hash Table X --- (linear probing)\n";
      for (int i = 0; i < linear.size(); i++){
          if (linear[i].mean == 0) {
                if ( i < 10 ) linear_out << "[  " << linear[i].id << "]\n";
                else if ( i >=10 && i <100 ) linear_out << "[ " << linear[i].id << "]\n";
                else  linear_out << "[" << linear[i].id << "]\n";
          }
          else{
              if ( i < 10 ) linear_out << "[  " << linear[i].id << "]\t" << linear[i]._hvalue << ",\t" ;
              else if ( i >=10 && i <100 ) linear_out << "[ " << linear[i].id << "]\t" << linear[i]._hvalue << ",\t" ;
              else  linear_out << "[" << linear[i].id << "]\t" << linear[i]._hvalue << ",\t" ;

              linear_out << linear[i].sid << ",\t" << linear[i].sname << ",\t" << linear[i].mean << endl;
          }
      }
      linear_out.close();
      linear.clear();
  }

  void output_double(string fileNum){
      ofstream double_out;
      double_out.open( "double" + fileNum + ".txt");
      double_out << " --- Hash Table Y --- (double hashing)\n";
      for (int i = 0; i < _double.size(); i++){
          if ( _double[i].mean == 0 ) {
                if ( i < 10 ) double_out << "[  " << _double[i].id << "]\n";
                else if ( i >=10 && i <100 ) double_out << "[ " << _double[i].id << "]\n";
                else double_out << "[" << _double[i].id << "]\n";
          }
          else{
             if ( i < 10 ) double_out << "[  " << _double[i].id << "]\t" << _double[i]._hvalue << ",\t" ;
             else if ( i >=10 && i <100 ) double_out << "[ " << _double[i].id << "]\t" << _double[i]._hvalue << ",\t" ;
             else double_out << "[" << _double[i].id << "]\t" << _double[i]._hvalue << ",\t" ;

             double_out << _double[i].sid << ",\t" << _double[i].sname << ",\t" << _double[i].mean << endl;
          }
      }
      double_out.close();
      _double.clear();
  }

  void output_quadratic(string fileNum){
      ofstream double_out;
      double_out.open( "quadratic" + fileNum + ".txt");
      double_out << " --- Hash Table Y --- (quadratic hashing)\n";
      for (int i = 0; i < quadratic.size(); i++){
          if ( quadratic[i].mean == 0 ) {
                if ( i < 10 ) double_out << "[  " << quadratic[i].id << "]\n";
                else if ( i >=10 && i <100 ) double_out << "[ " << quadratic[i].id << "]\n";
                else double_out << "[" << quadratic[i].id << "]\n";
          }
          else{
             if ( i < 10 ) double_out << "[  " << quadratic[i].id << "]\t" << quadratic[i]._hvalue << ",\t" ;
             else if ( i >=10 && i <100 ) double_out << "[ " << quadratic[i].id << "]\t" << quadratic[i]._hvalue << ",\t" ;
             else double_out << "[" << quadratic[i].id << "]\t" << quadratic[i]._hvalue << ",\t" ;

             double_out << quadratic[i].sid << ",\t" << quadratic[i].sname << ",\t" << quadratic[i].mean << endl;
          }
      }
      double_out.close();
      quadratic.clear();
  }

  void createLinear(string fileName, string fileNum){
      cout << "\nHash table X has been created\n";
      fstream binFile;
      studentType oneSt;
      int succes_search = 0, unsucces_search = 0;
      int stNo = 0, sizeOfHash = 0 ;

      binFile.open(fileName.c_str(), fstream::in | fstream::binary);
      if ( binFile.is_open() ){
          binFile.seekg(0, binFile.end);
          stNo = binFile.tellg() / sizeof(oneSt);
          binFile.seekg(0, binFile.beg);

          float temp_num1 = stNo*1.2;
          int num1 = int(temp_num1) + 1;
          sizeOfHash = prime(num1);

          for (int i = 0; i < sizeOfHash; i++){
              table temptype;
              temptype.id = i;
              strcpy( temptype.sid, " " );
              strcpy( temptype.sname, " " );
              temptype.mean = 0;
              temptype._hvalue = 0;

              linear.push_back(temptype);
          }

          //time_t start = clock();

          for (int i = 0; i < stNo; i++ ){
              binFile.read((char *)&oneSt, sizeof(oneSt));
              unsigned long long long_hvalue = 1;
              for (int j = 0; j < 8 ; j++){
                  if (oneSt.sid[j]=='\0')  break;
                  int x = oneSt.sid[j];
                  long_hvalue = long_hvalue * x;
              }
              int hvalue = long_hvalue % sizeOfHash;
              //cout << "[" << i+1 << "]" << oneSt.sid << ", " << oneSt.sname << endl;

              int x = hvalue ;
              while(1){
                  succes_search++;
                  if ( x > sizeOfHash - 1 ) {
                        x = 0 ;
                        succes_search--;
                  }
                  else if ( strcmp( linear.at(x).sid, " " ) == 0 ){
                      strcpy( linear.at(x).sid, oneSt.sid );
                      strcpy( linear.at(x).sname, oneSt.sname );
                      linear.at(x).mean = oneSt.mean;
                      linear.at(x)._hvalue = hvalue;
                      break;
                  }
                  else x++;
              }
          } // for

          //time_t end = clock();
          //cout << "linear time: " << float(end - start) << endl;
      }
      int mov = 0;



      for (int i = 0; i < sizeOfHash; i++){
          int k = i;
          while(1) {
            if ( k > sizeOfHash - 1 ) k = 0;
            else if ( strcmp( linear.at(k).sid, " " ) != 0 ) {
                unsucces_search++;
                if (i ==65) mov++;
                k++;
            }
            else break;
          } // for
      } // for

      float average_unsuccess = (float)unsucces_search / (float)sizeOfHash;
      printf( "unsuccessful search: %.4f comparisons on average\n", average_unsuccess );

      float average_success = (float)succes_search / (float)stNo;
      printf( "successful search: %.4f comparisons on average\n", average_success );
      output_linear(fileNum);
      binFile.close();
  }

  void createDouble(string fileName, string fileNum){
      cout << "\nHash table Y has been created\n";
      fstream binFile;
      studentType oneSt;
      bool dataInto = false;
      int succes_search = 0, unsucces_search = 0;
      int stNo = 0, sizeOfHash = 0, max_step = 0 ;

      binFile.open(fileName.c_str(), fstream::in | fstream::binary);
      if ( binFile.is_open() ){
          binFile.seekg(0, binFile.end);
          stNo = binFile.tellg() / sizeof(oneSt);
          binFile.seekg(0, binFile.beg);

          float temp_num1 = stNo*1.2, temp_num2 = stNo/3;
          int num1 = (int)temp_num1 + 1;
          int num2 = (int)temp_num2 + 1;
          max_step = prime(num2);
          sizeOfHash = prime(num1);

          for (int i = 0; i < sizeOfHash; i++){
              table temptype;
              temptype.id = i;
              strcpy( temptype.sid, " " );
              strcpy( temptype.sname, " " );
              temptype.mean = 0;
              temptype._hvalue = 0;

              _double.push_back(temptype);
          }

          for (int i = 0; i < stNo; i++ ){
              binFile.read((char *)&oneSt, sizeof(oneSt));
              unsigned long long long_hvalue = 1;
              for (int j = 0; j < 8 ; j++){
                  if (oneSt.sid[j]=='\0') break;
                  int x = oneSt.sid[j];
                  long_hvalue = long_hvalue * x;
              }
              int hvalue = long_hvalue % sizeOfHash;
              //cout << "[" << i+1 << "]" << oneSt.sid << ", " << oneSt.sname << ", " << hvalue << endl;

              int x = hvalue;
              int step = max_step - (long_hvalue % max_step);

              while(1){
                  succes_search++;
                  if ( x > sizeOfHash - 1 ) {
                        succes_search--;
                        x = x - sizeOfHash;
                  }
                  else if ( strcmp( _double.at(x).sid, " " ) == 0 ){
                      strcpy( _double.at(x).sid, oneSt.sid );
                      strcpy( _double.at(x).sname, oneSt.sname );
                      _double.at(x).mean = oneSt.mean;
                      _double.at(x)._hvalue = hvalue;
                      break;
                  }
                  else x = x + step;
              }
          } // for
      }

      float average_success = (float)succes_search / (float)stNo;
      printf( "successful search: %.4f comparisons on average\n", average_success );
      output_double(fileNum);
      binFile.close();
  }

  void createQuadratic(string fileName, string fileNum){
      cout << "\nHash table Z has been created\n";
      fstream binFile;
      studentType oneSt;
      int succes_search = 0, unsucces_search = 0;
      int stNo = 0, sizeOfHash = 0 ;

      binFile.open(fileName.c_str(), fstream::in | fstream::binary);
      if ( binFile.is_open() ){
          binFile.seekg(0, binFile.end);
          stNo = binFile.tellg() / sizeof(oneSt);
          binFile.seekg(0, binFile.beg);

          float temp_num1 = stNo*1.2;
          int num1 = int(temp_num1) + 1;
          sizeOfHash = prime(num1);

          for (int i = 0; i < sizeOfHash; i++){
              table temptype;
              temptype.id = i;
              strcpy( temptype.sid, " " );
              strcpy( temptype.sname, " " );
              temptype.mean = 0;
              temptype._hvalue = 0;

              quadratic.push_back(temptype);
          }

          for (int i = 0; i < stNo; i++ ){
              binFile.read((char *)&oneSt, sizeof(oneSt));
              unsigned long long long_hvalue = 1;
              for (int j = 0; j < 8 ; j++){
                  if (oneSt.sid[j]=='\0')  break;
                  int x = oneSt.sid[j];
                  long_hvalue = long_hvalue * x;
              }
              int hvalue = long_hvalue % sizeOfHash;
              //cout << "[" << i+1 << "]" << oneSt.sid << ", " << oneSt.sname << endl;

              int x = hvalue, tempx = hvalue ;
              int num = 1, step = 0;
              while(1){
                  succes_search++;
                  if ( x > sizeOfHash - 1 ) {
                        x = x % sizeOfHash;
                        succes_search--;
                  }
                  else if ( strcmp( quadratic.at(x).sid, " " ) == 0 ){
                      strcpy( quadratic.at(x).sid, oneSt.sid );
                      strcpy( quadratic.at(x).sname, oneSt.sname );
                      quadratic.at(x).mean = oneSt.mean;
                      quadratic.at(x)._hvalue = hvalue;
                      num = 1;
                      break;
                  }
                  else {
                      step = num * num;
                      x = tempx;
                      x = x + step;
                      num++;
                      if (num == 99999) {
                          cout << "Can not find:((\n";
                          break;
                      }
                  }
              }
          } // for
      }
      int mov = 0;

      int step = 0;
      int num = 1;
      for (int i = 0; i != sizeOfHash; i++){
          int k = i, tempk = i;
          while(1) {
            if ( k > sizeOfHash - 1 )  k = k % sizeOfHash;
            else if ( strcmp( quadratic.at(k).sid, " " ) != 0 ) {
                unsucces_search++;
                step = num*num;
                k = tempk;
                k = k + step;
                num++;
            }
            else {
                num = 1;
                break;
            }
          } // for
      } // for

      float average_unsuccess = (float)unsucces_search / (float)sizeOfHash;
      printf( "unsuccessful search: %.4f comparisons on average\n", average_unsuccess );

      float average_success = (float)succes_search / (float)stNo;
      printf( "successful search: %.4f comparisons on average\n", average_success );
      output_quadratic(fileNum);
      binFile.close();
  }


};
void PrintMenu(){
    cout << endl << "****        Hash Table       *****";
    cout << endl << "* 0. QUIT                        *";
    cout << endl << "* 1. Make a hash table   (linear)*";
    cout << endl << "* 2. Make a hash table   (double)*";
    cout << endl << "* 2. Make a hash table(quadratic)*";
    cout << endl << "****************************";
    cout << endl << "Input a choice(0, 1, 2, 3): ";
} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission miss ;
    string fileName;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1)       miss.Text2Binary(fileName,mission);
      else if ( mission == 2 ) miss.Text2Binary(fileName,mission);
      else if ( mission == 3 ) miss.Text2Binary(fileName,mission);
      else if ( mission > 3 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      cin >> mission ;
    } // while end
}

