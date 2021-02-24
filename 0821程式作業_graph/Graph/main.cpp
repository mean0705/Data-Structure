
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

typedef struct Coordinate {
  int x ;
  int y ;
  vector<int> contact;
} ; // Coordinate

class Mission{

  public:

  vector<Coordinate> form ;
  string fileNum ;

  void Mission1(){
    ifstream tempin ;

    cout << "Input 201, 202, ...[0]Quit):" ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    bool nofile = true ;
    while ( nofile == true ){ // 若沒有此文件就要繼續讀下去
      if ( fileNum.size() == 1 && fileNum[0] == '0' ) // 如果是0就結束
          return ;
      else {
        tempin.open( fileName );       // 打開此文件
        if ( !tempin.is_open() ){      // 文件並沒有被打開
            tempin.close();            // 重新輸入一次文件編號
            cout << "no file.\n";
            cout << "Input 201, 202, ...[0]Quit):" ;
            cin.clear() ;
            cin >> fileNum ;
            fileName = "input" + fileNum + ".txt" ;
            nofile = true;
        }
        else                           // 文件被打開
            nofile = false ;
      } // if  end

      if ( nofile == false ){          // 若文件被打開了，開始執行任務
          Coordinate temptype;
          char instruction, num ;
          int length, width;

          if (tempin.get(num))  length = num - '0'; // 得到長度
          tempin.get(num); // 讀到空格
          if (tempin.get(num))  width = num - '0';  // 得到寬度
          tempin.get(num); // 讀到換行

          for( int i = 1; tempin.get(instruction); i++){ // 開始輸入迷宮的字符
              if(instruction == 'O') ;                   // 是障礙物不存取
              else if(instruction == 'E' || instruction == 'G' ){ // 不是的 記錄此點 表示可通
                if  (i%length == 0){                              // 並得到x跟y
                   temptype.x = length;
                   temptype.y = i / length;
                }
                else{
                   temptype.x = i % length;
                   temptype.y = i / length + 1;
                }
                form.push_back(temptype);                         // 丟進vector裡
              }
              else if (instruction == '\n') i--;                     // 因每行之間會有換行，此換行不能算是字符
              else cout << "error\n";
          }

          for(int j = 0; j < form.size();j++){ // 輸出每個點的x跟y
             cout << "[" << j << "]" << " (" << form[j].x << "," << form[j].y << ")\n";
          }

          for(int i = 0; i < form.size(); i++){
            for(int j = 0; j < form.size(); j++){
                if (i == j) continue;
                else if (form[i].x == form[j].x - 1 && form[i].y == form[j].y){ // 一點在左一點在右 表示有連接，輸出
                    cout << "<" << i << "," << j << ">" << endl;
                }
                else if (form[i].y == form[j].y - 1 && form[i].x == form[j].x){ // 一點在上一點在下 表示有連接，輸出
                    cout << "<" << i << "," << j << ">" << endl;
                }
                else;
            }
          }
      } //if end
    } //while

  } // Mission1

  void Mission2(){
      if (form .size() == 0){
          cout << "please choose one first.\n";
      }
      else{
          ofstream tempout;       // 創立一個文件
          string outputName = "output" + fileNum + ".txt";  // 叫做outputxxx.txt
          tempout.open(outputName);          // 打開

          for(int i = 0; i < form.size(); i++){ // 一個點一個點觀察，若用相鄰點就印出
            for(int j = 0, k = 0; j < form.size(); j++){
                if (i == 0){
                    if (form[i].x == form[j].x - 1 && form[i].y == form[j].y)      form[i].contact.push_back(j); //右邊點不是障礙物，印
                    else if (form[i].y == form[j].y - 1 && form[i].x == form[j].x) form[i].contact.push_back(j); //下面點不是障礙物，印
                    else ;
                }
                else {
                    if (form[i].y == form[j].y + 1 && form[i].x == form[j].x)      form[i].contact.push_back(j);  //上面點不是障礙物，印
                    else if (form[i].x == form[j].x + 1 && form[i].y == form[j].y) form[i].contact.push_back(j); //左邊點不是障礙物，印
                    else if (form[i].x == form[j].x - 1 && form[i].y == form[j].y) form[i].contact.push_back(j); //右邊點不是障礙物，印
                    else if (form[i].y == form[j].y - 1 && form[i].x == form[j].x) form[i].contact.push_back(j); //下面點不是障礙物，印
                    else ;
                }
            }
          }

          for(int i = 0; i < form.size();i++){
              tempout << "[" << i << "] ";
              for (int j = 0; j < form[i].contact.size(); j++){
                tempout << form[i].contact[j] << ". ";
              }
              tempout << endl;
          }


      } //else end

      form.clear();

  } // Mission1
};

void PrintMenu(){
    cout << endl << "**** Heap Construction  *****";
    cout << endl << "* 0. QUIT                   *";
    cout << endl << "* 1. Get edge and vertex    *";
    cout << endl << "* 2. Create a adjacency list*";
    cout << endl << "* 3. Find a shortest path(no)";
    cout << endl << "*****************************";
    cout << endl << "Input a choice(0, 1, 2): ";
} // PrintMenu()

int main() {
    PrintMenu() ;
    Mission miss ;
    int mission ;
    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )      miss.Mission1() ;
      else if ( mission == 2 ) miss.Mission2() ;
      //else if ( mission == 3 ) miss.Mission3() ;
      else if ( mission > 3 && mission < 9999 )
        printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      cin >> mission ;
    } // while end
}

