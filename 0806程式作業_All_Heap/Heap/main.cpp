
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

using namespace std ;

typedef struct School {
  int id ;
  int score ;
} ; // School

class Mission{

  public:

  vector<School> max_heap, minmax_heap, deap, temp ;

  void Build_maxHeap(){
      /*
      max_heap 是用陣列表示的樹
      temp 將會一個一個把值丟入max_heap這棵樹
      bottom指的是 當下插入的第幾個
      place 是讓每一次在尋找的時候，指到插入的位址
      parent 就是place的父母
      */
      for ( int bottom = 0 ; temp.size() > bottom ; bottom++ ){
          max_heap.push_back( temp[bottom] ) ; // 將值丟入max_heap
          int place = bottom ;                 // 讓place回到插入的值
          int parent = ( place - 1 ) / 2 ;     // parent的位址
          if ( parent >= 0 ){                  // 所指向的位置有 parent 就需要檢查要不要調換位置
              while( parent >= 0 && max_heap[place].score > max_heap[parent].score ){ // 目前位置的 score > 此 parent 的 score
                  swap( max_heap[place].score, max_heap[parent].score ) ; // 就調換
                  swap( max_heap[place].id, max_heap[parent].id ) ;
                  place = parent ;                                        // place 變成原本的 parent
                  parent = ( place - 1 ) / 2 ;                            // 重新定義 parent
              } // while
          }
      }

      for(int j = 0; j < max_heap.size(); j++){
          cout << "[" << j << "] (" << max_heap[j].score << "," << max_heap[j].id << ")" << endl;
      }
      temp.clear() ;
      max_heap.clear() ;
  }

  void Mission1(){ // 將讀進來的值先存進temp裡
      School tempSchool;
      int score;
      cout << "input[0, 100]:";
      for(int j = 0; 1 ; j++){
          cin >> score;
          tempSchool.id = j+1;
          tempSchool.score = score;
          temp.push_back(tempSchool);
          if (cin.get() == '\n') break;
      }
      Build_maxHeap() ;

  } // Mission1

