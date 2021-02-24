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
    public :
  int id ;
  string schoolName ;
  string typeName ;
  string sunNight ;
  string level ;
  int stuNum ;
  School * same ;
} ; // IntPtr

typedef struct TreePtr {
    public :
  School * data[3] ;
  TreePtr * left ;
  TreePtr * right ;
  TreePtr * middle ;
  TreePtr * _max ;
  TreePtr * parent ;
  bool dataIsFall ;
};

typedef struct AVLtreePtr {
  School * data ;
  AVLtreePtr * left ;
  AVLtreePtr * right ;
  AVLtreePtr * parent ;
};

static int gnum = 0, sp = 0 ;

class Mission1{
  TreePtr * root = NULL ;

  int tree23Height( TreePtr * node ){ // calculate 23tree height
      int high = 1 ;
      while( node->left != NULL ){
          high++ ;
          node = node->left ;
      }
      return high ;
  }

  void setTreePtrNull( TreePtr * x ){ // let all pointer and data[] NULL
      x->left = NULL ;
      x->right = NULL ;
      x->middle = NULL ;
      x->parent = NULL ;
      x->_max = NULL ;
      x->data[0] = NULL ;
      x->data[1] = NULL ;
      x->data[2] = NULL ;
  }

  void newTreePtr( TreePtr * x ){ // set NULL new data[0]
      setTreePtrNull( x ) ;
      x->data[0] = new School ;
  }

  void copySchoolData( School * _copy , School * ttype ){ // copy left school data  to right
      _copy->id = ttype->id ;
      _copy->schoolName = ttype->schoolName ;
      _copy->typeName = ttype->typeName ;
      _copy->sunNight = ttype->sunNight ;
      _copy->level = ttype->level ;
      _copy->stuNum = ttype->stuNum ;
      _copy->same = ttype->same ;
  }

  void sameSchool( School * school, School * temptype ){ // same school, same pointer push back
      if ( school->same == NULL ){
        school->same = new School ;
        copySchoolData( school->same, temptype ) ;
      }
      else{
        sameSchool( school->same, temptype ) ;
      }
  }

  TreePtr * findCurrentLeaf( TreePtr * _search, School * temptype ){ // find insert location
      if ( _search->right == NULL && _search->left == NULL && _search->middle == NULL ){
          return _search ;
      }
      else {
          if ( _search->dataIsFall == false ){
              if ( temptype->schoolName > _search->data[0]->schoolName ) {
                  findCurrentLeaf( _search->right, temptype ) ;
              }
              else if ( temptype->schoolName < _search->data[0]->schoolName ){
                  findCurrentLeaf( _search->left, temptype ) ;
              }
              else if ( temptype->schoolName == _search->data[0]->schoolName ){
                  sameSchool( _search->data[0], temptype ) ;
                  return NULL ;
              }
              else ;
          }
          else if ( _search->dataIsFall == true ){
              if ( temptype->schoolName > _search->data[1]->schoolName ){
                  findCurrentLeaf( _search->right, temptype ) ;
              }
              else if ( temptype->schoolName < _search->data[0]->schoolName ){
                  findCurrentLeaf( _search->left, temptype ) ;
              }
              else if ( temptype->schoolName == _search->data[0]->schoolName ){
                  sameSchool( _search->data[0], temptype ) ;
                  return NULL ;
              }
              else if ( temptype->schoolName == _search->data[1]->schoolName ){
                  sameSchool( _search->data[1], temptype ) ;
                  return NULL ;
              }
              else if ( temptype->schoolName < _search->data[1]->schoolName && temptype->schoolName > _search->data[0]->schoolName ){
                  findCurrentLeaf( _search->middle, temptype ) ;
              }
              else ;
          }
      }
  }

  void compareTreePtrKey_put( TreePtr * node, School * datax, School * datay ){ // compare tree node which has two data
      node->data[1] = new School ;
      if ( datax->schoolName > datay->schoolName ) {
          copySchoolData( node->data[1], datax ) ;
          copySchoolData( node->data[0], datay ) ;

      }
      else if ( datax->schoolName < datay->schoolName ) {
          copySchoolData( node->data[1], datay ) ;
          copySchoolData( node->data[0], datax ) ;

      }
      else {
          cout << "error : same in. \n" ;
          cout << "datax name :" << datax->schoolName << "\n" ;
          cout << "datay name :" << datay->schoolName << "\n" ;
      }

      node->dataIsFall = true ;
  }

  void compareTempPtrKey_put( TreePtr * node, School * datax, School * datay, School * dataz ){// compare tree node which has tree node

      node->data[0] = new School ;
      node->data[1] = new School ;
      node->data[2] = new School ;
      if ( datax->schoolName > datay->schoolName && datax->schoolName > dataz->schoolName && datay->schoolName > dataz->schoolName ){
          copySchoolData( node->data[2], datax ) ;
          copySchoolData( node->data[1], datay ) ;
          copySchoolData( node->data[0], dataz ) ;
      }
      else if ( datax->schoolName > datay->schoolName && datax->schoolName > dataz->schoolName && datay->schoolName < dataz->schoolName ){
          copySchoolData( node->data[2], datax ) ;
          copySchoolData( node->data[0], datay ) ;
          copySchoolData( node->data[1], dataz ) ;
      }
      else if ( datay->schoolName > datax->schoolName && datay->schoolName > dataz->schoolName && datax->schoolName > dataz->schoolName ){
          copySchoolData( node->data[1], datax ) ;
          copySchoolData( node->data[2], datay ) ;
          copySchoolData( node->data[0], dataz ) ;
      }
      else if ( datay->schoolName > datax->schoolName && datay->schoolName > dataz->schoolName && datax->schoolName < dataz->schoolName ){
          copySchoolData( node->data[0], datax ) ;
          copySchoolData( node->data[2], datay ) ;
          copySchoolData( node->data[1], dataz ) ;
      }
      else if ( dataz->schoolName > datax->schoolName && dataz->schoolName > datay->schoolName && datax->schoolName > datay->schoolName ){
          copySchoolData( node->data[1], datax ) ;
          copySchoolData( node->data[0], datay ) ;
          copySchoolData( node->data[2], dataz ) ;
      }
      else if ( dataz->schoolName > datax->schoolName && dataz->schoolName > datay->schoolName && datax->schoolName < datay->schoolName ){
          copySchoolData( node->data[0], datax ) ;
          copySchoolData( node->data[1], datay ) ;
          copySchoolData( node->data[2], dataz ) ;
      }
      else {
          cout << "error : compare error.\n" ;
          cout << "datax name :" << datax->schoolName << "\n" ;
          cout << "datay name :" << datay->schoolName << "\n" ;
          cout << "dataz name :" << dataz->schoolName << "\n" ;
          if ( datax->schoolName == datay->schoolName ) cout << "what the fuck~~~??????\n" ;
      }
  }

