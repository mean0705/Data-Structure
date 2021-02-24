#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ctime>

using namespace std ;

int gNumPtr = 1 ;
int cT = 0 ;
struct NumPtr {
  float coefficient ;
  int index ;
  NumPtr * next;
} ;

class Mission{

    public:

    NumPtr * Combinne( NumPtr * funct ){
        funct = NULL;
        NumPtr * tempPtr = NULL;
        NumPtr * temp2 = NULL;
        NumPtr * tempHead = NULL;

        char symbol;
        float temp_coefficient = 0;
        int cur_index = 0, temp_index = 0;

        while(1){ // scan
            if (funct == NULL){  // 如果FUNCT1是NULL那就創立一個新的節點並將讀入的資料放進節點中
                cin >> symbol ; // (
                cin >> temp_coefficient;
                cin >> symbol; // ,
                cin >> temp_index;
                funct = new NumPtr;
                funct->coefficient = temp_coefficient;
                funct->index = temp_index;
                funct->next = NULL;
                tempPtr = funct;
                cur_index = funct->index; // 設置了一個現在的index以便插入時使用
            }
            else{
                cin >> symbol ; // (
                cin >> temp_coefficient;
                cin >> symbol; // ,
                cin >> temp_index;
                if ( temp_index > cur_index && tempPtr == funct ){ // 若讀入該筆資料的指數大於我原本串列裡的最大指數
                    tempHead = new NumPtr;                             // 新增一個新的頭且新增一個結點
                    tempHead->coefficient = temp_coefficient;       // 並將資料放入節點中
                    tempHead->index = temp_index;
                    tempHead->next = funct;                        // 並將後面接起來
                    funct = tempHead;
                    tempHead = NULL;
                }
                else if (temp_index == cur_index ){                 // 若指數相等，那就底數相加即可
                    tempPtr->coefficient = tempPtr->coefficient + temp_coefficient;
                }
                else if (temp_index < cur_index ){                  // 若讀入的指數比該串列的最大指數還小
                    temp2 = tempPtr;
                    if ( tempPtr->next != NULL ) tempPtr = tempPtr->next;
                    while( tempPtr != NULL ){                       // 那就往後找
                        cur_index = tempPtr->index;
                        if ( temp_index > cur_index ){              // 往後找，若找到讀入的指數比該指數大
                            temp2->next = NULL;                     // 那就插入
                            temp2->next = new NumPtr;
                            temp2 = temp2->next;
                            temp2->coefficient = temp_coefficient;
                            temp2->index = temp_index;
                            temp2->next = tempPtr;
                            break;
                        }
                        else if (temp_index == cur_index ){         // 相等相加即可
                            tempPtr->coefficient = tempPtr->coefficient + temp_coefficient;
                            break;
                        }
                        temp2 = tempPtr;
                        tempPtr = tempPtr->next;
                    }

                    if (tempPtr == NULL){                          // 若甚麼都沒找到，插到最後面
                        temp2->next = new NumPtr;
                        temp2 = temp2->next;
                        temp2->coefficient = temp_coefficient;
                        temp2->index = temp_index;
                        temp2->next = NULL;
                    }
                }
            }
            cin >> symbol; // )
            if ( cin.get() == '\n' ) break;

            tempPtr = funct;
            cur_index = funct->index; //設置了一個現在的index以便插入時使用
        } // while

        return funct;
    }

    void PrintFunction( NumPtr * funct ){
        NumPtr * tempPtr = funct;
        cout << "Answer is :  ";
        for (tempPtr = funct; tempPtr != NULL; tempPtr = tempPtr -> next){ // 印出答案
            if (tempPtr == funct) {
                if (tempPtr->coefficient == 1)  cout << "x^" << tempPtr->index;
                else if ( tempPtr->index == 1 ) cout  << tempPtr->coefficient << "x";
                else if ( tempPtr->index == 0 ) cout  << tempPtr->coefficient;
                else cout << tempPtr->coefficient << "x^" << tempPtr->index;
            }
            else if ( tempPtr->coefficient > 0 ) {
                if (tempPtr->coefficient == 1)  cout << "+x^" << tempPtr->index;
                else if ( tempPtr->index == 1 ) cout << "+" << tempPtr->coefficient << "x";
                else if ( tempPtr->index == 0 ) cout << "+" << tempPtr->coefficient;
                else cout << "+" << tempPtr->coefficient << "x^" << tempPtr->index;
            }
            else if ( tempPtr->coefficient < 0 ) {
                if ( tempPtr->index == 1 )      cout  << tempPtr->coefficient << "x";
                else if ( tempPtr->index == 0 ) cout  << tempPtr->coefficient;
                else cout << tempPtr->coefficient << "x^" << tempPtr->index;
            }
            else cout << ""; // 如果相加的底數為0就不用輸出了
        }
        cout << endl;
    }

    void Mission1(){
        cout << "When you input your function ,if you want to get 2x^3, input (2,3), and next, you need to input ',' to separate.\n";
        cout << "Like : (2,3),(1,2),(4.5,7)\n\n";
        cout << "Input your function : ";
        NumPtr * funct1 = Combinne(funct1);
        PrintFunction(funct1);
    } // Mission1

