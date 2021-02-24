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
#include <stack>

using namespace std;

typedef struct Read {

    public:
      char str[20] = "\0" ;
      Read * next;

} ; // Read

class Mission {

    public :
    Read * formula = NULL ;
    Read * post = NULL ;
    Read * temp = NULL ;


    bool IsOper( char ch ){
      if ( ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' )
            return true ;
      else
        return false ;
    } // IsOper

    bool IsBracket( char ch ){
      if ( ch == '(' || ch == ')' )
            return true ;
      else
        return false ;
    }

    bool IsInt( char ch ){
      if ( ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
           ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' )
            return true ;
      else
        return false ;
    } // IsInt

    bool Mission1new(){
        formula = NULL ;
        vector<char> vec ;
        vec.clear() ;
        cout << "Input an infix expression: " ;
        char getch[100] = "\0" ;
        int v = 0, right = 0, left = 0, i = 0, g = 0 ;
        cin >> getch ;
        while( getch[g] != '\n' && getch[g] != '\0'  ){  // 將輸入的字元丟進vector
            if ( getch[g] != ' ' )
              vec.push_back(getch[g]) ;
            g++ ;
        } // while end

        if ( IsOper( vec[0] ) ){
            cout << "Error 3: there is one extra operator\n" ;
            return false ;
        }

        stack<char> brackets ;
        Read * temp = NULL ;
        formula = new Read ;
        temp = formula ;
        temp->next = NULL ;
        while ( v < vec.size() ){
            if ( IsBracket( vec[v] ) ) {
                if ( vec[v] == '(' ){
                    if ( vec[v+1] == ')' ) { // 要事前一個是左括號後一個馬上就是右括號 error
                      cout << "Error 3: there is one extra operator\n" ;
                      return false ;
                    }
                    left++ ;
                    brackets.push( vec[v] ) ;
                } // if end



                if ( vec[v] == ')' ) {
                    right++ ;

                    if ( brackets.empty() ){ // stack裡沒有東西 卻丟進stack
                        cout << "Error 2: there is one extra close parenthesis\n" ;
                        return false ;
                    }
                    else if ( IsInt( vec[v+1] ) ){ // 前一個是右括號下一個不能是數字
                        cout << "Error 3: there is one extra operand.\n" ;
                        return false ;
                    }
                    else if ( brackets.top() == '(' )
                        brackets.pop() ;

                } // if end

                temp -> str[i] = vec[v] ;

                if ( v != vec.size() - 1 ){
                    temp -> next = new Read ;
                    temp->next->next = NULL ;
                    temp = temp -> next ;
                }

                v++ ;
            } // if end

            else if ( IsOper( vec[v] ) ) {
                temp -> str[i] = vec[v] ;
                if ( ! IsInt( vec[v-1] ) && vec[v-1] != ')' ){ // 運算符號進來前一個不是數字或不是)都錯
                    cout << "Error 3: there is one extra operator\n" ;
                    return false ;
                }


                if ( IsOper ( vec[v+1] ) ){
                    cout << "Error 3: there is one extra operator\n" ;
                    return false ;
                }

                if ( v != vec.size() - 1 ){
                    temp -> next = new Read ;
                    temp->next->next = NULL ;
                    temp = temp -> next ;
                }

                v++ ;
            } // else if

            else if ( IsInt( vec[v] ) ){
                temp -> str[i] = vec[v] ;
                i++ ;
                v++ ;
                while ( IsInt( vec[v] ) ) {
                    temp -> str[i] = vec[v] ;
                    i++ ;
                    v++ ;
                } // while

                if ( v != vec.size() ){
                    temp -> next = new Read ;
                    temp->next->next = NULL ;
                    temp = temp -> next ;
                }
            } // else if

            else { // 不是算式裡可以出現的東西
                cout << "Error 1: " << vec[v] << "is not a legitimate character.\n" ;
                return false ;
            }


            i = 0 ;
        } // while

        Read * tail = NULL ;
        temp = formula ;

        while ( temp != NULL ){
            tail = temp ;
            temp = temp->next ;
        }

        if ( IsOper( tail->str[0] ) ){
            cout << "Error 3: there is one extra operator\n" ;
            return false ;
        }

        if ( right != left ) {
            cout << "Error 2: there is one extra open parenthesis\n" ;
            return false ;
        }

        return true ;
    }

    bool MD( char ch ){
        if ( ch == '*' || ch == '/' )
            return true ;
        else
            return false ;
    }

    bool AS( char ch ){
        if ( ch == '+' || ch == '-' )
            return true ;
        else
            return false ;
    }

    bool FormerBig( char a, char b ){
        if ( MD(a) && AS(b) )
            return true ;
        else
            return false ;
    }

    bool Same( char a, char b ){
        if ( AS(a) && AS(b) )
            return true ;
        else
            return false ;
    }

    void Mission2(){
        post = NULL ;
        stack<char> operbrack ;
        bool brackets = false ;
        Read * temp = NULL ;
        Read * tempformula = formula ;
        post = new Read ;
        post->next = NULL ;
        temp = post ;
        if ( IsInt( tempformula->str[0] ) )
            strcpy( temp->str, tempformula->str ) ;
        else if ( tempformula->str[0] == '(' )
            operbrack.push( tempformula->str[0] ) ;

        tempformula = tempformula->next ;
        while ( tempformula != NULL ){
            if ( IsInt( tempformula->str[0] ) ){
                temp->next = new Read ;
                temp->next->next = NULL ;
                strcpy( temp->next->str, tempformula->str ) ;
                temp = temp->next ;
            }
            else if ( IsOper( tempformula->str[0] ) ){
                if ( operbrack.empty() ) // 是符號而且stack裡沒有東西 丟進去
                    operbrack.push( tempformula->str[0] ) ;
                else{
                    if ( operbrack.top() == '(' )
                        operbrack.push( tempformula->str[0] ) ;
                    else if ( FormerBig( tempformula->str[0], operbrack.top() ) ) // 乘除比加減大
                        operbrack.push( tempformula->str[0] ) ;
                    else {
                        temp->next = new Read ;
                        temp->next->next = NULL ;
                        temp->next->str[0] = operbrack.top() ;
                        temp = temp->next ;
                        operbrack.pop() ;
                        if ( !operbrack.empty() && Same( tempformula->str[0], operbrack.top() ) ){
                            temp->next = new Read ;
                            temp->next->next = NULL ;
                            temp->next->str[0] = operbrack.top() ;
                            temp = temp->next ;
                            operbrack.pop() ;
                        }

                        operbrack.push( tempformula->str[0] ) ;

                    }
                }
            }
            else if ( tempformula->str[0] == '(' ){
                operbrack.push( tempformula->str[0] ) ;
            }
            else if ( tempformula->str[0] == ')' ){
                while ( operbrack.top() != '(' ){
                    temp->next = new Read ;
                    temp->next->next = NULL ;
                    temp->next->str[0] = operbrack.top() ;
                    temp = temp->next ;
                    operbrack.pop() ;
                }
                operbrack.pop() ;
            }

            tempformula = tempformula->next ;

        } // while end

        while ( !operbrack.empty() ){
            temp->next = new Read ;
            temp->next->next = NULL ;
            temp->next->str[0] = operbrack.top() ;
            temp = temp->next ;
            operbrack.pop() ;
        }

        if ( ! IsInt( post->str[0] ) )
            post = post->next ;


        temp = post ;
        cout << "Postfix expression: " ;
        while ( temp != NULL ){
            cout << " " << temp->str ;
            temp = temp->next ;
            if ( temp != NULL )
              cout << "," ;
        }

        cout << "\n" ;

    }

    int Mer( int former, char oper, int latter ){
        if ( oper == '+' )
            return former + latter ;
        else if ( oper == '-' )
            return former - latter ;
        else if ( oper == '*' )
            return former * latter ;
        else if ( oper == '/' )
            return former / latter ;
        else
            return 0 ;
    }

    void Mission3(){
        stack<int> Int ;
        int mer = 0, former = 0, latter = 0, x = 0, h = 0 ;
        Read * tempformula = post ;
        while ( tempformula != NULL ){
            if ( IsInt( tempformula->str[0] ) ){ // 是數字直接丟進stack
                x = atoi( tempformula->str ) ;
                Int.push( x ) ;
            }
            else{ // 遇到運算符號把前兩個數字拿出來做運算
                latter = Int.top() ;
                Int.pop() ;

                former = Int.top() ;
                Int.pop() ;

                mer = Mer( former, tempformula->str[0], latter ) ;
                Int.push( mer ) ;
            }

            tempformula = tempformula ->next ;
        }

        cout << "Answer : " << Int.top() << "\n" ;
        Int.pop() ;

    }




};

void PrintMenu() {
    cout << endl << "* Arithmetic Expression Evaluator *";
    cout << endl << "* 0. QUIT *";
    cout << endl << "* 1. Infix2postfix Evaluation *";
    cout << endl << "***********************************";
    cout << endl << "Input a choice(0, 1): ";
}


int main()
{
    PrintMenu() ;
    int mission ;
    Mission Miss ;

    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 ){
        if ( Miss.Mission1new() ){
            cout << "It is a legitimate infix expression.\n" ;
            Miss.Mission2() ;
            Miss.Mission3() ;
        } // if end
        else
            ;
      } // if end

      else if ( mission > 1 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      cin >> mission ;
    } // while end

}
