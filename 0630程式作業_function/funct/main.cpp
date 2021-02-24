#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ctime>

using namespace std ;

int gnum = 1 ;
int cT = 0 ;
struct num {
  float coefficient ;
  int index ;
} ;

class Mission{

    public:
    vector<num> funct1, funct2, temp;

    void Bubble_sort_1(){ // sort function1
      int i, j;
      for (i = 0; i < funct1.size() - 1; i++) {
          for (j = 0; j < funct1.size() - 1 - i; j++){
              if ( funct1[j].index < funct1[j+1].index ){
                  swap( funct1[j], funct1[j+1] );
              }
          }
      }
    }

    void Bubble_sort_2(){ // sort function2
      int i, j;
      for (i = 0; i < funct2.size() - 1; i++) {
          for (j = 0; j < funct2.size() - 1 - i; j++){
              if ( funct2[j].index < funct2[j+1].index ){
                  swap( funct2[j], funct2[j+1] );
              }
          }
      }
    }

    void Bubble_sort_temp(){ // sort temp
      int i, j;
      for (i = 0; i < temp.size() - 1; i++) {
          for (j = 0; j < temp.size() - 1 - i; j++){
              if ( temp[j].index < temp[j+1].index ){
                  swap( temp[j], temp[j+1] );
              }
          }
      }
    }