  void Build_minmax(){
      /*
      minmax_heap 是用陣列表示的樹
      temp 將會一個一個把值丟入minmax_heap這棵樹
      bottom指的是 當下插入的第幾個
      place 是讓每一次在尋找的時候，指到插入的位址
      parent 就是place的父母

      now_min 表示現在正在min層
      changeLine 為true 表示我下一個進來的值將會進入到樹的下一層，也就表示要是上一行在MIN層, 下一行就到MAX層, 反之亦然
      rightNum 是表示我留住上一層最右邊的數字，來做計算
      */
      bool changeline = false, now_min = false ;
      int rightNum = 0, temp2 = 0 ;
      for ( int bottom = 0 ; temp.size() > bottom ; bottom++ ){
          minmax_heap.push_back( temp[bottom] ) ;
          int place = bottom ;
          int parent = ( place - 1 ) / 2 ;

          if ( place == 1 && minmax_heap[place].score < minmax_heap[0].score ){ // 要是是第2個丟入的，而且第二個比正在min層的第1個小
              swap( minmax_heap[place].score, minmax_heap[0].score ) ;          // 就要交換
              swap( minmax_heap[place].id, minmax_heap[0].id ) ;
              continue ;
          }

          if ( rightNum == (place-2)/2 && (place-2)%2 == 0 ) changeline = true ;  // 判斷是否ChangeLine EX : right = 2, place = 6

          if ( parent > 0 ){          // 所指向的位置有 parent 就需要檢查要不要調換位置
              if ( now_min == true ){ // 要是現在在min層
                  if ( minmax_heap[place].score > minmax_heap[parent].score ){       //要是目前值比父母大
                      swap( minmax_heap[place].score, minmax_heap[parent].score ) ;  //與父母交換
                      swap( minmax_heap[place].id, minmax_heap[parent].id ) ;
                      place = parent ;             // place 表示 目前的 parent, 也就表示到了max層
                      temp2 = ( place - 1 ) / 2 ;  // temp2是place 的 parent
                      if ( temp2 <= 0 ) continue ; // 要是temp2沒有父母了, 就結束, 插入下一個

                      parent = ( temp2 - 1 ) / 2 ; // parent是temp2 的 parent, 所以parent其實是place 的 grandparent, place和parent都在max層
                      while( parent >= 0 && minmax_heap[place].score > minmax_heap[parent].score ){ // 判斷是否能在max層一直往上交換
                              swap( minmax_heap[place].score, minmax_heap[parent].score ) ;
                              swap( minmax_heap[place].id, minmax_heap[parent].id ) ;
                              place = parent ;
                              temp2 = ( place - 1 ) / 2 ;
                              if ( temp2 <= 0 ) break ;    //  因為在min層，所以temp2能是0
                              parent = ( temp2 - 1 ) / 2 ;
                      } // while

                      // change and max continue
                  }
                  else{ //要是目前值比父母小
                      temp2 = parent ;  // temp2是place 的 parent
                      if ( temp2 <= 0 ) continue ; // 要是temp2沒有父母了, 就結束, 插入下一個

                      parent = ( temp2 - 1 ) / 2 ; // parent是temp2 的 parent, 所以parent其實是place 的 grandparent, place和parent都在min層
                      while( parent >= 0 && minmax_heap[place].score < minmax_heap[parent].score ){ // 判斷是否能在min層一直往上交換
                              swap( minmax_heap[place].score, minmax_heap[parent].score ) ;
                              swap( minmax_heap[place].id, minmax_heap[parent].id ) ;
                              place = parent ;
                              temp2 = ( place - 1 ) / 2 ;
                              if ( temp2 < 0 ) break ;    //  因為在max層，所以temp2不能是0
                              parent = ( temp2 - 1 ) / 2 ;
                      } // while

                      // min continue
                  }
              }
              else if ( now_min == false ){ // 要是現在在max層
                  if ( minmax_heap[place].score < minmax_heap[parent].score ){ // 要是目前值比父母小
                      swap( minmax_heap[place].score, minmax_heap[parent].score ) ; // 交換
                      swap( minmax_heap[place].id, minmax_heap[parent].id ) ;
                      place = parent ;                                     // place 表示 目前的 parent, 也就表示到了min層
                      temp2 = ( place - 1 ) / 2 ;
                      if ( temp2 <= 0 ) continue ; // 要是temp2沒有父母了, 就結束, 插入下一個

                      parent = ( temp2 - 1 ) / 2 ;
                      while( parent >= 0 && minmax_heap[place].score < minmax_heap[parent].score ){ // 判斷是否能在min層一直往上交換
                              swap( minmax_heap[place].score, minmax_heap[parent].score ) ;
                              swap( minmax_heap[place].id, minmax_heap[parent].id ) ;
                              place = parent ;
                              temp2 = ( place - 1 ) / 2 ;
                              if ( temp2 < 0 ) break ;  //  因為在max層，所以temp2不能是0
                              parent = ( temp2 - 1 ) / 2 ;
                      } // while
                      // change and min continue
                  }
                  else{  //要是目前值比父母大
                      temp2 = parent ; // temp2是place 的 parent
                      if ( temp2 <= 0 ) continue ;

                      parent = ( temp2 - 1 ) / 2 ;
                      while( parent >= 0 && minmax_heap[place].score > minmax_heap[parent].score ){
                              swap( minmax_heap[place].score, minmax_heap[parent].score ) ;
                              swap( minmax_heap[place].id, minmax_heap[parent].id ) ;
                              place = parent ;
                              temp2 = ( place - 1 ) / 2 ;
                              if ( temp2 <= 0 ) break ;    //  因為在min層，所以temp2能是0
                              parent = ( temp2 - 1 ) / 2 ;
                      } // while
                      // max continue
                  }
              }
          }

          if ( changeline == true ){ // 要是我 change line
              rightNum = bottom ;    // 留住right number 方便我之後判斷是否change line

              if ( now_min == true )       now_min = false ;  // min層 變 max層
              else if ( now_min == false ) now_min = true ;   // max層 變 min層

              if(rightNum == 2 && minmax_heap[0].score > minmax_heap[2].score ){
                  // 因為當right number是2時判斷不到 ，所以要是right number 是2 然後此score 比 root 的 score 還小，要換
                  swap( minmax_heap[0].score, minmax_heap[2].score ) ;
                  swap( minmax_heap[0].id, minmax_heap[2].id ) ;
              }
              changeline = false ;
          }
      }

      for(int j = 0; j < minmax_heap.size(); j++){
          cout << "[" << j << "] (" << minmax_heap[j].score << "," << minmax_heap[j].id << ")" << endl;
      }

      temp.clear() ;
      minmax_heap.clear() ;
  }

  void Mission2(){
      School tempSchool;
      int score;
      cout << "input[0, 100]:";
      for(int j = 0; 1 ; j++){
          cin >> score;
          tempSchool.id = j+1;
          tempSchool.score = score;
          temp.push_back(tempSchool);
          if (cin.get() == '\n') break;
      }
      Build_minmax();
  }

