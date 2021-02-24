#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef char Str100[ 100 ] ;
typedef struct task {

  public:
    string rawR ;
    int oid ;
    int arrival ;
    int duration ;
    int timeout ;

}; // task

typedef struct data {

  public:
    int oid ;
    int cid ;
    int delay ;
    int abort_departure ;


}; // task

static int gnum = 0 ;

class Mission{

  public:

  vector<task> inputfile ;

  void Shell_sort( string fileNum, int total ){ // 存進打開的文件檔
    task temptype1 ;
    task temptype2 ;
    int i = total ;
    for( i = i/2 ; i > 0 ; i = i/2 ){
        for ( int j = i ; j < total ; j++ ){
            for ( int k = j-i ; k >= 0 ; k = k-i ){
                if ( inputfile[k].arrival == inputfile[k+i].arrival ){
                    break ;
                }
                else if ( inputfile[k].arrival < inputfile[k+i].arrival ){
                    if ( inputfile[k].oid > inputfile[k+i].arrival ){
                        temptype1 = inputfile[k] ;
                        temptype2 = inputfile[k+i] ;
                        inputfile.erase( inputfile.begin()+k+i ) ;
                        inputfile.erase( inputfile.begin()+k ) ;
                        inputfile.insert( inputfile.begin()+k, temptype2 ) ;
                        inputfile.insert( inputfile.begin()+k+i, temptype1 ) ;
                    }
                    else
                        break ;
                }
                else if ( inputfile[k].arrival > inputfile[k+i].arrival ){
                    temptype1 = inputfile[k] ;
                    temptype2 = inputfile[k+i] ;
                    inputfile.erase( inputfile.begin()+k+i ) ;
                    inputfile.erase( inputfile.begin()+k ) ;
                    inputfile.insert( inputfile.begin()+k, temptype2 ) ;
                    inputfile.insert( inputfile.begin()+k+i, temptype1 ) ;
                }

            }
        }
    }

    ofstream tempout ;
    string fileName = "sort" + fileNum + ".txt" ;
    tempout.open ( fileName ) ;
    for ( int i = 0 ; i < gnum ; i++ ) {
        tempout << inputfile[i].rawR << "\n" ;
    }
     tempout.close() ;
  } // Save



  void Mission1(){

    task temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 201, 202, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + "txt" ;

    while ( nofile == true ){ //判斷有無檔案
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() )
            printf( "### input%d.txt does not exist! ###\n", fileNum ) ;
        else
            nofile = false ;
      } // if  end



      if ( nofile == false ){// 有檔案了就開始讀進並存入
          string trash ;
          string raw ;
          for ( int times = 0 ; getline( tempin, trash ) && times < 1 ; times++ );
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;
              temptype.rawR = raw ;
              temptype.oid = atoi( arr[0].c_str() ) ;
              temptype.arrival = atoi( arr[1].c_str() ) ;
              temptype.duration = atoi( arr[2].c_str() ) ;
              temptype.timeout = atoi( arr[3].c_str() ) ;

              inputfile.push_back(temptype) ;


           } // for read

           tempin.close() ;
           Shell_sort( fileNum, gnum ) ;
      } //if end
    } //while
  } // Mission1
};



void PrintMenu(){
  cout << endl << "*** File Object Manipulator ***";
  cout << endl << "* 0. QUIT *";
  cout << endl << "* 1. COPY (Read & Save a file) *";
  cout << endl << "* 2. FILTER (Reduce a file) *";
  cout << endl << "* 3. MERGE (Join two files) *";
  cout << endl << "*********************************";
  cout << endl << "Input a choice(0, 1, 2, 3): ";


} // PrintMenu()

int main() {
    PrintMenu() ;
    int mission ;
    Mission Miss ;

    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )      Miss.Mission1() ;
      //else if ( mission == 2 ) Miss.Filter() ;
      //else if ( mission == 3 ) Miss.Merge() ;
      else if ( mission > 1 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      gnum = 0 ;
      cin >> mission ;
    } // while end

} //
