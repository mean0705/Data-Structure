// 10627232 10627231

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

typedef struct School {
  int id ;
  int sNum ;
} ; // IntPtr

static int gnum = 0 ;

class Mission{

  public:

  vector<School> heap, temp ;

  void Build_heap(){
      for ( int bottom = 0 ; temp.size() > bottom ; bottom++ ){
          cout << "here\n" ;
          heap.push_back( temp[bottom] ) ;
          int place = bottom ;
          int parent = ( place - 1 ) / 2 ;
          if ( parent >= 0 ){
              while( parent >= 0 && heap[place].sNum > heap[parent].sNum ){
                  int temp = heap[place].sNum ;
                  heap[place].sNum = heap[parent].sNum ;
                  heap[parent].sNum = temp ;
                  place = parent ;
                  parent = ( place - 1 ) / 2 ;
              } // while
          }


      }

      for( int i = 0 ; heap.size() > i ; i++ ){
          cout << heap[i].id << "\n" ;
      }
  }


  void Mission1(){
    School temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    int total = 0 ;
    printf( "Input 101, 102, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //?P?_???L???
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() ){
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
            printf( "Input 101, 102, ...[0]Quit):" ) ;
            cin.clear() ;
            cin >> fileNum ;
            string fileName = "input" + fileNum + ".txt" ;
        }
        else
            nofile = false ;
      } // if  end



      if ( nofile == false ){// ?????F?N?}?l??i?as?J
          string raw ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;

          for ( string token ; getline( tempin, raw ) ; total++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype.id = total+1 ;
              temptype.sNum = atoi( arr[8].c_str() ) ;

              temp.push_back(temptype) ;

           } // for read

           tempin.close() ;

      } //if end

    } //while

    Build_heap() ;

  } // Mission1

};

void PrintMenu(){
    cout << endl << "*** Binary Search Tree on Pokemon ***";
    cout << endl << "* 0. QUIT                           *";
    cout << endl << "* 1. Read one file to build BST     *";
    cout << endl << "* 2. Threshold search on one column *";
    cout << endl << "* 3. Delete the max on one column   *";
    cout << endl << "*************************************";
    cout << endl << "Input a choice(0, 1, 2, 3): ";

} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission miss ;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )
        miss.Mission1() ;
      //else if ( mission == 2 )
      //  miss.Mission2() ;
      else if ( mission > 2 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;


      PrintMenu() ;
      cin >> mission ;
    } // while end
}