  void beParent( TreePtr * x, TreePtr * y ){ // let x->child->parent = x , and y so.
      x->left->parent = x ;
      x->right->parent = x ;
      y->left->parent = y ;
      y->right->parent = y ;
  }

  void connectFourPointers( TreePtr * former, TreePtr * latter, TreePtr * temp ){ // tree node which has three node split complete, so connect back
      former->left = temp->left ;
      former->right = temp->middle ;
      latter->left = temp->right ;
      latter->right = temp->_max ;
  }

  void split( TreePtr * treeNode ){ // just split, and recursion
      TreePtr * p = NULL ;
      if ( treeNode ->parent == NULL ){  // tree node which I call IN this function is tree's root
          p = new TreePtr ;
          newTreePtr( p ) ;              // new p

          p->left = new TreePtr ;
          newTreePtr( p->left ) ;        // new p->left

          p->right = new TreePtr ;
          newTreePtr( p->right ) ;       // new p->right

          p->left->parent = p ;
          p->right->parent = p ;         // make p->child->parent = p

          copySchoolData( p->data[0], treeNode->data[1] ) ;
          copySchoolData( p->left->data[0], treeNode->data[0] ) ;
          copySchoolData( p->right->data[0], treeNode->data[2] ) ; // put data into three tree node

          p->dataIsFall = false ;
          p->left->dataIsFall = false ;
          p->right->dataIsFall = false ; // split, so their data each just have only one

          if ( treeNode->left != NULL && treeNode->right != NULL ){ // if tree node I call is not just tree's leaf
              connectFourPointers( p->left, p->right, treeNode ) ;  // connect, and let tree be normal.
              beParent( p->left, p->right ) ;
          }
          root = p ; // root becomes p
      }
      else{                              // tree node which I call IN this function is not tree's root
          p = treeNode->parent ;
          if ( p->dataIsFall == false ){ // if tree node's parent have only one data
              compareTreePtrKey_put( p, treeNode->data[1], p->data[0] ) ; // compare and put
              if ( treeNode == p->right ){ // middle and right new, and put tree data[0] and data[2] into and connect
                  p->middle = new TreePtr ;
                  newTreePtr( p->middle ) ;
                  copySchoolData( p->middle->data[0], treeNode->data[0] ) ; // new p->middle and put data into

                  p->right = NULL ;

                  p->right = new TreePtr ;
                  newTreePtr( p->right ) ;
                  copySchoolData( p->right->data[0], treeNode->data[2] ) ; // new p-> right and put data into

                  p->middle->parent = p ;
                  p->right->parent= p ;

                  p->dataIsFall = true ;
                  p->middle->dataIsFall = false ;
                  p->right->dataIsFall = false ;                     // p will have two data


                  if ( treeNode->left != NULL && treeNode->right != NULL ){ // if tree node is not leaf
                      connectFourPointers( p->middle, p->right, treeNode ) ;
                      beParent( p->middle, p->right ) ;
                  }

              }
              else if ( treeNode == p->left ){ // left and middle new, and put data[0] and data[2] into and connect
                  p->left = NULL ;

                  p->left = new TreePtr ;
                  newTreePtr( p->left ) ;
                  copySchoolData( p->left->data[0], treeNode->data[0] ) ;

                  p->middle = new TreePtr ;
                  newTreePtr( p->middle ) ;
                  copySchoolData( p->middle->data[0], treeNode->data[2] ) ;

                  p->left->parent = p ;
                  p->middle->parent = p ;

                  p->dataIsFall = true ;
                  p->left->dataIsFall = false ;
                  p->middle->dataIsFall = false ;


                  if ( treeNode->left != NULL && treeNode->right != NULL ){
                      connectFourPointers( p->left, p->middle, treeNode ) ;
                      beParent( p->left, p->middle ) ;
                  }
              }

          }
          else if ( p->dataIsFall == true ){ // if tree node's parent's  have two data
            TreePtr * temp = new TreePtr ; // create temp tree pointer for split
            setTreePtrNull( temp ) ;
            compareTempPtrKey_put( temp, p->data[0], p->data[1], treeNode->data[1] ) ; // question
            if ( treeNode == p->right ){ // copy p->left,middle to temp's, and new right , _max, make temp complete
                temp->left = p->left ;
                temp->middle = p->middle ;

                temp->right = new TreePtr ;
                newTreePtr( temp->right ) ;
                copySchoolData( temp->right->data[0], treeNode->data[0] ) ;

                temp->_max = new TreePtr ;
                newTreePtr( temp->_max ) ;
                copySchoolData( temp->_max->data[0], treeNode->data[2] ) ;

                temp->left->parent = temp ;
                temp->middle->parent = temp ;
                temp->right->parent = temp ;
                temp->_max->parent = temp ;

                temp->right->dataIsFall = false ;
                temp->_max->dataIsFall = false ;


                if ( treeNode->left != NULL && treeNode->right != NULL ){ // if tree node is not leaf
                    connectFourPointers( temp->right, temp->_max, treeNode ) ;
                    beParent( temp->right, temp->_max ) ;
                }
            }
            else if ( treeNode == p->middle ){ // copy p->left,_max to temp's, and new right , middle, make temp complete
                temp->left = p->left ;
                temp->left->parent = temp ;

                temp->middle = new TreePtr ;
                newTreePtr( temp->middle ) ;
                temp->middle->parent = temp ;

                copySchoolData( temp->middle->data[0], treeNode->data[0] ) ;

                temp->right = new TreePtr ;
                newTreePtr( temp->right ) ;
                temp->right->parent = temp ;

                copySchoolData( temp->right->data[0], treeNode->data[2] ) ;

                temp->_max = p->right ;
                temp->_max->parent = temp ;

                temp->middle->dataIsFall = false ;
                temp->right->dataIsFall = false ;


                if ( treeNode->left != NULL && treeNode->right != NULL ){
                    connectFourPointers( temp->middle, temp->right, treeNode ) ;
                    beParent( temp->middle, temp->right ) ;
                }
            }
            else if ( treeNode == p->left ){ // copy p->right,_max to temp's, and new left , middle, make temp complete
                temp->left = new TreePtr ;
                newTreePtr( temp->left ) ;
                temp->left->parent = temp ;

                copySchoolData( temp->left->data[0], treeNode->data[0] ) ;

                temp->middle = new TreePtr ;
                newTreePtr( temp->middle ) ;
                temp->middle->parent = temp ;
                copySchoolData( temp->middle->data[0], treeNode->data[2] ) ;

                temp->right = p->middle ;
                temp->right->parent = temp ;
                temp->_max = p->right ;
                temp->_max->parent = temp ;

                temp->left->dataIsFall = false ;
                temp->middle->dataIsFall = false ;

                connectFourPointers( temp->left, temp->middle, treeNode ) ;
                if ( treeNode->left != NULL && treeNode->right != NULL ){
                    connectFourPointers( temp->left, temp->middle, treeNode ) ;
                    beParent( temp->left, temp->middle ) ;
                }
            }
            else ;

            if ( p == root )  root = temp ;   // set root
            else if ( p == p->parent->right ) { // set parent pointer
                    temp->parent = p->parent ;
                    p->parent->right = temp ;
            }
            else if ( p == p->parent->middle ) {
                    temp->parent = p->parent ;
                    p->parent->middle = temp ;
            }
            else if ( p == p->parent->left ) {
                    temp->parent = p->parent ;
                    p->parent->left = temp ;
            }
            else ;

            split( temp ) ; // because temp have three data
          }
          else ;

      }

  }

