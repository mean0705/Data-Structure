
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
    while ( nofile == true ){ // �Y�S�������N�n�~��Ū�U�h
      if ( fileNum.size() == 1 && fileNum[0] == '0' ) // �p�G�O0�N����
          return ;
      else {
        tempin.open( fileName );       // ���}�����
        if ( !tempin.is_open() ){      // ���èS���Q���}
            tempin.close();            // ���s��J�@�����s��
            cout << "no file.\n";
            cout << "Input 201, 202, ...[0]Quit):" ;
            cin.clear() ;
            cin >> fileNum ;
            fileName = "input" + fileNum + ".txt" ;
            nofile = true;
        }
        else                           // ���Q���}
            nofile = false ;
      } // if  end

      if ( nofile == false ){          // �Y���Q���}�F�A�}�l�������
          Coordinate temptype;
          char instruction, num ;
          int length, width;

          if (tempin.get(num))  length = num - '0'; // �o�����
          tempin.get(num); // Ū��Ů�
          if (tempin.get(num))  width = num - '0';  // �o��e��
          tempin.get(num); // Ū�촫��

          for( int i = 1; tempin.get(instruction); i++){ // �}�l��J�g�c���r��
              if(instruction == 'O') ;                   // �O��ê�����s��
              else if(instruction == 'E' || instruction == 'G' ){ // ���O�� �O�����I ��ܥi�q
                if  (i%length == 0){                              // �ño��x��y
                   temptype.x = length;
                   temptype.y = i / length;
                }
                else{
                   temptype.x = i % length;
                   temptype.y = i / length + 1;
                }
                form.push_back(temptype);                         // ��ivector��
              }
              else if (instruction == '\n') i--;                     // �]�C�椧���|������A�����椣���O�r��
              else cout << "error\n";
          }

          for(int j = 0; j < form.size();j++){ // ��X�C���I��x��y
             cout << "[" << j << "]" << " (" << form[j].x << "," << form[j].y << ")\n";
          }

          for(int i = 0; i < form.size(); i++){
            for(int j = 0; j < form.size(); j++){
                if (i == j) continue;
                else if (form[i].x == form[j].x - 1 && form[i].y == form[j].y){ // �@�I�b���@�I�b�k ��ܦ��s���A��X
                    cout << "<" << i << "," << j << ">" << endl;
                }
                else if (form[i].y == form[j].y - 1 && form[i].x == form[j].x){ // �@�I�b�W�@�I�b�U ��ܦ��s���A��X
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
          ofstream tempout;       // �Хߤ@�Ӥ��
          string outputName = "output" + fileNum + ".txt";  // �s��outputxxx.txt
          tempout.open(outputName);          // ���}

          for(int i = 0; i < form.size(); i++){ // �@���I�@���I�[��A�Y�ά۾F�I�N�L�X
            for(int j = 0, k = 0; j < form.size(); j++){
                if (i == 0){
                    if (form[i].x == form[j].x - 1 && form[i].y == form[j].y)      form[i].contact.push_back(j); //�k���I���O��ê���A�L
                    else if (form[i].y == form[j].y - 1 && form[i].x == form[j].x) form[i].contact.push_back(j); //�U���I���O��ê���A�L
                    else ;
                }
                else {
                    if (form[i].y == form[j].y + 1 && form[i].x == form[j].x)      form[i].contact.push_back(j);  //�W���I���O��ê���A�L
                    else if (form[i].x == form[j].x + 1 && form[i].y == form[j].y) form[i].contact.push_back(j); //�����I���O��ê���A�L
                    else if (form[i].x == form[j].x - 1 && form[i].y == form[j].y) form[i].contact.push_back(j); //�k���I���O��ê���A�L
                    else if (form[i].y == form[j].y - 1 && form[i].x == form[j].x) form[i].contact.push_back(j); //�U���I���O��ê���A�L
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

