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
#include <ctype.h>
#include <stdexcept>

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

  vector<tmpTree> treevec, limitvec ;
  TreePtr * tree = NULL ;

  void MergeD( vector<tmpTree> &Array, int _front, int mid, int _end){

    vector<tmpTree> LeftSub(Array.begin()+_front, Array.begin()+mid+1) ;
    vector<tmpTree> RightSub(Array.begin()+mid+1, Array.begin()+_end+1);

    tmpTree temptype ;
    temptype.hp = -1 ;
    temptype.raw = "0";
    temptype.attack = 0;
    temptype.defense = 0;
    temptype.name = "0";
    temptype.num = 0;
    temptype.speed = 0;
    temptype.type = "0";
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

  void Merge_SortD( vector<tmpTree> &Array, int _front, int _end){
                                       // front?Pend???x?}?d??
    if (_front < _end) {                   // ????e???x?}?d??O?????
        int mid = (_front+_end)/2;   // mid?Y?O?N?x?}??b????index
        Merge_SortD( Array, _front, mid);    // ?~??divide?x?}???e?b?qsubarray
        Merge_SortD( Array, mid+1, _end);    // ?~??divide?x?}????b?qsubarray
        MergeD( Array, _front, mid, _end);   // ?N???subarray?????, ?aX??X?????x?}
    }
  }

  void MergeI( vector<tmpTree> &Array, int _front, int mid, int _end){

    vector<tmpTree> LeftSub(Array.begin()+_front, Array.begin()+mid+1) ;
    vector<tmpTree> RightSub(Array.begin()+mid+1, Array.begin()+_end+1);

    tmpTree temptype ;
    temptype.hp = 9999999 ;
    temptype.raw = "0" ;
    LeftSub.insert(LeftSub.end(), temptype);      // ?bLeftSub[]????[?J??? Max ??????
    RightSub.insert(RightSub.end(), temptype);    // ?bRightSub[]????[?J??? Max ??????

    int idxLeft = 0, idxRight = 0;

    for (int i = _front; i <= _end; i++) {

        if (LeftSub[idxLeft].hp <= RightSub[idxRight].hp ) {
            Array[i] = LeftSub[idxLeft];
            idxLeft++;
        }
        else{
            Array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
  }

  void Merge_SortI( vector<tmpTree> &Array, int _front, int _end){

    if (_front < _end) {
        int mid = (_front+_end)/2;
        Merge_SortI( Array, _front, mid);
        Merge_SortI( Array, mid+1, _end);
        MergeI( Array, _front, mid, _end);
    }
  }

  void PrintData1(string fileNum){
      ofstream sort_out;
      sort_out.open("sort"+fileNum+".txt");
      sort_out << "#	Name	Type 1	Type 2	Total	HP	Attack	Defense	Sp. Atk	Sp. Def	Speed	Generation	Legendary\n" ;
      for ( int i = 0 ; i < treevec.size() ; i++ ){
          //sort_out << "[" << i+1 << "]" << "\t" ;
          //sort_out << treevec[i].num << "\t" ;
          //sort_out << treevec[i].name << "\t\t" ;
          //sort_out << treevec[i].type << "\t" ;
          //sort_out << treevec[i].hp << "\t" ;
          //sort_out << treevec[i].attack << "\t" ;
          //sort_out << treevec[i].defense << "\n" ;
          sort_out << treevec[i].raw << "\n" ;
      }
  }

  bool AllisNum(string str)  {
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
  }

  void Mission1(){
    treevec.clear() ;
    tmpTree temptype ;
    string fileNum ;
    char sort_direc;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 201, 202, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //
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



      if ( nofile == false ){
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
              if (AllisNum(arr[3])){
                 temptype.hp = atoi( arr[4].c_str() ) ;
                 temptype.attack = atoi( arr[5].c_str() ) ;
                 temptype.defense = atoi( arr[6].c_str() ) ;
                 temptype.speed = atoi( arr[9].c_str() ) ;
              }
              else{
                 temptype.hp = atoi( arr[5].c_str() ) ;
                 temptype.attack = atoi( arr[6].c_str() ) ;
                 temptype.defense = atoi( arr[7].c_str() ) ;
                 temptype.speed = atoi( arr[10].c_str() ) ;
              }

              treevec.push_back(temptype) ;


           } //

           bool true_commend = false;
           while( true_commend == false ){
              cout << "Input your sort direction(if increment, input i . if decrement input d) :";
              cin >> sort_direc;
              if (sort_direc == 'i'){
                  Merge_SortI( treevec, 0, gnum-1 ) ;
                  true_commend = true;
              }
              else if (sort_direc == 'd'){
                  Merge_SortD( treevec, 0, gnum-1 ) ;
                  true_commend = true;
              }

           }

           PrintData1(fileNum);

           tempin.close() ;

      } //if end

    } //while

  } // Mission1

  void Create(){
      tree = NULL ;
      TreePtr * temp = NULL ;
      int i = 0 ,high = 0 ;

      while ( i < treevec.size() ){
          if ( tree == NULL ){ // tree is empty, so new one
              tree = new TreePtr ;
              tree->num = treevec[i].num ;
              tree->name = treevec[i].name ;
              tree->type = treevec[i].type ;
              tree->hp = treevec[i].hp ;
              tree->attack = treevec[i].attack ;
              tree->defense = treevec[i].defense ;
              tree->speed = treevec[i].speed ;
              tree->raw = treevec[i].raw ;

              tree->left = NULL ;
              tree->right = NULL ;
              tree->same = NULL ;
              tree->parent = NULL ;

              temp = tree ;

              i++ ;
          }
          else if ( treevec[i].hp > temp->hp ){ // add to right
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
          else if ( treevec[i].hp < temp->hp ){ // add to left
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
          else if ( treevec[i].hp == temp->hp ){ // add to same
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
  }

  int treeHeight( TreePtr * node ) {
     if (node == NULL) return -1;

     int left = treeHeight(node->left);
     int right = treeHeight(node->right);

     return 1 + max(left, right);
  }

  void Print2(){
      cout << "Tree root is : " << endl;
      cout << "#      Name         Type    hp  attack  defense  speed\n";
      cout << tree->num << "\t" << tree->name << "\t" << tree->type << "\t" << tree->hp << "\t" << tree->attack << "\t" << tree->defense << "\t" << tree->speed << "\n";
      cout << "Tree Height is : " << treeHeight( tree )+1 << endl;
  }

  void Mission2(){
    treevec.clear() ;
    tree = NULL;
    tmpTree temptype ;
    string fileNum ;
    char sort_direc;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input input201, input202....., sort201, sort202 ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = fileNum + ".txt" ;

    while ( nofile == true ){ //
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() ){
            printf( "### %s.txt does not exist! ###\n", fileNum ) ;
            printf( "Input input201, input202....., sort201, sort202 ...[0]Quit):" ) ;
            cin.clear() ;
            cin >> fileNum ;
            string fileName = fileNum + ".txt" ;
        }
        else
            nofile = false ;
      } // if  end



      if ( nofile == false ){//
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
              if (AllisNum(arr[3])){
                 temptype.hp = atoi( arr[4].c_str() ) ;
                 temptype.attack = atoi( arr[5].c_str() ) ;
                 temptype.defense = atoi( arr[6].c_str() ) ;
                 temptype.speed = atoi( arr[9].c_str() ) ;
              }
              else{
                 temptype.hp = atoi( arr[5].c_str() ) ;
                 temptype.attack = atoi( arr[6].c_str() ) ;
                 temptype.defense = atoi( arr[7].c_str() ) ;
                 temptype.speed = atoi( arr[10].c_str() ) ;
              }

              treevec.push_back(temptype) ;


           } // for read\

           Create();
           Print2();
           tempin.close() ;

      } //if end

    } //while
  }

  void Search(TreePtr * node, int up_limit, int down_limit){
      tmpTree temp;
      if (node->hp >= down_limit && node->hp <= up_limit){
          temp.attack = node->attack;
          temp.defense = node->defense;
          temp.hp = node->hp;
          temp.name = node->name;
          temp.num = node->num;
          temp.raw = node->raw;
          temp.speed = node->speed;
          temp.type = node->type;

          limitvec.push_back(temp);
      }

      if (node->right!=NULL) Search(node->right, up_limit, down_limit); // search right
      if (node->left!=NULL) Search(node->left, up_limit, down_limit);  // search left
      if (node->same!=NULL) Search(node->same, up_limit, down_limit);  // search same

  }

  void Mission3(){
      cout << "input up limit :";
      int up_limit;
      cin >> up_limit;
      cout << "input down limit :";
      int down_limit;
      cin >> down_limit;

      Search(tree, up_limit, down_limit);
      Merge_SortD( limitvec, 0, limitvec.size()-1 );
      cout << "#      Name         Type    hp  attack  defense  speed\n";
      for(int i = 0; i<limitvec.size();i++){
        cout << limitvec[i].num << "\t" << limitvec[i].name << "\t" << limitvec[i].type << "\t" << limitvec[i].hp << "\t" << limitvec[i].attack << "\t" << limitvec[i].defense << "\t" << limitvec[i].speed << "\n";
      }
  }

};

void PrintMenu(){
    cout << endl << "*** Binary Tree                        ***";
    cout << endl << "* 0. QUIT                                *";
    cout << endl << "* 1. Read one file to build sort file    *";
    cout << endl << "* 2. Read one file to build Binary tree  *";
    cout << endl << "* 3. Set a limit if has a tree           *";
    cout << endl << "******************************************";
    cout << endl << "Input a choice(0, 1, 2, 3): ";

} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission miss ;
    int mission ;
    bool hasTree = false;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )
        miss.Mission1() ;
      else if ( mission == 2 ){
        miss.Mission2() ;
        hasTree = true;
      }
      else if ( mission == 3 && hasTree == true )
        miss.Mission3() ;
      else if ( mission == 3 && hasTree == false )
        cout << "you haven't built a tree.";
      else if ( mission > 3 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;


      PrintMenu() ;
      gnum = 0 ;
      cin >> mission ;
    } // while end
}