  void Create23tree( School * temptype ){ // create 23tree
      if ( root == NULL ){ // set root->data[0]
          root = new TreePtr ;
          newTreePtr( root ) ;
          copySchoolData( root->data[0], temptype ) ; // put temp type into root's data[0]
          root->dataIsFall = false ;
      }
      else{
          TreePtr * follow = root ;
          follow = findCurrentLeaf( follow, temptype ) ; // Insert and find node's location
          if ( follow == NULL ) return ; // node which I find and node which is done have same school name except follow
          else {
              if ( follow->dataIsFall == false ){ // follow has only one data
                  if ( temptype->schoolName == follow->data[0]->schoolName ){
                      sameSchool( follow->data[0], temptype ) ;
                      return ;
                  }
                  compareTreePtrKey_put( follow, temptype,  follow->data[0] ) ; // compare two data and sort
              }
              else if ( follow->dataIsFall == true ){

                  TreePtr * tempForSplit = new TreePtr ; // new tree pointer
                  setTreePtrNull( tempForSplit ) ;
                  //tempForSplit->dataIsFall = false ;
                  if ( temptype->schoolName == follow->data[0]->schoolName ){
                      sameSchool( follow->data[0], temptype ) ;
                      return ;
                  }
                  if ( temptype->schoolName == follow->data[1]->schoolName ){
                      sameSchool( follow->data[1], temptype ) ;
                      return ;
                  }
                  compareTempPtrKey_put( tempForSplit, follow->data[0], follow->data[1], temptype ) ; // compare three data and sort, then put into tempForSplit

                  tempForSplit->parent = follow->parent ; // let tempForSplit replace with follow
                  if ( follow->parent == NULL ) ;
                  else if ( follow == follow->parent->right ) {
                        follow->parent->right = NULL ;
                        follow->parent->right = tempForSplit ;
                  }
                  else if ( follow == follow->parent->left ) {
                        follow->parent->left = NULL ;
                        follow->parent->left = tempForSplit ;
                  }
                  else if ( follow == follow->parent->middle ) {
                        follow->parent->middle = NULL ;
                        follow->parent->middle = tempForSplit ;
                  }
                  else ;

                  split( tempForSplit ) ;
              }
              else ;
          }
      }
  }

  void Print_Raw( School * temp, int & total ){ // print raw
      cout << total << ". [" << temp->id << "] " << temp->schoolName << ", " << temp->typeName << ", " << temp->sunNight << ", " << temp->level << ", " << temp->stuNum << "\n" ;
      total++ ;
      while( temp->same != NULL ){
          temp = temp->same ;
          cout << total << ". [" << temp->id << "] " << temp->schoolName << ", " << temp->typeName << ", " << temp->sunNight << ", " << temp->level << ", " << temp->stuNum << "\n" ;
          total++ ;
      }
  }

  void Print_Ans(){ // print data
      int total = 1 ;
      School * temp0 = NULL ;
      School * temp1 = NULL ;
      if ( root->data[1] != NULL ){
          temp0 = root->data[0] ;
          temp1 = root->data[1] ;
          if ( temp0->id < temp1->id ){
              Print_Raw( temp0, total ) ;
              Print_Raw( temp1, total ) ;
          }
          else {
              Print_Raw( temp1, total ) ;
              Print_Raw( temp0, total ) ;
          }
      }
      else if ( root->data[1] == NULL ){
          temp0 = root->data[0] ;
          Print_Raw( temp0, total ) ;
      }
  }

  public : void Mission(){
    School * temptype  = new School ;
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
        tempin.open( fileName.c_str() );
        if ( ! tempin.is_open() ){
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
            printf( "Input 201, 202, ...[0]Quit):" ) ;
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
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype->id = gnum+1 ;
              temptype->schoolName = arr[1] ;
              temptype->typeName = arr[3] ;
              temptype->sunNight = arr[4] ;
              temptype->level = arr[5] ;
              temptype->stuNum = atoi( arr[6].c_str() ) ;
              if ( arr[6].size() > 3 ){
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), ','));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
              }
              temptype->same = NULL ;

              Create23tree( temptype ) ;


           } // for read

           cout << "Tree height = " << tree23Height( root ) << "\n" ;
           Print_Ans() ;
           tempin.close() ;
           root = NULL ;

      } //if end

    } //while

  } // Mission1

};

class Mission2{
  AVLtreePtr * AVLroot = NULL ;

  int treeHeight( AVLtreePtr * node ) {
     if (node == NULL) return 0;

     int left = treeHeight(node->left);
     int right = treeHeight(node->right);

     return 1 + max(left, right);
  }

  void copySchoolData( School * _copy , School * ttype ){
      _copy->id = ttype->id ;
      _copy->schoolName = ttype->schoolName ;
      _copy->typeName = ttype->typeName ;
      _copy->sunNight = ttype->sunNight ;
      _copy->level = ttype->level ;
      _copy->stuNum = ttype->stuNum ;
      _copy->same = ttype->same ;
  }

  void setAVLtreeNULL( AVLtreePtr * x ){
      x->data = new School ;
      x->left = NULL ;
      x->right = NULL ;
      x->parent = NULL ;
  }

  void sameType( School * school, School * temptype ){
      if ( school->same == NULL ){
        school->same = new School ;
        copySchoolData( school->same, temptype ) ;
      }
      else{
        sameType( school->same, temptype ) ;
      }
  }

  AVLtreePtr * Insert( AVLtreePtr * follow , School * temptype ){
      if ( temptype->typeName > follow->data->typeName ){
          if ( follow->right == NULL ){
              follow->right = new AVLtreePtr ;
              setAVLtreeNULL( follow->right ) ;
              follow->right->parent = follow ;
              copySchoolData( follow->right->data, temptype ) ;
              return follow ;
          }
          else Insert( follow->right, temptype ) ;
      }
      else if ( temptype->typeName < follow->data->typeName ){
          if ( follow->left == NULL ){
              follow->left = new AVLtreePtr ;
              setAVLtreeNULL( follow->left ) ;
              follow->left->parent = follow ;
              copySchoolData( follow->left->data, temptype ) ;
              return follow ;
          }
          else Insert( follow->left, temptype ) ;
      }
      else if ( temptype->typeName == follow->data->typeName ) {
          sameType( follow->data, temptype );
          return NULL ;
      }
      else ;
  }

