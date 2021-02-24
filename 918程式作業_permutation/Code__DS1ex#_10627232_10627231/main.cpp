#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime> // clock_t, clock, CLOCKS_PER_SEC

using namespace std ;

int gnum = 1 ;
int cT = 0 ;
struct IntPtr {
  int num ;
  IntPtr * next;
} ; // IntPtr

void Print ( IntPtr * arr ){ // 印出每個排列組合
    printf( "[%d] ", gnum ) ;
    //while ( arr != NULL ) {
    //    printf( "%d. ", arr->num ) ;
    //    arr= arr->next ;
    //}
    gnum++ ;
    printf( "\n" ) ;

} // Print

void Permutation ( IntPtr * arr, int clas, int length, int times ){

  if ( clas == 1 ){
    Print( arr ) ;
  }
  else {
    IntPtr * temp = NULL ;
    IntPtr * trans = NULL ;
    IntPtr * h = NULL ;
    for ( int times = 0 ; times < clas ; times++ ){
        Permutation( arr, clas - 1, length, 0 ) ;
        temp = arr ;

        for ( int x = length - clas + 1 ; x > 0 ; x-- ){
            trans = temp ;
            if ( x != 1 )
              temp = temp->next ;
        } // for 找到我要交換的指標 若clas = 3, length = 3, 就指到第1個
          //                        若clas = 2, length = 3, 就指到第2個
          //                        若clas = 1, length = 3, 就指到第3個


        for ( temp = arr ; temp != NULL ; temp = temp->next ) {
            if ( arr == trans )
                arr = arr->next ;
            else if ( temp->next == trans ){
                h = temp->next->next ;
                temp->next = h ;
            }

            else
                ;
        } // for 除了要交換的指標 其他順著接起來

        trans->next = NULL ;

        for( temp = arr ; temp != NULL ; temp = temp->next ){
            if ( temp->next == NULL ){
                temp->next = trans ;
                temp->next->next = NULL ;
                break ;
            } // if
        } // for 把要交換的指標接到最後



    } // for

  } // else
} //Permutation()

void Mission1(){ // 先把第一個指標創立好
                 // 若clas = 3, 指標為123，若clas = 4,指標為1234, 然後開始排列
    int clas, length ;
    printf( "Input a number : " ) ;
    scanf( "%d", &clas ) ;
    printf( "\n" ) ;
    length = clas ;
    IntPtr * arr = NULL ;
    arr = new IntPtr ;
    arr->next = NULL ;
    IntPtr * temp = arr ;
    for ( int i = 1 ; i <= clas ; i++ ){
        temp->num = i ;
        if ( i != clas ) {
          temp->next = new IntPtr ;
          temp->next->next = NULL ;
          temp = temp->next ;
        } // if
    } // for

    Permutation( arr, clas, length, 0 ) ;
    printf( "Mission1 : %d permutations\n", gnum-1 ) ;
    printf( "L = %d\n", length ) ;
} // Mission1

void Mission2(){ // 先把第一個指標創立好

    int clas, length, nums ;
    bool repeat = false ;
    printf( "Input a number : " ) ;
    scanf( "%d", &length ) ;
    printf( "\n" ) ;
    while( length >= 15 || length <= 1 ){ // 不在指定範圍就重新輸入
      printf( "##It is not in [2,9]##\n" ) ;
      printf( "Input a number : " ) ;
      scanf( "%d", &length ) ;
      printf( "\n" ) ;
    } // while

    clas = length ;
    IntPtr * arr = NULL ;
    arr = new IntPtr ;
    arr->next = NULL ;
    arr->num = -99999 ;
    IntPtr * temp = NULL ;
    IntPtr * arrTail = NULL ;
    for ( int i = 0 ; i < length ; i++ ){ // 每輸入一個數字就放進去
        printf( "Input a number : " ) ;
        scanf( "%d", &nums ) ;
        printf( "\n" ) ;
        //for ( temp = arr ; temp != NULL ; temp = temp->next ){ // 有相同的數字不能放
        //  if ( temp->num == nums ){
        //    printf( "Duplicate! Still need 1 numbers!\n" ) ;
        //    repeat = true ;
        //  } // if end
        //} // for

        if ( repeat == true ){
            i-- ;
            repeat = false ;
            continue ;
        } // if
        else {
          if ( i == 0 ){
            arr->num = nums ;
            arrTail = arr ;
          } // if
          else {
            arrTail->next = new IntPtr ;
            arrTail->next->next = NULL ;
            arrTail->next->num = nums ;
            arrTail = arrTail -> next ;
          } // else

        } // else

    } // for 每輸入一個數字就放進去

    cT = clock(); // start timer
    Permutation( arr, clas, length, 0 ) ;

}// Mission2

