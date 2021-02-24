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

  void treeDepth( TreePtr * node, int tmpdepth, int & depth ){ // 1 1
      TreePtr * temp = node ;
      if ( temp -> right == NULL && temp -> left == NULL ){
          if ( tmpdepth > depth ) depth = tmpdepth ;
      }
      else {
          if ( temp->right == NULL ) treeDepth( temp->left, tmpdepth+1, depth ) ;
          else if ( temp->left == NULL ) treeDepth( temp->right, tmpdepth+1 , depth ) ;
          else{
              treeDepth( temp->left, tmpdepth+1, depth ) ;
              treeDepth( temp->right, tmpdepth+1 , depth ) ;
          }

      }

  }

  int treeHeight( TreePtr * node ) {
     if (node == NULL) return -1;

     int left = treeHeight(node->left);
     int right = treeHeight(node->right);

     return 1 + max(left, right);
  }

  void PrintData( int high ){
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

      cout << "tree high : " << high+1 << "\n" ;
  }

  void Create(){
      tree = NULL ;
      TreePtr * temp = NULL ;
      int i = 0 ,high = 0 ;
      while ( i < treevec.size() ){
          if ( tree == NULL ){
              tree = new TreePtr ;
              tree->num = treevec[i].num ;
              tree->name = treevec[i].name ;
              tree->type = treevec[i].type ;
              tree->hp = treevec[i].hp ;
              tree->attack = treevec[i].attack ;
              tree->defense = treevec[i].defense ;
              tree->raw = treevec[i].raw ;
              tree->speed = treevec[i].speed;

              tree->left = NULL ;
              tree->right = NULL ;
              tree->same = NULL ;
              tree->parent = NULL ;

              temp = tree ;

              i++ ;
          }
          else if ( treevec[i].hp > temp->hp ){
              if ( temp->right == NULL ){
                  temp->right = new TreePtr ;

                  temp->right->num = treevec[i].num ;
                  temp->right->name = treevec[i].name ;
                  temp->right->type = treevec[i].type ;
                  temp->right->hp = treevec[i].hp ;
                  temp->right->attack = treevec[i].attack ;
                  temp->right->defense = treevec[i].defense ;
                  temp->right->speed = treevec[i].speed ;
                  temp->right->raw = treevec[i].raw ;

                  temp->right->parent = temp ;
                  temp->right->right = NULL ;
                  temp->right->left = NULL ;
                  temp->right->same = NULL ;

                  temp = tree ;
                  i++ ;
              }
              else{
                temp = temp->right ;
              }
          }
          else if ( treevec[i].hp < temp->hp ){
              if ( temp->left == NULL ){
                  temp->left = new TreePtr ;

                  temp->left->num = treevec[i].num ;
                  temp->left->name = treevec[i].name ;
                  temp->left->type = treevec[i].type ;
                  temp->left->hp = treevec[i].hp ;
                  temp->left->attack = treevec[i].attack ;
                  temp->left->defense = treevec[i].defense ;
                  temp->left->speed = treevec[i].speed ;
                  temp->left->raw = treevec[i].raw ;

                  temp->left->parent = temp ;
                  temp->left->right = NULL ;
                  temp->left->left = NULL ;
                  temp->left->same = NULL ;

                  temp = tree ;
                  i++ ;
              }
              else{
                temp = temp->left ;
              }
          }
          else if ( treevec[i].hp == temp->hp ){
              if ( temp->same == NULL ){
                  temp->same = new TreePtr ;

                  temp->same->num = treevec[i].num ;
                  temp->same->name = treevec[i].name ;
                  temp->same->type = treevec[i].type ;
                  temp->same->hp = treevec[i].hp ;
                  temp->same->attack = treevec[i].attack ;
                  temp->same->defense = treevec[i].defense ;
                  temp->same->speed = treevec[i].speed ;
                  temp->same->raw = treevec[i].raw ;

                  temp->same->parent = temp ;
                  temp->same->right = NULL ;
                  temp->same->left = NULL ;
                  temp->same->same = NULL ;

                  temp = tree ;
                  i++ ;
              }
              else {
                temp = temp->same ;
              }
          }
      }

      //int tmpdepth = 1, depth = 1 ;
      //treeDepth( tree, tmpdepth, depth ) ;

      int depth = treeHeight( tree ) ;
      PrintData( depth ) ;
  }

  void Mission1(){
    treevec.clear() ;
    tmpTree temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 601, 602, ...[0]Quit):" ) ;
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

           Create() ;

           tempin.close() ;

      } //if end

    } //while

  } // Mission1

  void Search( TreePtr * node, int sear ){
      times++ ;
      if ( node->right == NULL && node->left == NULL && node->same == NULL ){
         tmpTree tempt ;
         tempt.num = node->num ;
         tempt.name = node->name ;
         tempt.hp = node->hp ;
         tempt.type = node->type ;
         tempt.attack = node->attack ;
         tempt.defense = node->defense ;
         tempt.raw = node->raw ;
         hpvec.push_back( tempt ) ;

         return ;
      }
      else {
          if ( node->hp < sear && node->right != NULL )
              Search( node->right, sear ) ;

          else if ( node->hp > sear ){
              tmpTree tempt ;
              tempt.num = node->num ;
              tempt.name = node->name ;
              tempt.hp = node->hp ;
              tempt.type = node->type ;
              tempt.attack = node->attack ;
              tempt.defense = node->defense ;
              tempt.raw = node->raw ;
              hpvec.push_back( tempt ) ;


              if ( node->right != NULL ) Search( node->right, sear ) ;
              if ( node->same != NULL ){
                  Search( node->same, sear ) ;
                  times-- ;
              }
              if ( node->left != NULL ) Search( node->left, sear ) ;
          }

          else if ( node->hp == sear ){
              tmpTree tempt ;
              tempt.num = node->num ;
              tempt.name = node->name ;
              tempt.hp = node->hp ;
              tempt.type = node->type ;
              tempt.attack = node->attack ;
              tempt.defense = node->defense ;
              tempt.raw = node->raw ;
              hpvec.push_back( tempt ) ;

              if ( node->same != NULL ){
                  Search( node->same, sear ) ;
                  times-- ;
              }
              if ( node->right != NULL ) Search( node->right, sear ) ;
          }
      }
  }

  void Sort(){
      int i, j, temp;
      tmpTree temptype ;
      for (i = 0; i < hpvec.size() ; i++) {
          for (j = 0; j < hpvec.size() - i; j++){
              if (hpvec[j].hp < hpvec[j + 1].hp){
                  temptype = hpvec[j];
                  hpvec[j] = hpvec[j + 1];
                  hpvec[j + 1] = temptype;
              }
          }
      }

      cout << "\t#\tName\tType1\tHP\tAttack\tDefense\n" ;
      for ( int i = 0 ; i < hpvec.size() ; i++ ){
          cout << "[" << i+1 << "]" << "\t" ;
          cout << hpvec[i].num << "\t" ;
          cout << hpvec[i].name << "\t" ;
          cout << hpvec[i].type << "\t" ;
          cout << hpvec[i].hp << "\t" ;
          cout << hpvec[i].attack << "\t" ;
          cout << hpvec[i].defense << "\n" ;
      }
      hpvec.clear() ;

  }

  void Mission2() {
      int search_int = 0 ;
      cout << "give me limit :" ;
      cin >> search_int ;
      cout << "\n" ;

      Search( tree, search_int ) ;
      Sort() ;

      cout << "Number of visited nodes = " << times << "\n" ;
      times = 0 ;

  }

  void Mission3(){
      TreePtr * temp = tree ;
      if ( tree == NULL ) cout << "ALL GONE" << "\n" ;
      else if ( tree->right == NULL && tree->left == NULL && tree->same == NULL && tree->parent == NULL ){
            cout << tree->raw << "\n" ;
            tree = NULL ;
      }
      else if ( tree->right == NULL ){
          cout << tree->raw << "\n" ;
          if ( tree->same != NULL ){
              cout << "same\n" ;
              tree->num = tree->same->num ;
              tree->name = tree->same->name ;
              tree->type = tree->same->type ;
              tree->hp = tree->same->hp ;
              tree->attack = tree->same->attack  ;
              tree->defense = tree->same->defense ;
              tree->raw = tree->same->raw ;

              tree->same = tree->same->same ;
              if ( tree->same != NULL )tree->same->parent = tree ;
          }
          else{
             tree = tree->left ;
             tree->parent = NULL ;
          }

      }
      else if ( tree->right != NULL ) {
          while ( temp->right != NULL ) temp = temp->right ;
          cout << temp->raw << "\n" ;
          if ( temp->same != NULL ){
              cout << "same\n" ;
              temp->num = temp->same->num ;
              temp->name = temp->same->name ;
              temp->type = temp->same->type ;
              temp->hp = temp->same->hp ;
              temp->attack = temp->same->attack  ;
              temp->defense = temp->same->defense ;
              temp->raw = temp->same->raw ;

              temp->same = temp->same->same ;
              if ( temp->same != NULL ) temp->same->parent = temp ;
          }
          else{
              temp->parent->right = temp->left ;
              if ( temp->left != NULL ) temp->left->parent = temp->parent ;
          }
      }

      cout << "tree high : " << treeHeight( tree )+1 << "\n" ;

  }
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
      else if ( mission == 2 )
        miss.Mission2() ;
      else if ( mission == 3 )
        miss.Mission3() ;
      else if ( mission > 3 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;


      PrintMenu() ;
      gnum = 1 ;
      cin >> mission ;
    } // while end
}