  AVLtreePtr * FindRotate( AVLtreePtr * follow ){
    if ( follow == AVLroot ){
        if ( treeHeight(follow->left) - treeHeight(follow->right) == 2
          ||  treeHeight(follow->left) - treeHeight(follow->right) == -2 ){
              return follow ;
          }
        else
            return NULL ;
    }
    else if ( treeHeight(follow->left) - treeHeight(follow->right) == 2
        ||  treeHeight(follow->left) - treeHeight(follow->right) == -2 ){
            return follow ;
        }
    else {
        FindRotate( follow->parent ) ;
    }
  }

  AVLtreePtr * rotateLL( AVLtreePtr * x ){
      AVLtreePtr * y = x->left ;
      x->left = y->right ;
      if ( x->left != NULL ) x->left->parent = x ;
      y->right = x ;
      x->parent = y ;
      return y ;
  }

  AVLtreePtr * rotateRR( AVLtreePtr * x ){
      AVLtreePtr * y = x->right ;
      x->right = y->left ;
      if ( x->right != NULL ) x->right->parent = x ;
      y->left = x ;
      x->parent = y ;
      return y ;
  }

  AVLtreePtr * rotateLR( AVLtreePtr * x ){
      x->left = rotateRR( x->left ) ;
      return rotateLL( x );
  }

  AVLtreePtr * rotateRL( AVLtreePtr * x ){
      x->right = rotateLL( x->right ) ;
      return rotateRR( x );
  }

  void CreateAVLtree( School * temptype ){
    if ( AVLroot == NULL ){ // set AVLroot data
        AVLroot = new AVLtreePtr ;
        setAVLtreeNULL( AVLroot ) ;
        copySchoolData( AVLroot->data, temptype ) ;
    }
    else{
        AVLtreePtr * temp = NULL ;
        AVLtreePtr * follow = AVLroot ;
        bool isRight = false ;
        follow = Insert( follow, temptype ) ; // Insert
        if ( follow == NULL ) // same typeName
            return ;
        follow = FindRotate( follow ) ; // follow needs to rotate
        if ( follow == NULL )
            return ;


        if ( treeHeight( follow->left ) - treeHeight( follow->right ) == 2 ){ // follow node's balance factor is 2
            AVLtreePtr * templeft = follow->left ;
            if ( treeHeight( templeft->left ) - treeHeight( templeft->right ) == 0 ||
                 treeHeight( templeft->left ) - treeHeight( templeft->right ) == 1 ){ // follow->left node's balance factor is 0 or 1, LL
                if ( follow == AVLroot ){
                    AVLroot = rotateLL( AVLroot ) ;
                    AVLroot->parent = NULL ;
                }
                else{
                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateLL( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;
                }
            }
            else if ( treeHeight( templeft->left ) - treeHeight( templeft->right ) == -1 ){ // LR
                if ( follow == AVLroot ){
                    AVLroot = rotateLR( AVLroot ) ;
                    AVLroot->parent = NULL ;
                }
                else{

                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateLR( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;

                }
                //double rotation
            }
            else ;
        }
        else if ( treeHeight( follow->left ) - treeHeight( follow->right ) == -2 ){ //follow node's balance factor is -2
            AVLtreePtr * tempright = follow->right ;
            if ( treeHeight( tempright->left ) - treeHeight( tempright->right ) == 0 ||
                 treeHeight( tempright->left ) - treeHeight( tempright->right ) == -1 ){ // follow->right node's balance factor is 0 or -1, RR
                if ( follow == AVLroot )
                    AVLroot = rotateRR( AVLroot ) ;
                else{
                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateRR( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;

                }
            }
            else if (  treeHeight( tempright->left ) - treeHeight( tempright->right ) == 1 ){ // RL
                if ( follow == AVLroot )
                    AVLroot = rotateRL( AVLroot ) ;
                else{
                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateRL( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;
                }
                //double rotation
            }
            else;
        }
        else ;
    }

  }

  void Print_Raw( School * temp, int total ){
      cout << total << ". [" << temp->id << "] " << temp->schoolName << ", " << temp->typeName << ", " << temp->sunNight << ", " << temp->level << ", " << temp->stuNum << "\n" ;
      total++ ;
      while( temp->same != NULL ){
          temp = temp->same ;
          cout << total << ". [" << temp->id << "] " << temp->schoolName << ", " << temp->typeName << ", " << temp->sunNight << ", " << temp->level << ", " << temp->stuNum << "\n" ;
          total++ ;
      }
  }

  public : void Mission(){
    School * temptype  = new School ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;

    printf( "Input 201, 202, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName.c_str() );
        if ( ! tempin.is_open() ){
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
            printf( "Input 201, 202, ...[0]Quit):" ) ;
            cin.clear() ;
            cin >> fileNum ;
            string fileName = "input" + fileNum + ".txt" ;
        }
        else
            nofile = false ;
      } // if  end



      if ( nofile == false ){ //
          string raw ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype->id = gnum+1 ;
              temptype->schoolName = arr[1] ;
              temptype->typeName = arr[3] ;
              temptype->sunNight = arr[4] ;
              temptype->level = arr[5] ;
              temptype->stuNum = atoi( arr[6].c_str() ) ;
              if ( arr[6].size() > 3 ){
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), ','));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
              }
              temptype->same = NULL ;
              CreateAVLtree( temptype ) ;


           } // for read

           cout << "Tree height = " << treeHeight( AVLroot ) << "\n" ;
           Print_Raw( AVLroot->data, 1 ) ;
           tempin.close() ;
           AVLroot = NULL ;

      } //if end

    } //while

  } // Mission1



};

class Mission3{

  TreePtr * root = NULL ;
  AVLtreePtr * AVLroot = NULL ;
  vector<School> temp ;

  int tree23Height( TreePtr * node ){ // calculate 23tree height
      int high = 1 ;
      while( node->left != NULL ){
          high++ ;
          node = node->left ;
      }
      return high ;
  }

  void setTreePtrNull( TreePtr * x ){ // let all pointer and data[] NULL
      x->left = NULL ;
      x->right = NULL ;
      x->middle = NULL ;
      x->parent = NULL ;
      x->_max = NULL ;
      x->data[0] = NULL ;
      x->data[1] = NULL ;
      x->data[2] = NULL ;
  }

  void newTreePtr( TreePtr * x ){ // set NULL new data[0]
      setTreePtrNull( x ) ;
      x->data[0] = new School ;
  }

  void copySchoolData( School * _copy , School * ttype ){ // copy left school data  to right
      _copy->id = ttype->id ;
      _copy->schoolName = ttype->schoolName ;
      _copy->typeName = ttype->typeName ;
      _copy->sunNight = ttype->sunNight ;
      _copy->level = ttype->level ;
      _copy->stuNum = ttype->stuNum ;
      _copy->same = ttype->same ;
  }

  void sameSchool( School * school, School * temptype ){ // same school, same pointer push back
      if ( school->same == NULL ){
        school->same = new School ;
        copySchoolData( school->same, temptype ) ;
      }
      else{
        sameSchool( school->same, temptype ) ;
      }
  }