void Combination( IntPtr * arr, int clas, int length, int times, int k ) { // 找出所有組合
    if ( clas == 0 ){ // 指到各組合後排列
        Permutation( arr, length, length, 0 ) ;
    }
    else {
        IntPtr * temp = NULL ;
        IntPtr * trans = NULL ;
        IntPtr * head = NULL ;
        IntPtr * tail = NULL ;
        IntPtr * tail2 = NULL ;

        bool IsNine = false ;
        while ( times < k + 1 - length ){ // 每個組合會增加的次數
            head = new IntPtr ;
            head -> next = NULL ;
            tail = head ;
            temp = arr ;
            tail -> num = temp -> num ;
            temp = temp -> next ;

            while ( temp != NULL ) {
              tail->next = new IntPtr ;
              tail->next->next = NULL ;
              tail = tail -> next ;
              tail -> num = temp -> num ;
              temp = temp -> next ;
            } // while 將被改變的arr先存起來

            Combination( arr, clas-1, length, times, k ) ;
            arr = head ;
            temp = arr ;
            for ( int x = length - clas + 1 ; x > 0 ; x-- ){
                trans = temp ;
                if ( x != 1 )
                    temp = temp -> next ;
            } // for 指到要從第幾個開始往後加1

            for ( temp = arr ; temp != NULL ; temp = temp->next ){
                tail2 = temp ;

            } // 找到尾巴指標

            for( trans = trans ; trans != NULL ; trans = trans->next ){
                if ( tail2->num < k ) {
                    trans->num++ ;
                }

            } // for 從指向的指標往後都加1

            times++ ;


        } // while
    } // else
} // Combination()

void Mission3(){ // 先把第一個指標創立好
                 // 若clas = 3, 指標為123，若clas = 4,指標為1234, 然後開始尋找組合
    int clas, length, k ;
    printf( "Input a number : " ) ;
    scanf( "%d", &k ) ;
    printf( "\n" ) ;

    printf( "Input a number : " ) ;
    scanf( "%d", &clas ) ;
    printf( "\n" ) ;
    while( clas >= k + 1 || clas <= 0 ){
      printf( "##It is not in [1,9]##\n" ) ;
      printf( "Input a number : " ) ;
      scanf( "%d", &clas ) ;
      printf( "\n" ) ;
    } // while
    cT = clock(); // start timer
    length = clas ;
    IntPtr * arr = NULL ;
    arr = new IntPtr ;
    arr->next = NULL ;
    IntPtr * temp = arr ;
    for ( int i = 1 ; i <= clas ; i++ ){
        temp->num = i ;
        if ( i != clas ) {
          temp->next = new IntPtr ;
          temp->next->next = NULL ;
          temp = temp->next ;
        } // if
    } // for

    Combination( arr, clas, length, 0, k ) ;


}// Mission3

void PrintMenu(){
    cout << endl << "** Permutation Generator **";
    cout << endl << "* 0. Quit *";
    cout << endl << "* 1. N numbers from 1..N *";
    cout << endl << "* 2. M numbers from input *";
    cout << endl << "* 3. M numbers from 1..9 *";
    cout << endl << "***************************";
    cout << endl << "Input a choice(0, 1, 2, 3): ";

} // PrintMenu()



int main()
{
    PrintMenu() ;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )
        Mission1() ;
      else if ( mission == 2 )
        Mission2() ;
      else if ( mission == 3 )
        Mission3() ;
      else if ( mission > 3 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else{
        break ;
      }

      if ( mission == 2 || mission == 3 ){
        cT = clock() - cT; // stop timer
        printf( "Mission%d : %d permutations\n", mission, gnum-1 ) ;
        cout << "T = " << (float)cT * 1000 / CLOCKS_PER_SEC << " ms" << endl;
      }


      PrintMenu() ;
      gnum = 1 ;
      cin >> mission ;
    } // while end

}

