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

typedef struct TreePtr {
  string raw ;
  int num ;
  string name ;
  string type ;
  int hp ;
  int attack ;
  int defense ;
  int speed;

  TreePtr * right ;
  TreePtr * left ;
  TreePtr * same ;
  TreePtr * parent ;
} ; // IntPtr

typedef struct tmpTree {
    public :

  string raw ;
  int num ;
  string name ;
  string type ;
  int hp ;
  int attack ;
  int defense ;
  int speed;
};

static int gnum = 0 ;

class Mission{

    public:

  vector<tmpTree> treevec, hpvec ;
  vector<string> deletevec ;
  int times = 0 ;
  TreePtr * tree = NULL ;

  void Merge( vector<tmpTree> &Array, int _front, int mid, int _end){

    vector<tmpTree> LeftSub(Array.begin()+_front, Array.begin()+mid+1) ;
    vector<tmpTree> RightSub(Array.begin()+mid+1, Array.begin()+_end+1);

    tmpTree temptype ;
    temptype.hp = -1 ;
    temptype.raw = "0" ;
    LeftSub.insert(LeftSub.end(), temptype);      // ?bLeftSub[]????[?J??? Max ??????
    RightSub.insert(RightSub.end(), temptype);    // ?bRightSub[]????[?J??? Max ??????

    int idxLeft = 0, idxRight = 0;

    for (int i = _front; i <= _end; i++) {

        if (LeftSub[idxLeft].hp >= RightSub[idxRight].hp ) {
            Array[i] = LeftSub[idxLeft];
            idxLeft++;
        }
        else{
            Array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
  }

  void Merge_Sort( vector<tmpTree> &Array, int _front, int _end){
                                       // front?Pend???x?}?d??
    if (_front < _end) {                   // ????e???x?}?d??O?????
        int mid = (_front+_end)/2;   // mid?Y?O?N?x?}??b????index
        Merge_Sort( Array, _front, mid);    // ?~??divide?x?}???e?b?qsubarray
        Merge_Sort( Array, mid+1, _end);    // ?~??divide?x?}????b?qsubarray
        Merge( Array, _front, mid, _end);   // ?N???subarray?????, ?aX??X?????x?}
    }
  }

  void PrintData(){
      cout << "\t#\tName\t\tType1\tHP\tAttack\tDefense\n" ;
      for ( int i = 0 ; i < treevec.size() ; i++ ){
          cout << "[" << i+1 << "]" << "\t" ;
          cout << treevec[i].num << "\t" ;
          cout << treevec[i].name << "\t\t" ;
          cout << treevec[i].type << "\t" ;
          cout << treevec[i].hp << "\t" ;
          cout << treevec[i].attack << "\t" ;
          cout << treevec[i].defense << "\n" ;
      }
  }

  void Mission1(){
    treevec.clear() ;
    tmpTree temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 201, 202, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //?P?_???L???
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() ){
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
            printf( "Input 601, 602, ...[0]Quit):" ) ;
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
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype.raw = raw ;
              temptype.num = atoi( arr[0].c_str() ) ;
              temptype.name = arr[1] ;
              temptype.type = arr[2] ;
              temptype.hp = atoi( arr[5].c_str() ) ;
              temptype.attack = atoi( arr[6].c_str() ) ;
              temptype.defense = atoi( arr[7].c_str() ) ;
              temptype.speed = atoi( arr[10].c_str() ) ;


              treevec.push_back(temptype) ;


           } // for read

           Merge_Sort( treevec, 0, gnum-1 ) ;
           PrintData();

           tempin.close() ;

      } //if end

    } //while

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
        //miss.Mission2() ;
      //else if ( mission == 3 )
        //miss.Mission3() ;
      else if ( mission > 3 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;


      PrintMenu() ;
      gnum = 1 ;
      cin >> mission ;
    } // while end
}