  TreePtr * findCurrentLeaf( TreePtr * _search, School * temptype ){ // find insert location
      if ( _search->right == NULL && _search->left == NULL && _search->middle == NULL ){
          return _search ;
      }
      else {
          if ( _search->dataIsFall == false ){
              if ( temptype->schoolName > _search->data[0]->schoolName ) {
                  findCurrentLeaf( _search->right, temptype ) ;
              }
              else if ( temptype->schoolName < _search->data[0]->schoolName ){
                  findCurrentLeaf( _search->left, temptype ) ;
              }
              else if ( temptype->schoolName == _search->data[0]->schoolName ){
                  sameSchool( _search->data[0], temptype ) ;
                  return NULL ;
              }
              else ;
          }
          else if ( _search->dataIsFall == true ){
              if ( temptype->schoolName > _search->data[1]->schoolName ){
                  findCurrentLeaf( _search->right, temptype ) ;
              }
              else if ( temptype->schoolName < _search->data[0]->schoolName ){
                  findCurrentLeaf( _search->left, temptype ) ;
              }
              else if ( temptype->schoolName == _search->data[0]->schoolName ){
                  sameSchool( _search->data[0], temptype ) ;
                  return NULL ;
              }
              else if ( temptype->schoolName == _search->data[1]->schoolName ){
                  sameSchool( _search->data[1], temptype ) ;
                  return NULL ;
              }
              else if ( temptype->schoolName < _search->data[1]->schoolName && temptype->schoolName > _search->data[0]->schoolName ){
                  findCurrentLeaf( _search->middle, temptype ) ;
              }
              else ;
          }
      }
  }

  void compareTreePtrKey_put( TreePtr * node, School * datax, School * datay ){ // compare tree node which has two data
      node->data[1] = new School ;
      if ( datax->schoolName > datay->schoolName ) {
          copySchoolData( node->data[1], datax ) ;
          copySchoolData( node->data[0], datay ) ;

      }
      else if ( datax->schoolName < datay->schoolName ) {
          copySchoolData( node->data[1], datay ) ;
          copySchoolData( node->data[0], datax ) ;

      }
      else {
          cout << "error : same in. \n" ;
          cout << "datax name :" << datax->schoolName << "\n" ;
          cout << "datay name :" << datay->schoolName << "\n" ;
      }

      node->dataIsFall = true ;
  }

  void compareTempPtrKey_put( TreePtr * node, School * datax, School * datay, School * dataz ){// compare tree node which has tree node

      node->data[0] = new School ;
      node->data[1] = new School ;
      node->data[2] = new School ;
      if ( datax->schoolName > datay->schoolName && datax->schoolName > dataz->schoolName && datay->schoolName > dataz->schoolName ){
          copySchoolData( node->data[2], datax ) ;
          copySchoolData( node->data[1], datay ) ;
          copySchoolData( node->data[0], dataz ) ;
      }
      else if ( datax->schoolName > datay->schoolName && datax->schoolName > dataz->schoolName && datay->schoolName < dataz->schoolName ){
          copySchoolData( node->data[2], datax ) ;
          copySchoolData( node->data[0], datay ) ;
          copySchoolData( node->data[1], dataz ) ;
      }
      else if ( datay->schoolName > datax->schoolName && datay->schoolName > dataz->schoolName && datax->schoolName > dataz->schoolName ){
          copySchoolData( node->data[1], datax ) ;
          copySchoolData( node->data[2], datay ) ;
          copySchoolData( node->data[0], dataz ) ;
      }
      else if ( datay->schoolName > datax->schoolName && datay->schoolName > dataz->schoolName && datax->schoolName < dataz->schoolName ){
          copySchoolData( node->data[0], datax ) ;
          copySchoolData( node->data[2], datay ) ;
          copySchoolData( node->data[1], dataz ) ;
      }
      else if ( dataz->schoolName > datax->schoolName && dataz->schoolName > datay->schoolName && datax->schoolName > datay->schoolName ){
          copySchoolData( node->data[1], datax ) ;
          copySchoolData( node->data[0], datay ) ;
          copySchoolData( node->data[2], dataz ) ;
      }
      else if ( dataz->schoolName > datax->schoolName && dataz->schoolName > datay->schoolName && datax->schoolName < datay->schoolName ){
          copySchoolData( node->data[0], datax ) ;
          copySchoolData( node->data[1], datay ) ;
          copySchoolData( node->data[2], dataz ) ;
      }
      else {
          cout << "error : compare error.\n" ;
          cout << "datax name :" << datax->schoolName << "\n" ;
          cout << "datay name :" << datay->schoolName << "\n" ;
          cout << "dataz name :" << dataz->schoolName << "\n" ;
          if ( datax->schoolName == datay->schoolName ) cout << "what the fuck~~~??????\n" ;
      }
  }

  void beParent( TreePtr * x, TreePtr * y ){ // let x->child->parent = x , and y so.
      x->left->parent = x ;
      x->right->parent = x ;
      y->left->parent = y ;
      y->right->parent = y ;
  }

  void connectFourPointers( TreePtr * former, TreePtr * latter, TreePtr * temp ){ // tree node which has three node split complete, so connect back
      former->left = temp->left ;
      former->right = temp->middle ;
      latter->left = temp->right ;
      latter->right = temp->_max ;
  }

