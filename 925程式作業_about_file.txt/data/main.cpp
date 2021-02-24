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
typedef struct cT {

  public:
    string rawR ;//
    string cname ;//
    string drealname ;
    string dname ;//
    int sNo ;
    int gNo ;

}; // college Type

static int gnum = 0 ;

class Mission{

  vector<cT> cSet201, cSet202, cSet203, cSet204, cSet205 ;

  public:

  void Save( int filenum ){

  } // Save



  void ReadAndSave(){



  } // ReadAndSave

  void DoForFilter( vector<cT> cSettemp, int lims, int limg ){

  } // DoForFilter


  void Filter(){


};
  void Merge() {
    Str100 filename ;
    int i = 0 ;
    char filechar1 = '\0' ;
    cin >> filechar1 ;
    while ( filechar1 != '\n' ){
        Str100[i] = filechar1 ;
        i++ ;
        cin >> filechar1 ;
    } // while

    printf(" ")
  }






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
      if ( mission == 1 )      Miss.ReadAndSave() ;
      else if ( mission == 2 ) Miss.Filter() ;
      else if ( mission == 3 ) Miss.Merge() ;
      else if ( mission > 3 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      gnum = 0 ;
      cin >> mission ;
    } // while end

} //