    NumPtr * AddTwoFunct( NumPtr * funct1, NumPtr * funct2 ){ // 把function2的一筆一筆資料讀入並合成到function1裡
        NumPtr * tempPtr1 = funct1;
        NumPtr * tempPtr2 = funct2;
        NumPtr * tempHead = NULL;
        NumPtr * temp = NULL;

        while( tempPtr2 != NULL ){
            if ( tempPtr2->index > tempPtr1->index ){
                tempHead = new NumPtr;                             // 新增一個新的頭且新增一個結點
                tempHead->coefficient = tempPtr2->coefficient;       // 並將資料放入節點中
                tempHead->index = tempPtr2->index;
                tempHead->next = tempPtr1;                        // 並將後面接起來
                tempPtr1 = tempHead;
                funct1 = tempHead;
                tempHead = NULL;
            }
            else if ( tempPtr2->index == tempPtr1->index ){
                tempPtr1->coefficient = tempPtr1->coefficient + tempPtr2->coefficient;
            }
            else if ( tempPtr2->index < tempPtr1->index ){
                temp = tempPtr1;
                if ( tempPtr1->next != NULL ) tempPtr1 = tempPtr1->next;
                while( tempPtr1 != NULL ){                           // 那就往後找
                    int cur_index = tempPtr1->index;
                    if ( tempPtr2->index > cur_index ){              // 往後找，若找到讀入的function2的指數比該指數大
                        temp->next = NULL;                           // 那就插入
                        temp->next = new NumPtr;
                        temp = temp->next;
                        temp->coefficient = tempPtr2->coefficient;
                        temp->index = tempPtr2->index;
                        temp->next = tempPtr1;
                        break;
                    }
                    else if (tempPtr2->index == cur_index ){         // 相等相加即可
                        tempPtr1->coefficient = tempPtr1->coefficient + tempPtr2->coefficient;
                        break;
                    }
                    temp = tempPtr1;
                    tempPtr1 = tempPtr1->next;
                }

                if (tempPtr1 == NULL){                          // 若甚麼都沒找到，插到最後面
                    temp->next = new NumPtr;
                    temp = temp->next;
                    temp->coefficient = tempPtr2->coefficient;
                    temp->index = tempPtr2->index;
                    temp->next = NULL;
                }
            }
            else cout << "what??\n";

            tempPtr1 = funct1;
            tempPtr2 = tempPtr2->next;
        }

        return funct1;     // 回傳function1 也就是和 加過的
    }

    void Mission2(){
        cout << "When you input your function ,if you want to get 2x^3, input (2,3), and next, you need to input ',' to separate.\n";
        cout << "Like : (2,3),(1,2),(4.5,7)\n\n";
        cout << "Input your function1 : ";
        NumPtr * funct1 = Combinne(funct1);
        cout << "Input your function2 : ";
        NumPtr * funct2 = Combinne(funct2); // 先排好兩個function

        NumPtr * sumFunct = AddTwoFunct(funct1, funct2); //相加 sum Function
        PrintFunction(sumFunct);
    }

    NumPtr * MultiplyTwoFunct( NumPtr * funct1, NumPtr * funct2 ){
        NumPtr * Product = NULL;  // 新增一個 product pointer 將互相乘起來的數值放進去
        NumPtr * tempPro = NULL;
        for( NumPtr * tempPtr1 = funct1; tempPtr1 != NULL; tempPtr1 = tempPtr1->next ){
            for( NumPtr * tempPtr2 = funct2; tempPtr2 != NULL; tempPtr2 = tempPtr2->next ){
                if (Product == NULL){ // product還沒有東西的話因為tempPro要跟著product，所以要另外寫
                    Product = new NumPtr;
                    Product->coefficient = tempPtr1->coefficient * tempPtr2->coefficient;
                    Product->index = tempPtr1->index + tempPtr2->index;
                    Product->next = NULL;
                    tempPro = Product;
                }
                else{
                    tempPro->next = new NumPtr; // 其他就是一個一個加在後面
                    tempPro = tempPro->next;
                    tempPro->coefficient = tempPtr1->coefficient * tempPtr2->coefficient;
                    tempPro->index = tempPtr1->index + tempPtr2->index;
                    tempPro->next = NULL;
                }
            }
        }

        return Product;
    }

    void Mission3(){
        cout << "When you input your function ,if you want to get 2x^3, input (2,3), and next, you need to input ',' to separate.\n";
        cout << "Like : (2,3),(1,2),(4.5,7)\n\n";
        cout << "Input your function1 : ";
        NumPtr * funct1 = Combinne(funct1);
        cout << "Input your function2 : ";
        NumPtr * funct2 = Combinne(funct2);

        NumPtr * product = MultiplyTwoFunct(funct1, funct2);
        PrintFunction(product);
    }

}; // Mission

void Print(){
    cout << endl << "** Function                           *";
    cout << endl << "* 0. Quit                             *";
    cout << endl << "* 1. Create a function                *";
    cout << endl << "* 2. Add two functions                *";
    cout << endl << "* 3. Multiply two functions           *";
    cout << endl << "***************************************";
    cout << endl << "Input a choice(0, 1, 2, 3): ";

} // PrintMenu()

int main()
{
    Print() ;
    Mission miss;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )
        miss.Mission1() ;
      else if ( mission == 2 )
        miss.Mission2() ;
      else if ( mission == 3 )
        miss.Mission3() ;
      else if ( mission > 3 && mission < 999 )
        printf( "Not Exist!\n" ) ;
      else{
        break ;
      }

      Print() ;
      cin >> mission ;
    } // while end

}