  void split( TreePtr * treeNode ){ // just split, and recursion
      TreePtr * p = NULL ;
      if ( treeNode ->parent == NULL ){  // tree node which I call IN this function is tree's root
          p = new TreePtr ;
          newTreePtr( p ) ;              // new p

          p->left = new TreePtr ;
          newTreePtr( p->left ) ;        // new p->left

          p->right = new TreePtr ;
          newTreePtr( p->right ) ;       // new p->right

          p->left->parent = p ;
          p->right->parent = p ;         // make p->child->parent = p

          copySchoolData( p->data[0], treeNode->data[1] ) ;
          copySchoolData( p->left->data[0], treeNode->data[0] ) ;
          copySchoolData( p->right->data[0], treeNode->data[2] ) ; // put data into three tree node

          p->dataIsFall = false ;
          p->left->dataIsFall = false ;
          p->right->dataIsFall = false ; // split, so their data each just have only one

          if ( treeNode->left != NULL && treeNode->right != NULL ){ // if tree node I call is not just tree's leaf
              connectFourPointers( p->left, p->right, treeNode ) ;  // connect, and let tree be normal.
              beParent( p->left, p->right ) ;
          }
          root = p ; // root becomes p
      }
      else{                              // tree node which I call IN this function is not tree's root
          p = treeNode->parent ;
          if ( p->dataIsFall == false ){ // if tree node's parent have only one data
              compareTreePtrKey_put( p, treeNode->data[1], p->data[0] ) ; // compare and put
              if ( treeNode == p->right ){ // middle and right new, and put tree data[0] and data[2] into and connect
                  p->middle = new TreePtr ;
                  newTreePtr( p->middle ) ;
                  copySchoolData( p->middle->data[0], treeNode->data[0] ) ; // new p->middle and put data into

                  p->right = NULL ;

                  p->right = new TreePtr ;
                  newTreePtr( p->right ) ;
                  copySchoolData( p->right->data[0], treeNode->data[2] ) ; // new p-> right and put data into

                  p->middle->parent = p ;
                  p->right->parent= p ;

                  p->dataIsFall = true ;
                  p->middle->dataIsFall = false ;
                  p->right->dataIsFall = false ;                     // p will have two data


                  if ( treeNode->left != NULL && treeNode->right != NULL ){ // if tree node is not leaf
                      connectFourPointers( p->middle, p->right, treeNode ) ;
                      beParent( p->middle, p->right ) ;
                  }

              }
              else if ( treeNode == p->left ){ // left and middle new, and put data[0] and data[2] into and connect
                  p->left = NULL ;

                  p->left = new TreePtr ;
                  newTreePtr( p->left ) ;
                  copySchoolData( p->left->data[0], treeNode->data[0] ) ;

                  p->middle = new TreePtr ;
                  newTreePtr( p->middle ) ;
                  copySchoolData( p->middle->data[0], treeNode->data[2] ) ;

                  p->left->parent = p ;
                  p->middle->parent = p ;

                  p->dataIsFall = true ;
                  p->left->dataIsFall = false ;
                  p->middle->dataIsFall = false ;


                  if ( treeNode->left != NULL && treeNode->right != NULL ){
                      connectFourPointers( p->left, p->middle, treeNode ) ;
                      beParent( p->left, p->middle ) ;
                  }
              }

          }
          else if ( p->dataIsFall == true ){ // if tree node's parent's  have two data
            TreePtr * temp = new TreePtr ; // create temp tree pointer for split
            setTreePtrNull( temp ) ;
            compareTempPtrKey_put( temp, p->data[0], p->data[1], treeNode->data[1] ) ; // question
            if ( treeNode == p->right ){ // copy p->left,middle to temp's, and new right , _max, make temp complete
                temp->left = p->left ;
                temp->middle = p->middle ;

                temp->right = new TreePtr ;
                newTreePtr( temp->right ) ;
                copySchoolData( temp->right->data[0], treeNode->data[0] ) ;

                temp->_max = new TreePtr ;
                newTreePtr( temp->_max ) ;
                copySchoolData( temp->_max->data[0], treeNode->data[2] ) ;

                temp->left->parent = temp ;
                temp->middle->parent = temp ;
                temp->right->parent = temp ;
                temp->_max->parent = temp ;

                temp->right->dataIsFall = false ;
                temp->_max->dataIsFall = false ;


                if ( treeNode->left != NULL && treeNode->right != NULL ){ // if tree node is not leaf
                    connectFourPointers( temp->right, temp->_max, treeNode ) ;
                    beParent( temp->right, temp->_max ) ;
                }
            }
            else if ( treeNode == p->middle ){ // copy p->left,_max to temp's, and new right , middle, make temp complete
                temp->left = p->left ;
                temp->left->parent = temp ;

                temp->middle = new TreePtr ;
                newTreePtr( temp->middle ) ;
                temp->middle->parent = temp ;

                copySchoolData( temp->middle->data[0], treeNode->data[0] ) ;

                temp->right = new TreePtr ;
                newTreePtr( temp->right ) ;
                temp->right->parent = temp ;

                copySchoolData( temp->right->data[0], treeNode->data[2] ) ;

                temp->_max = p->right ;
                temp->_max->parent = temp ;

                temp->middle->dataIsFall = false ;
                temp->right->dataIsFall = false ;


                if ( treeNode->left != NULL && treeNode->right != NULL ){
                    connectFourPointers( temp->middle, temp->right, treeNode ) ;
                    beParent( temp->middle, temp->right ) ;
                }
            }
            else if ( treeNode == p->left ){ // copy p->right,_max to temp's, and new left , middle, make temp complete
                temp->left = new TreePtr ;
                newTreePtr( temp->left ) ;
                temp->left->parent = temp ;

                copySchoolData( temp->left->data[0], treeNode->data[0] ) ;

                temp->middle = new TreePtr ;
                newTreePtr( temp->middle ) ;
                temp->middle->parent = temp ;
                copySchoolData( temp->middle->data[0], treeNode->data[2] ) ;

                temp->right = p->middle ;
                temp->right->parent = temp ;
                temp->_max = p->right ;
                temp->_max->parent = temp ;

                temp->left->dataIsFall = false ;
                temp->middle->dataIsFall = false ;

                connectFourPointers( temp->left, temp->middle, treeNode ) ;
                if ( treeNode->left != NULL && treeNode->right != NULL ){
                    connectFourPointers( temp->left, temp->middle, treeNode ) ;
                    beParent( temp->left, temp->middle ) ;
                }
            }
            else ;

            if ( p == root )  root = temp ;   // set root
            else if ( p == p->parent->right ) { // set parent pointer
                    temp->parent = p->parent ;
                    p->parent->right = temp ;
            }
            else if ( p == p->parent->middle ) {
                    temp->parent = p->parent ;
                    p->parent->middle = temp ;
            }
            else if ( p == p->parent->left ) {
                    temp->parent = p->parent ;
                    p->parent->left = temp ;
            }
            else ;

            split( temp ) ; // because temp have three data
          }
          else ;

      }

  }

  void Create23tree( School * temptype ){ // create 23tree
      if ( root == NULL ){ // set root->data[0]
          root = new TreePtr ;
          newTreePtr( root ) ;
          copySchoolData( root->data[0], temptype ) ; // put temp type into root's data[0]
          root->dataIsFall = false ;
      }
      else{
          TreePtr * follow = root ;
          follow = findCurrentLeaf( follow, temptype ) ; // Insert and find node's location
          if ( follow == NULL ) return ; // node which I find and node which is done have same school name except follow
          else {
              if ( follow->dataIsFall == false ){ // follow has only one data
                  if ( temptype->schoolName == follow->data[0]->schoolName ){
                      sameSchool( follow->data[0], temptype ) ;
                      return ;
                  }
                  compareTreePtrKey_put( follow, temptype,  follow->data[0] ) ; // compare two data and sort
              }
              else if ( follow->dataIsFall == true ){

                  TreePtr * tempForSplit = new TreePtr ; // new tree pointer
                  setTreePtrNull( tempForSplit ) ;
                  //tempForSplit->dataIsFall = false ;
                  if ( temptype->schoolName == follow->data[0]->schoolName ){
                      sameSchool( follow->data[0], temptype ) ;
                      return ;
                  }
                  if ( temptype->schoolName == follow->data[1]->schoolName ){
                      sameSchool( follow->data[1], temptype ) ;
                      return ;
                  }
                  compareTempPtrKey_put( tempForSplit, follow->data[0], follow->data[1], temptype ) ; // compare three data and sort, then put into tempForSplit

                  tempForSplit->parent = follow->parent ; // let tempForSplit replace with follow
                  if ( follow->parent == NULL ) ;
                  else if ( follow == follow->parent->right ) {
                        follow->parent->right = NULL ;
                        follow->parent->right = tempForSplit ;
                  }
                  else if ( follow == follow->parent->left ) {
                        follow->parent->left = NULL ;
                        follow->parent->left = tempForSplit ;
                  }
                  else if ( follow == follow->parent->middle ) {
                        follow->parent->middle = NULL ;
                        follow->parent->middle = tempForSplit ;
                  }
                  else ;

                  split( tempForSplit ) ;
              }
              else ;
          }
      }
  }