    void Combine(){ // combine function1
        Bubble_sort_1(); // sort , from high to low

        num tempdata;
        float temp_coefficient = 0;
        int temp_index = funct1[0].index;
        for(int j = 0 ; j <= funct1.size(); j++){ // combine if function1 data has same and push back to temp
            if ( j == funct1.size() ){ // last processed data needs to push back to temp
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                temp.push_back(tempdata);
            }
            else if (temp_index == funct1[j].index && j != 0) temp_coefficient = funct1[j].coefficient + temp_coefficient; // combine same index's coefficient
            else if (temp_index == funct1[j].index && j == 0) temp_coefficient = funct1[j].coefficient ; // combine same index's coefficient, but first data
            else { // next data because no same index, and put current data to temp
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                if (temp_coefficient == 0){ // if current data's coefficient is 0, don't need to push back to temp
                    temp_index = funct1[j].index;
                    temp_coefficient = funct1[j].coefficient;
                    continue;
                }
                temp.push_back(tempdata);
                temp_index = funct1[j].index;
                temp_coefficient = funct1[j].coefficient;
            }
        }

        funct1 = temp;
        cout << endl << "answer: ";
        for (int i = 0; i < funct1.size(); i++){ // print answer
            if (i == 0) {
                if (funct1[i].coefficient == 1) cout << "x^" << funct1[i].index;
                else if ( funct1[i].index == 1 ) cout  << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout  << funct1[i].coefficient;
                else cout << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else if ( funct1[i].coefficient > 0 ) {
                if (funct1[i].coefficient == 1) cout << "+x^" << funct1[i].index;
                else if ( funct1[i].index == 1 ) cout << "+" << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout << "+" << funct1[i].coefficient;
                else cout << "+" << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else if ( funct1[i].coefficient < 0 ) {
                if ( funct1[i].index == 1 ) cout  << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout  << funct1[i].coefficient;
                else cout << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else cout << "error\n";
        }
        cout << endl;
        temp.clear();
        funct1.clear();

    }

    void Mission1(){
        num tempdata;
        char symbol, temp;
        float temp_coefficient;
        int temp_index;
        cout << "Input your function : ";
        while(1){ // scan
            cin >> symbol ; // (
            cin >> temp_coefficient;
            cin >> symbol; // ,
            cin >> temp_index;
            tempdata.coefficient = temp_coefficient;
            tempdata.index = temp_index;
            funct1.push_back(tempdata);
            cin >> symbol; // )
            if ( cin.get() == '\n' ) break;
        }

        Combine();
    } // Mission1

    void ComnimeTwo(){
        num tempdata;
        for(int i = 0 ; i < funct1.size(); i++){ // make function1 data push back to temp
            tempdata.index = funct1[i].index;
            tempdata.coefficient = funct1[i].coefficient;
            temp.push_back(tempdata);
        }
        for(int i = 0 ; i < funct2.size(); i++){ // make function2 data push back to temp
            tempdata.index = funct2[i].index;
            tempdata.coefficient = funct2[i].coefficient;
            temp.push_back(tempdata);
        }
        funct1.clear();
        funct2.clear();

        Bubble_sort_temp(); // sort temp

        int temp_index = temp[0].index;
        float temp_coefficient = 0;
        for(int j = 0 ; j <= temp.size(); j++){ // combine if temp data has same and push back to function1
            if ( j == temp.size() ){
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                funct1.push_back(tempdata);
            }
            else if (temp_index == temp[j].index && j != 0) temp_coefficient = temp[j].coefficient + temp_coefficient;
            else if (temp_index == temp[j].index && j == 0) temp_coefficient = temp[j].coefficient ;
            else {
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                if (temp_coefficient == 0){
                    temp_index = temp[j].index;
                    temp_coefficient = temp[j].coefficient;
                    continue;
                }
                funct1.push_back(tempdata);
                temp_index = temp[j].index;
                temp_coefficient = temp[j].coefficient;
            }
        }

        cout << endl << "answer: ";
        for (int i = 0; i < funct1.size(); i++){
            if (i == 0) {
                if (funct1[i].coefficient == 1) cout << "x^" << funct1[i].index;
                else if ( funct1[i].index == 1 ) cout  << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout  << funct1[i].coefficient;
                else cout << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else if ( funct1[i].coefficient > 0 ) {
                if (funct1[i].coefficient == 1) cout << "+x^" << funct1[i].index;
                else if ( funct1[i].index == 1 ) cout << "+" << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout << "+" << funct1[i].coefficient;
                else cout << "+" << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else if ( funct1[i].coefficient < 0 ) {
                if ( funct1[i].index == 1 ) cout  << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout  << funct1[i].coefficient;
                else cout << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else cout << "error\n";
        }
        cout << endl;
        temp.clear();
        funct1.clear();
        funct2.clear();
    }

    void Mission2(){
        num tempdata;
        char symbol, temp;
        float temp_coefficient;
        int temp_index;
        cout << "Input your function1 : ";
        while(1){
            cin >> symbol ; // (
            cin >> temp_coefficient;
            cin >> symbol; // ,
            cin >> temp_index;
            tempdata.coefficient = temp_coefficient;
            tempdata.index = temp_index;
            funct1.push_back(tempdata);
            cin >> symbol; // )
            if ( cin.get() == '\n' ) break;
        }

        cout << "Input your function2 : ";
        while(1){
            cin >> symbol ; // (
            cin >> temp_coefficient;
            cin >> symbol; // ,
            cin >> temp_index;
            tempdata.coefficient = temp_coefficient;
            tempdata.index = temp_index;
            funct2.push_back(tempdata);
            cin >> symbol; // )
            if ( cin.get() == '\n' ) break;
        }

        ComnimeTwo();
    }

    void MultiplyTwo(){
        Bubble_sort_1();
        Bubble_sort_2();
        num tempdata;
        float temp_coefficient = 0;
        int temp_index = funct1[0].index;
        for(int j = 0 ; j <= funct1.size(); j++){ // combine if function1 data has same and push back to temp
            if ( j == funct1.size() ){ // last processed data needs to push back to temp
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                temp.push_back(tempdata);
            }
            else if (temp_index == funct1[j].index && j != 0) temp_coefficient = funct1[j].coefficient + temp_coefficient; // combine same index's coefficient
            else if (temp_index == funct1[j].index && j == 0) temp_coefficient = funct1[j].coefficient ; // combine same index's coefficient, but first data
            else { // next data because no same index, and put current data to temp
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                if (temp_coefficient == 0){ // if current data's coefficient is 0, don't need to push back to temp
                    temp_index = funct1[j].index;
                    temp_coefficient = funct1[j].coefficient;
                    continue;
                }
                temp.push_back(tempdata);
                temp_index = funct1[j].index;
                temp_coefficient = funct1[j].coefficient;
            }
        }
        funct1 = temp;
        temp.clear();

        temp_coefficient = 0;
        temp_index = funct2[0].index;
        for(int j = 0 ; j <= funct2.size(); j++){ // combine if function2 data has same and push back to temp
            if ( j == funct2.size() ){ // last processed data needs to push back to temp
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                temp.push_back(tempdata);
            }
            else if (temp_index == funct2[j].index && j != 0) temp_coefficient = funct2[j].coefficient + temp_coefficient; // combine same index's coefficient
            else if (temp_index == funct2[j].index && j == 0) temp_coefficient = funct2[j].coefficient ; // combine same index's coefficient, but first data
            else { // next data because no same index, and put current data to temp
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                if (temp_coefficient == 0){ // if current data's coefficient is 0, don't need to push back to temp
                    temp_index = funct2[j].index;
                    temp_coefficient = funct2[j].coefficient;
                    continue;
                }
                temp.push_back(tempdata);
                temp_index = funct2[j].index;
                temp_coefficient = funct2[j].coefficient;
            }
        }

        funct2 = temp;
        temp.clear();
        temp_coefficient = 0;
        temp_index = 0;
        for(int i = 0 ;i < funct1.size(); i++){ // multiply two functions.
            for(int j = 0; j < funct2.size(); j++){
                tempdata.coefficient = funct1[i].coefficient * funct2[j].coefficient;
                tempdata.index = funct1[i].index + funct2[j].index;
                temp.push_back(tempdata);
            }
        }

        funct1.clear();
        funct2.clear();
        Bubble_sort_temp();

        temp_index = temp[0].index;
        temp_coefficient = 0;
        for(int j = 0 ; j <= temp.size(); j++){ // combine if temp data has same and push back to function1
            if ( j == temp.size() ){
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                funct1.push_back(tempdata);
            }
            else if (temp_index == temp[j].index && j != 0) temp_coefficient = temp[j].coefficient + temp_coefficient;
            else if (temp_index == temp[j].index && j == 0) temp_coefficient = temp[j].coefficient ;
            else {
                tempdata.index = temp_index;
                tempdata.coefficient = temp_coefficient;
                if (temp_coefficient == 0){
                    temp_index = temp[j].index;
                    temp_coefficient = temp[j].coefficient;
                    continue;
                }
                funct1.push_back(tempdata);
                temp_index = temp[j].index;
                temp_coefficient = temp[j].coefficient;
            }
        }

        cout << endl << "answer: ";
        for (int i = 0; i < funct1.size(); i++){
            if (i == 0) {
                if (funct1[i].coefficient == 1) cout << "x^" << funct1[i].index;
                else if ( funct1[i].index == 1 ) cout  << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout  << funct1[i].coefficient;
                else cout << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else if ( funct1[i].coefficient > 0 ) {
                if (funct1[i].coefficient == 1) cout << "+x^" << funct1[i].index;
                else if ( funct1[i].index == 1 ) cout << "+" << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout << "+" << funct1[i].coefficient;
                else cout << "+" << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else if ( funct1[i].coefficient < 0 ) {
                if ( funct1[i].index == 1 ) cout  << funct1[i].coefficient << "x";
                else if ( funct1[i].index == 0 ) cout  << funct1[i].coefficient;
                else cout << funct1[i].coefficient << "x^" << funct1[i].index;
            }
            else cout << "error\n";
        }
        cout << endl;
        temp.clear();
        funct1.clear();
        funct2.clear();

    }

    void Mission3(){
        num tempdata;
        char symbol, temp;
        float temp_coefficient;
        int temp_index;
        cout << "Input your function1 : ";
        while(1){
            cin >> symbol ; // (
            cin >> temp_coefficient;
            cin >> symbol; // ,
            cin >> temp_index;
            tempdata.coefficient = temp_coefficient;
            tempdata.index = temp_index;
            funct1.push_back(tempdata);
            cin >> symbol; // )
            if ( cin.get() == '\n' ) break;
        }

        cout << "Input your function2 : ";
        while(1){
            cin >> symbol ; // (
            cin >> temp_coefficient;
            cin >> symbol; // ,
            cin >> temp_index;
            tempdata.coefficient = temp_coefficient;
            tempdata.index = temp_index;
            funct2.push_back(tempdata);
            cin >> symbol; // )
            if ( cin.get() == '\n' ) break;
        }

        MultiplyTwo();
    }

}; // Mission

void Print(){
    cout << endl << "** Function                           *";
    cout << endl << "* 0. Quit                             *";
    cout << endl << "* 1. Create a function                *";
    cout << endl << "* 2. Add two functions                *";
    cout << endl << "* 3. Multiply two functions           *";
    cout << endl << "***************************";
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
      else if ( mission > 2 && mission < 999 )
        printf( "Not Exist!\n" ) ;
      else{
        break ;
      }

      Print() ;
      cin >> mission ;
    } // while end

}

