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
            if (funct == NULL){  // �p�GFUNCT1�ONULL���N�Хߤ@�ӷs���`�I�ñNŪ�J����Ʃ�i�`�I��
                cin >> symbol ; // (
                cin >> temp_coefficient;
                cin >> symbol; // ,
                cin >> temp_index;
                funct = new NumPtr;
                funct->coefficient = temp_coefficient;
                funct->index = temp_index;
                funct->next = NULL;
                tempPtr = funct;
                cur_index = funct->index; // �]�m�F�@�Ӳ{�b��index�H�K���J�ɨϥ�
            }
            else{
                cin >> symbol ; // (
                cin >> temp_coefficient;
                cin >> symbol; // ,
                cin >> temp_index;
                if ( temp_index > cur_index && tempPtr == funct ){ // �YŪ�J�ӵ���ƪ����Ƥj��ڭ쥻��C�̪��̤j����
                    tempHead = new NumPtr;                             // �s�W�@�ӷs���Y�B�s�W�@�ӵ��I
                    tempHead->coefficient = temp_coefficient;       // �ñN��Ʃ�J�`�I��
                    tempHead->index = temp_index;
                    tempHead->next = funct;                        // �ñN�᭱���_��
                    funct = tempHead;
                    tempHead = NULL;
                }
                else if (temp_index == cur_index ){                 // �Y���Ƭ۵��A���N���Ƭۥ[�Y�i
                    tempPtr->coefficient = tempPtr->coefficient + temp_coefficient;
                }
                else if (temp_index < cur_index ){                  // �YŪ�J�����Ƥ�Ӧ�C���̤j�����٤p
                    temp2 = tempPtr;
                    if ( tempPtr->next != NULL ) tempPtr = tempPtr->next;
                    while( tempPtr != NULL ){                       // ���N�����
                        cur_index = tempPtr->index;
                        if ( temp_index > cur_index ){              // �����A�Y���Ū�J�����Ƥ�ӫ��Ƥj
                            temp2->next = NULL;                     // ���N���J
                            temp2->next = new NumPtr;
                            temp2 = temp2->next;
                            temp2->coefficient = temp_coefficient;
                            temp2->index = temp_index;
                            temp2->next = tempPtr;
                            break;
                        }
                        else if (temp_index == cur_index ){         // �۵��ۥ[�Y�i
                            tempPtr->coefficient = tempPtr->coefficient + temp_coefficient;
                            break;
                        }
                        temp2 = tempPtr;
                        tempPtr = tempPtr->next;
                    }

                    if (tempPtr == NULL){                          // �Y�ƻ򳣨S���A����̫᭱
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
            cur_index = funct->index; //�]�m�F�@�Ӳ{�b��index�H�K���J�ɨϥ�
        } // while

        return funct;
    }

    void PrintFunction( NumPtr * funct ){
        NumPtr * tempPtr = funct;
        cout << "Answer is :  ";
        for (tempPtr = funct; tempPtr != NULL; tempPtr = tempPtr -> next){ // �L�X����
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
            else cout << ""; // �p�G�ۥ[�����Ƭ�0�N���ο�X�F
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

    NumPtr * AddTwoFunct( NumPtr * funct1, NumPtr * funct2 ){ // ��function2���@���@�����Ū�J�æX����function1��
        NumPtr * tempPtr1 = funct1;
        NumPtr * tempPtr2 = funct2;
        NumPtr * tempHead = NULL;
        NumPtr * temp = NULL;

        while( tempPtr2 != NULL ){
            if ( tempPtr2->index > tempPtr1->index ){
                tempHead = new NumPtr;                             // �s�W�@�ӷs���Y�B�s�W�@�ӵ��I
                tempHead->coefficient = tempPtr2->coefficient;       // �ñN��Ʃ�J�`�I��
                tempHead->index = tempPtr2->index;
                tempHead->next = tempPtr1;                        // �ñN�᭱���_��
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
                while( tempPtr1 != NULL ){                           // ���N�����
                    int cur_index = tempPtr1->index;
                    if ( tempPtr2->index > cur_index ){              // �����A�Y���Ū�J��function2�����Ƥ�ӫ��Ƥj
                        temp->next = NULL;                           // ���N���J
                        temp->next = new NumPtr;
                        temp = temp->next;
                        temp->coefficient = tempPtr2->coefficient;
                        temp->index = tempPtr2->index;
                        temp->next = tempPtr1;
                        break;
                    }
                    else if (tempPtr2->index == cur_index ){         // �۵��ۥ[�Y�i
                        tempPtr1->coefficient = tempPtr1->coefficient + tempPtr2->coefficient;
                        break;
                    }
                    temp = tempPtr1;
                    tempPtr1 = tempPtr1->next;
                }

                if (tempPtr1 == NULL){                          // �Y�ƻ򳣨S���A����̫᭱
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

        return funct1;     // �^��function1 �]�N�O�M �[�L��
    }

    void Mission2(){
        cout << "When you input your function ,if you want to get 2x^3, input (2,3), and next, you need to input ',' to separate.\n";
        cout << "Like : (2,3),(1,2),(4.5,7)\n\n";
        cout << "Input your function1 : ";
        NumPtr * funct1 = Combinne(funct1);
        cout << "Input your function2 : ";
        NumPtr * funct2 = Combinne(funct2); // ���Ʀn���function

        NumPtr * sumFunct = AddTwoFunct(funct1, funct2); //�ۥ[ sum Function
        PrintFunction(sumFunct);
    }

    NumPtr * MultiplyTwoFunct( NumPtr * funct1, NumPtr * funct2 ){
        NumPtr * Product = NULL;  // �s�W�@�� product pointer �N���ۭ��_�Ӫ��ƭȩ�i�h
        NumPtr * tempPro = NULL;
        for( NumPtr * tempPtr1 = funct1; tempPtr1 != NULL; tempPtr1 = tempPtr1->next ){
            for( NumPtr * tempPtr2 = funct2; tempPtr2 != NULL; tempPtr2 = tempPtr2->next ){
                if (Product == NULL){ // product�٨S���F�誺�ܦ]��tempPro�n���product�A�ҥH�n�t�~�g
                    Product = new NumPtr;
                    Product->coefficient = tempPtr1->coefficient * tempPtr2->coefficient;
                    Product->index = tempPtr1->index + tempPtr2->index;
                    Product->next = NULL;
                    tempPro = Product;
                }
                else{
                    tempPro->next = new NumPtr; // ��L�N�O�@�Ӥ@�ӥ[�b�᭱
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