  int treeHeight( AVLtreePtr * node ) {
     if (node == NULL) return 0;

     int left = treeHeight(node->left);
     int right = treeHeight(node->right);

     return 1 + max(left, right);
  }

  void setAVLtreeNULL( AVLtreePtr * x ){
      x->data = new School ;
      x->left = NULL ;
      x->right = NULL ;
      x->parent = NULL ;
  }

  void sameType( School * school, School * temptype ){
      if ( school->same == NULL ){
        school->same = new School ;
        copySchoolData( school->same, temptype ) ;
      }
      else{
        sameType( school->same, temptype ) ;
      }
  }

  AVLtreePtr * Insert( AVLtreePtr * follow , School * temptype ){
      if ( temptype->typeName > follow->data->typeName ){
          if ( follow->right == NULL ){
              follow->right = new AVLtreePtr ;
              setAVLtreeNULL( follow->right ) ;
              follow->right->parent = follow ;
              copySchoolData( follow->right->data, temptype ) ;
              return follow ;
          }
          else Insert( follow->right, temptype ) ;
      }
      else if ( temptype->typeName < follow->data->typeName ){
          if ( follow->left == NULL ){
              follow->left = new AVLtreePtr ;
              setAVLtreeNULL( follow->left ) ;
              follow->left->parent = follow ;
              copySchoolData( follow->left->data, temptype ) ;
              return follow ;
          }
          else Insert( follow->left, temptype ) ;
      }
      else if ( temptype->typeName == follow->data->typeName ) {
          sameType( follow->data, temptype );
          return NULL ;
      }
      else ;
  }

  AVLtreePtr * FindRotate( AVLtreePtr * follow ){
    if ( follow == AVLroot ){
        if ( treeHeight(follow->left) - treeHeight(follow->right) == 2
          ||  treeHeight(follow->left) - treeHeight(follow->right) == -2 ){
              return follow ;
          }
        else
            return NULL ;
    }
    else if ( treeHeight(follow->left) - treeHeight(follow->right) == 2
        ||  treeHeight(follow->left) - treeHeight(follow->right) == -2 ){
            return follow ;
        }
    else {
        FindRotate( follow->parent ) ;
    }
  }

  AVLtreePtr * rotateLL( AVLtreePtr * x ){
      AVLtreePtr * y = x->left ;
      x->left = y->right ;
      if ( x->left != NULL ) x->left->parent = x ;
      y->right = x ;
      x->parent = y ;
      return y ;
  }

  AVLtreePtr * rotateRR( AVLtreePtr * x ){
      AVLtreePtr * y = x->right ;
      x->right = y->left ;
      if ( x->right != NULL ) x->right->parent = x ;
      y->left = x ;
      x->parent = y ;
      return y ;
  }

  AVLtreePtr * rotateLR( AVLtreePtr * x ){
      x->left = rotateRR( x->left ) ;
      return rotateLL( x );
  }

  AVLtreePtr * rotateRL( AVLtreePtr * x ){
      x->right = rotateLL( x->right ) ;
      return rotateRR( x );
  }