  void Build_deap(){
      /*
      deap 是用陣列表示的樹
      temp 將會一個一個把值丟入deap這棵樹
      bottom指的是 當下插入的第幾個
      place 是讓每一次在尋找的時候，指到插入的位址
      parent 就是place的父母


      changeLine 為true 表示我下一個進來的值將會進入到樹的下一層
      rightNum  是表示我留住上一層最右邊的數字，來做計算
      interval  是表示此層要從左邊跳到右邊需要跳幾格
      hor_route 是表示是此層的從左數過來第幾個
      */
      bool changeline = false ;
      int rightNum = 0, interval = 1, hor_route = 0 ;
      for ( int bottom = 0 ; temp.size() > bottom ; bottom++, hor_route++ ){
          deap.push_back( temp[bottom] ) ;
          int place = bottom ;
          int parent = ( place - 1 ) / 2 ;
          if ( rightNum == (place-2)/2 && (place-2)%2 == 0 ) changeline = true ;  // 判斷是否ChangeLine EX : right = 2, place = 6

          if ( parent > 0 ){
              if ( hor_route < interval ){ // 目前在左邊 也就是min區
                    if ( deap[place].score > deap[ (place+interval-1)/2 ].score ){ // 進來的數大於對應點的父母時
                          swap( deap[place].score, deap[ (place+interval-1)/2 ].score ) ; // 跟對應點的父母換
                          swap( deap[place].id, deap[ (place+interval-1)/2 ].id ) ;
                          place = (place+interval-1)/2 ;
                          parent = ( place - 1 ) / 2 ;
                          while( parent > 0 && deap[place].score > deap[parent].score ){ // 並且一直往上比 更大就要換
                              swap( deap[place].score, deap[parent].score ) ;
                              swap( deap[place].id, deap[parent].id ) ;
                              place = parent ;
                              parent = ( place - 1 ) / 2 ;
                          } // while
                    }
                    else{                 // 進來的數小於對應點的父母時
                        while( parent > 0 && deap[place].score < deap[parent].score ){ // 那就不用換 但還是要往上比 更小就要換
                          swap( deap[place].score, deap[parent].score ) ;
                          swap( deap[place].id, deap[parent].id ) ;
                          place = parent ;
                          parent = ( place - 1 ) / 2 ;
                        } // while
                    }

              } // if
              else if ( hor_route >= interval ){ // 目前在右邊 也就是max區
                  if ( deap[place].score < deap[place-interval].score ){ // 進來的數小於對應點的父母時
                      swap( deap[place].score, deap[place-interval].score ) ; // 跟對應點的父母換
                      swap( deap[place].id, deap[place-interval].id ) ;
                      place = place - interval ;
                      parent = ( place - 1 ) / 2 ;
                      while( parent > 0 && deap[place].score < deap[parent].score ){ // 並且一直往上比 更小就要換
                          swap( deap[place].score, deap[parent].score ) ;
                          swap( deap[place].id, deap[parent].id ) ;
                          place = parent ;
                          parent = ( place - 1 ) / 2 ;
                      } // while
                  } // if
                  else{  // 進來的數大於對應點的父母時
                      while( parent > 0 && deap[place].score > deap[parent].score ){ // 那就不用換 但還是要往上比 更大就要換
                          swap( deap[place].score, deap[parent].score ) ;
                          swap( deap[place].id, deap[parent].id ) ;
                          place = parent ;
                          parent = ( place - 1 ) / 2 ;
                      } // while
                  }


              } // else if
          }

          if ( changeline == true ){
              rightNum = bottom ;
              if(rightNum == 2 && deap[1].score > deap[2].score ){
                  swap( deap[1].score, deap[2].score ) ;
                  swap( deap[1].id, deap[2].id ) ;
              }
              interval = interval * 2 ; // 因為每一層的數量都會增加兩倍，對應點所差的距離也會是兩倍
              hor_route = -1 ;          // 每一層就更新，所以從下一個就從0開始
              changeline = false ;
          }
      }

      for(int j = 0; j < deap.size(); j++){
          if ( deap[j].id == -1 ) cout << "[" << j << "] ( , )" << endl;
          else cout << "[" << j << "] (" << deap[j].score << "," << deap[j].id << ")" << endl;
      }

      temp.clear() ;
      deap.clear() ;
  }

  void Mission3(){
      School tempSchool;
      int score;
      tempSchool.id = -1;
      tempSchool.score = -1;
      temp.push_back(tempSchool);
      cout << "input[0, 100]:";
      for(int j = 0; 1 ; j++){
          cin >> score;
          tempSchool.id = j+1;
          tempSchool.score = score;
          temp.push_back(tempSchool);
          if (cin.get() == '\n') break;
      }
      Build_deap();
  }

};

void PrintMenu(){
    cout << endl << "**** Heap Construction *****";
    cout << endl << "* 0. QUIT                  *";
    cout << endl << "* 1. Build a max heap      *";
    cout << endl << "* 1. Build a min max heap  *";
    cout << endl << "* 3. Build a DEAP          *";
    cout << endl << "****************************";
    cout << endl << "Input a choice(0, 1, 2, 3): ";
} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission miss ;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )      miss.Mission1() ;
      else if ( mission == 2 ) miss.Mission2() ;
      else if ( mission == 3 ) miss.Mission3() ;
      else if ( mission > 3 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      cin >> mission ;
    } // while end
}