  void CreateAVLtree( School * temptype ){
    if ( AVLroot == NULL ){ // set AVLroot data
        AVLroot = new AVLtreePtr ;
        setAVLtreeNULL( AVLroot ) ;
        copySchoolData( AVLroot->data, temptype ) ;
    }
    else{
        AVLtreePtr * temp = NULL ;
        AVLtreePtr * follow = AVLroot ;
        bool isRight = false ;
        follow = Insert( follow, temptype ) ; // Insert
        if ( follow == NULL ) // same typeName
            return ;
        follow = FindRotate( follow ) ; // follow needs to rotate
        if ( follow == NULL )
            return ;


        if ( treeHeight( follow->left ) - treeHeight( follow->right ) == 2 ){ // follow node's balance factor is 2
            AVLtreePtr * templeft = follow->left ;
            if ( treeHeight( templeft->left ) - treeHeight( templeft->right ) == 0 ||
                 treeHeight( templeft->left ) - treeHeight( templeft->right ) == 1 ){ // follow->left node's balance factor is 0 or 1, LL
                if ( follow == AVLroot ){
                    AVLroot = rotateLL( AVLroot ) ;
                    AVLroot->parent = NULL ;
                }
                else{
                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateLL( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;
                }
            }
            else if ( treeHeight( templeft->left ) - treeHeight( templeft->right ) == -1 ){ // LR
                if ( follow == AVLroot ){
                    AVLroot = rotateLR( AVLroot ) ;
                    AVLroot->parent = NULL ;
                }
                else{

                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateLR( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;

                }
                //double rotation
            }
            else ;
        }
        else if ( treeHeight( follow->left ) - treeHeight( follow->right ) == -2 ){ //follow node's balance factor is -2
            AVLtreePtr * tempright = follow->right ;
            if ( treeHeight( tempright->left ) - treeHeight( tempright->right ) == 0 ||
                 treeHeight( tempright->left ) - treeHeight( tempright->right ) == -1 ){ // follow->right node's balance factor is 0 or -1, RR
                if ( follow == AVLroot )
                    AVLroot = rotateRR( AVLroot ) ;
                else{
                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateRR( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;

                }
            }
            else if (  treeHeight( tempright->left ) - treeHeight( tempright->right ) == 1 ){ // RL
                if ( follow == AVLroot )
                    AVLroot = rotateRL( AVLroot ) ;
                else{
                    temp = follow->parent ;
                    if ( follow == temp->right ) isRight = true ;
                    follow = rotateRL( follow ) ;
                    follow->parent = temp ;
                    if ( isRight ) temp->right = follow ;
                    else           temp->left = follow ;
                }
                //double rotation
            }
            else;
        }
        else ;
    }

  }

  void search_AVL(){
      ;
  }

  void search_23tree(){

  }

  void print_all( string fileName ){
      ifstream tempin ;
      tempin.open( fileName.c_str() ) ;

      string raw ;
      getline( tempin, raw ) ;
      getline( tempin, raw ) ;
      getline( tempin, raw ) ;
      for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              cout << gnum+1 << ". [" << gnum+1 << "] " << arr[1] << ", " << arr[3] ;
              cout << ", " << arr[4] << ", " << arr[5] << ", " << arr[6] << "\n" ;

      }
      tempin.close() ;
  }

  bool search23( TreePtr * temp, string search_school ){
      School * ttt = NULL ;
      int total = 1 ;
      if ( temp == NULL ) ;
      else if ( temp->dataIsFall == false ){
          if ( temp->data[0]->schoolName == search_school ){
              cout << total << ". [" << temp->data[0]->id << "] " << temp->data[0]->schoolName << ", " ;
              cout << temp->data[0]->typeName << ", " << temp->data[0]->sunNight << ", " << temp->data[0]->level << ", " << temp->data[0]->stuNum << "\n" ;
              ttt = temp->data[0]->same ;
              while ( ttt != NULL ){
                  cout << total << ". [" << ttt->id << "] " << ttt->schoolName << ", " ;
                  cout << ttt->typeName << ", " << ttt->sunNight << ", " << ttt->level << ", " << ttt->stuNum << "\n" ;
                  ttt = ttt->same ;
                  total++ ;
              }
              return true ;
          }
          else{
              search23( temp->right, search_school );
              search23( temp->left, search_school ) ;
          }
      }
      else if ( temp->dataIsFall == true ){
          if ( temp->data[0]->schoolName == search_school ){
              cout << total << ". [" << temp->data[0]->id << "] " << temp->data[0]->schoolName << ", " ;
              cout << temp->data[0]->typeName << ", " << temp->data[0]->sunNight << ", " << temp->data[0]->level << ", " << temp->data[0]->stuNum << "\n" ;
              ttt = temp->data[0]->same ;
              int total = 1 ;
              while ( ttt != NULL ){
                  cout << total << ". [" << ttt->id << "] " << ttt->schoolName << ", " ;
                  cout << ttt->typeName << ", " << ttt->sunNight << ", " << ttt->level << ", " << ttt->stuNum << "\n" ;
                  ttt = ttt->same ;
                  total++ ;
              }
              return true ;
          }
          else if ( temp->data[1]->schoolName == search_school ){
              cout << total << ". [" << temp->data[1]->id << "] " << temp->data[1]->schoolName << ", " ;
              cout << temp->data[1]->typeName << ", " << temp->data[1]->sunNight << ", " << temp->data[1]->level << ", " << temp->data[1]->stuNum << "\n" ;
              ttt = temp->data[1]->same ;
              int total = 1 ;
              while ( ttt != NULL ){
                  cout << total << ". [" << ttt->id << "] " << ttt->schoolName << ", " ;
                  cout << ttt->typeName << ", " << ttt->sunNight << ", " << ttt->level << ", " << ttt->stuNum << "\n" ;
                  ttt = ttt->same ;
                  total++ ;
              }
              return true ;
          }
          else{
              search23( temp->right, search_school );
              search23( temp->middle, search_school );
              search23( temp->left, search_school );
          }
      }
  }

  void print_school( string search_school ){
      bool haha = search23( root, search_school );
  }

  bool searchAVL( AVLtreePtr * temp, string search_type ){
      School * ttt = NULL ;
      int total = 1 ;
      if ( temp == NULL ) ;
      else if ( temp->data->typeName == search_type ){
          cout << total << ". [" << temp->data->id << "] " << temp->data->schoolName << ", " ;
          cout << temp->data->typeName << ", " << temp->data->sunNight << ", " << temp->data->level << ", " << temp->data->stuNum << "\n" ;
          ttt = temp->data->same ;
          while ( ttt != NULL ){
              cout << total << ". [" << ttt->id << "] " << ttt->schoolName << ", " ;
              cout << ttt->typeName << ", " << ttt->sunNight << ", " << ttt->level << ", " << ttt->stuNum << "\n" ;
              ttt = ttt->same ;
              total++ ;
          }
          return true ;
      }
      else{
          searchAVL( temp->right, search_type ) ;
          searchAVL( temp->left, search_type ) ;
      }
  }

  void print_type( string search_type ){
      bool haha = searchAVL( AVLroot, search_type ) ;
  }

  void print_school_type( string fileName, string search_school, string search_type ){
      ifstream tempin ;
      tempin.open( fileName.c_str() ) ;

      string raw ;
      getline( tempin, raw ) ;
      getline( tempin, raw ) ;
      getline( tempin, raw ) ;
      for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              if ( search_school ==  arr[1] && search_type == arr[3] ){
                  cout << arr[1] << ", " << arr[3] ;
                  cout << ", " << arr[4] << ", " << arr[5] << ", " << arr[6] << "\n" ;
              }


      }
      tempin.close() ;
  }

  void intersection_query( string fileName ){

      string search_school = "", search_type = "" ;

      cout << "search school : " ;
      cin >> search_school ;
      cout << "\n" ;

      cout << "search type : " ;
      cin >> search_type ;
      cout << "\n" ;

      if ( search_school == "*" && search_type == "*" ){
          print_all( fileName ) ;
      }
      else if ( search_school != "*" && search_type == "*" ){
          print_school( search_school ) ;
      }
      else if ( search_school == "*" && search_type != "*" ){
          print_type( search_type ) ;
      }
      else if ( search_school != "*" && search_type != "*" ){
          print_school_type( fileName, search_school, search_type ) ;
      }
      else ;
  }

  public : void Mission(){
    School * temptype  = new School ;
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
        tempin.open( fileName.c_str() );
        if ( ! tempin.is_open() ){
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
            printf( "Input 201, 202, ...[0]Quit):" ) ;
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
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype->id = gnum+1 ;
              temptype->schoolName = arr[1] ;
              temptype->typeName = arr[3] ;
              temptype->sunNight = arr[4] ;
              temptype->level = arr[5] ;
              temptype->stuNum = atoi( arr[6].c_str() ) ;
              if ( arr[6].size() > 3 ){
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), ','));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
              }
              temptype->same = NULL ;

              Create23tree( temptype ) ;
              CreateAVLtree( temptype ) ;

           } // for read
           tempin.close() ;
           intersection_query( fileName ) ;

           root = NULL ;
           AVLroot = NULL ;

      } //if end

    } //while

  } // Mission1

};

void PrintMenu(){
    cout << endl << "*** Search Tree Utilities **";
    cout << endl << "* 0. QUIT                  *";
    cout << endl << "* 1. Build 2-3 tree        *";
    cout << endl << "* 2. Build AVL tree        *";
    cout << endl << "*************************************";
    cout << endl << "Input a choice(0, 1, 2): ";

} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission1 miss1 ;
    Mission2 miss2 ;
    Mission3 miss3 ;
    bool miss1done = false, miss2done = false ;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 ){
        miss1.Mission() ;
        miss1done = true ;
      }
      else if ( mission == 2 ){
        miss2.Mission() ;
        miss2done = true ;
      }
      else if ( mission == 3 ){
        if ( miss1done == true && miss2done == true )
          miss3.Mission();
        else
          cout << "do 1 and 2 \n " ;
        miss1done = false ;
        miss2done = false ;
      }

      else if ( mission > 2 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;


      PrintMenu() ;
      gnum = 0 ;
      cin >> mission ;
    } // while end
}

