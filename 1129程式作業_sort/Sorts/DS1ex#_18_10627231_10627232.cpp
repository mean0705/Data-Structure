// 10627232 10627231
// ���ɾ�   �d���n
// ��T�G�A
//  code blocks 17.12

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

using namespace std;

typedef char Str100[ 100 ] ;
typedef struct cT {

  public:
    string rawR ;
    int gNo ;

}; // task

typedef struct Time {

  public:
    string filen ;
    int s ;
    int b ;
    int m ;
    int q ;
    int r ;
    int ba ;

}; // task

static int gnum = 0 ;
static int clock_s = 0, clock_b = 0, clock_m = 0 , clock_q = 0, clock_r = 0, clock_ba = 0 ;

class Mission{

  public:

  vector<cT> inputfile, mergefile, quickfile, radixfile ;
  vector<Time> timefile ;

  void Selection_sort( string fileNum, int total ){
      vector<cT> sortfile = inputfile ;
      ofstream tempout ;
      string fileName = "Selection_sort" + fileNum + ".txt" ;
      tempout.open ( fileName ) ;
      int big = 0;//�ŧi���ƧǧǦC���̤p��
      cT temptype ;
      clock_s = clock() ;
      for (int i = 0 ; i <total ; i++) {
            big = i;
            int j = i + 1 ;
            while ( j < total ){
                if (sortfile[j].gNo > sortfile[big].gNo)
                    big = j;
                j++ ;
            }

            temptype = sortfile[i];
            sortfile[i] = sortfile[big];
            sortfile[big] = temptype;
      }

      clock_s = clock() - clock_s ;
      cout << "Selection sort :" << (float)clock_s * 1000 / CLOCKS_PER_SEC << " ms"  << endl;
      for ( int i = 0 ; i < total ; i++ ) {
        tempout << sortfile[i].rawR << "\n" ;
      }

      sortfile.clear() ;
      tempout.close() ;
  }

  void Bubble_sort( string fileNum, int total ){
      int i, j, temp;
      vector<cT> sortfile = inputfile ;
      ofstream tempout ;
      string fileName = "Bubble_sort" + fileNum + ".txt" ;
      tempout.open ( fileName ) ;
      cT temptype ;
      clock_b = clock() ;
      for (i = 0; i < total - 1; i++) {
          for (j = 0; j < total - 1 - i; j++){
              if (sortfile[j].gNo < sortfile[j + 1].gNo){
                  temptype = sortfile[j];
                  sortfile[j] = sortfile[j + 1];
                  sortfile[j + 1] = temptype;
              }
          }
      }

      clock_b = clock() - clock_b ;
      cout << "Bubble sort :" << (float)clock_b * 1000 / CLOCKS_PER_SEC << " ms"  << endl;

      for ( int i = 0 ; i < total ; i++ ) {
        tempout << sortfile[i].rawR << "\n" ;
      }
      tempout.close() ;
      sortfile.clear() ;

  }

  void Bubble_advance( string fileNum, int total ){
      int i, j, temp;
      vector<cT> sortfile = inputfile ;
      ofstream tempout ;
      string fileName = "Bubble_sort" + fileNum + ".txt" ;
      tempout.open ( fileName ) ;
      cT temptype ;
      clock_ba = clock() ;
      for(int i = 0; i < total; ++i)
    {
        bool isExchange = false;
        for(int j = i + 1; j < total; ++j)
          if(sortfile[j-1].gNo > sortfile[j].gNo)
            {
                temptype = sortfile[j-1];
                sortfile[j-1] = sortfile[j];
                sortfile[j] = temptype;
                isExchange = true;
            }
        if(isExchange == false)
            break;
    }

      clock_ba = clock() - clock_ba ;
      cout << "Bubble advance sort :" << (float)clock_ba * 1000 / CLOCKS_PER_SEC << " ms"  << endl;



  }

  void Mission1(){

    cT temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 501, 502, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //?P?_???L???
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() )
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
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
              temptype.rawR = raw ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }
              temptype.gNo = atoi( arr[8].c_str() ) ;

              inputfile.push_back(temptype) ;


           } // for read

           tempin.close() ;
           Selection_sort( fileNum, gnum ) ;
           Bubble_sort( fileNum, gnum ) ;

           inputfile.clear() ;
      } //if end

    } //while

  } // Mission1

  void Merge( vector<cT> &Array, int _front, int mid, int _end){

    // �Q�� std::vector ��constructor,
    // ��array[front]~array[mid]��i LeftSub[]
    // ��array[mid+1]~array[end]��i RightSub[]
    vector<cT> LeftSub(Array.begin()+_front, Array.begin()+mid+1) ;
    vector<cT> RightSub(Array.begin()+mid+1, Array.begin()+_end+1);

    cT temptype ;
    temptype.gNo = -1 ;
    temptype.rawR = "0" ;
    LeftSub.insert(LeftSub.end(), temptype);      // �bLeftSub[]���ݥ[�J�Ȭ� Max ������
    RightSub.insert(RightSub.end(), temptype);    // �bRightSub[]���ݥ[�J�Ȭ� Max ������

    int idxLeft = 0, idxRight = 0;

    for (int i = _front; i <= _end; i++) {

        if (LeftSub[idxLeft].gNo >= RightSub[idxRight].gNo ) {
            Array[i] = LeftSub[idxLeft];
            idxLeft++;
        }
        else{
            Array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
}

  void Merge_Sort( vector<cT> &Array, int _front, int _end){
                                       // front�Pend���x�}�d��
    if (_front < _end) {                   // ��ܥثe���x�}�d��O���Ī�
        int mid = (_front+_end)/2;   // mid�Y�O�N�x�}��b����index
        Merge_Sort( Array, _front, mid);    // �~��divide�x�}���e�b�qsubarray
        Merge_Sort( Array, mid+1, _end);    // �~��divide�x�}����b�qsubarray
        Merge( Array, _front, mid, _end);   // �N���subarray�����, �æX�֥X�Ƨǫ᪺�x�}
    }
  }

  int Partition(vector<cT> &Array, int _front, int _end){
    int pivot = Array[_end].gNo;
    int i = _front -1;
    cT temptype ;
    for (int j = _front; j < _end; j++) {
        if (Array[j].gNo > pivot) {
            i++;
            temptype = Array[i] ;
            Array[i] = Array[j] ;
            Array[j] = temptype ;
        }
    }
    i++;
    temptype = Array[i] ;
    Array[i] = Array[_end] ;
    Array[_end] = temptype ;
    return i;
  }

  void Quick_Sort(vector<cT> &Array, int _front, int _end){
    if (_front < _end) {
        int pivot = Partition(Array, _front, _end);
        Quick_Sort(Array, _front, pivot - 1);
        Quick_Sort(Array, pivot + 1, _end);
    }
  }

  void Mission2(){
    cT temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 501, 502, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //?P?_???L???
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() )
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
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
              temptype.rawR = raw ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }
              temptype.gNo = atoi( arr[8].c_str() ) ;

              inputfile.push_back(temptype) ;


           } // for read


           tempin.close() ;

           mergefile = inputfile ;
           clock_m = clock() ;
           Merge_Sort( mergefile, 0, gnum-1 ) ;
           clock_m = clock() - clock_m ;
           cout << "Merge sort :" << (float)clock_m * 1000 / CLOCKS_PER_SEC << " ms"  << endl;

           ofstream tempout ;
           string fileName = "Merge_sort" + fileNum + ".txt" ;
           tempout.open ( fileName ) ;
           for ( int i = 0 ; i < gnum ; i++ ) {
             tempout << mergefile[i].rawR << "\n" ;
           }

           mergefile.clear() ;
           tempout.close() ;


           quickfile = inputfile ;
           clock_q = clock() ;
           Quick_Sort( quickfile, 0, gnum-1 ) ;
           clock_q = clock() - clock_q ;
           cout << "Quick sort :" << (float)clock_q * 1000 / CLOCKS_PER_SEC << " ms"  << endl;

           ofstream tempout2 ;
           string fileName2 = "Quick_sort" + fileNum + ".txt" ;
           tempout2.open ( fileName2 ) ;
           for ( int i = 0 ; i < gnum ; i++ ) {
             tempout2 << quickfile[i].rawR << "\n" ;
           }
           quickfile.clear() ;
           tempout2.close() ;


           inputfile.clear() ;
      } //if end

    } //while
  }

  void radix_Sort(vector<cT> &Array, int _max, int total) {
    int x = total / 2 ;
    cT temp[10][x] ;
    int order[10] = {0};

    int a = _max ;
    int d = 0 ;
    while( a != 0 ){
        a /= 10 ;
        d++ ;
    }
    int n = 1;

    for ( int time = 1 ; time <= d ; time++ ) {

        int i;
        for(i = 0; i < total ; i++) {
            int lsd = ((Array[i].gNo / n) % 10);
            temp[lsd][order[lsd]] = Array[i];
            order[lsd]++;
        }

        // ���s�ƦC
        int k = 0;
        for(i = 9; i >= 0 ; i-- ) {
            if(order[i] != 0)  {
                int j;
                for(j = 0 ; j < order[i] ; j++, k++) {
                    Array[k] = temp[i][j];
                }
            }
            order[i] = 0;
        }

        n = n * 10;
    }
  }

  void Mission3(){

    cT temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 501, 502, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //?P?_???L???
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() )
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
        else
            nofile = false ;
      } // if  end

      if ( nofile == false ){// ?????F?N?}?l??i?as?J
          string raw ;
          int _max = 0 ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;
              temptype.rawR = raw ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }
              temptype.gNo = atoi( arr[8].c_str() ) ;

              if ( temptype.gNo > _max ) _max = temptype.gNo ;
              inputfile.push_back(temptype) ;


           } // for read

           tempin.close() ;
           radixfile = inputfile ;
           clock_r = clock() ;
           radix_Sort( radixfile, _max, gnum ) ;
           clock_r = clock() - clock_r ;
           cout << "Radix sort :" << (float)clock_r * 1000 / CLOCKS_PER_SEC << " ms"  << endl;

           ofstream tempout2 ;
           string fileName2 = "Radix_sort" + fileNum + ".txt" ;
           tempout2.open ( fileName2 ) ;
           for ( int i = 0 ; i < gnum ; i++ ) {
             tempout2 << radixfile[i].rawR << "\n" ;
           }

           tempout2.close() ;
           radixfile.clear() ;
           inputfile.clear() ;
      } //if end

    } //while

  } // Mission1

  void Mission4(){
    cT temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 501, 502, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;

    while ( nofile == true ){ //?P?_???L???
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        tempin.open( fileName );
        if ( ! tempin.is_open() )
            printf( "### sort%s.txt does not exist! ###\n", fileNum ) ;
        else
            nofile = false ;
      } // if  end

      if ( nofile == false ){// ?????F?N?}?l??i?as?J
          string raw ;
          int _max = 0 ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;
          getline( tempin, raw ) ;
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;
              temptype.rawR = raw ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }
              temptype.gNo = atoi( arr[8].c_str() ) ;

              if ( temptype.gNo > _max ) _max = temptype.gNo ;
              inputfile.push_back(temptype) ;


           } // for read

           tempin.close() ;


           Selection_sort( fileNum, gnum ) ;

           Bubble_sort( fileNum, gnum ) ;

           Bubble_advance( fileNum, gnum ) ;

           mergefile = inputfile ;
           clock_m = clock() ;
           Merge_Sort( mergefile, 0, gnum-1 ) ;
           clock_m = clock() - clock_m ;
           cout << "Merge sort :" << (float)clock_m * 1000 / CLOCKS_PER_SEC << " ms"  << endl;
           mergefile.clear() ;

           quickfile = inputfile ;
           clock_q = clock() ;
           Quick_Sort( quickfile, 0, gnum-1 ) ;
           clock_q = clock() - clock_q ;
           cout << "Quick sort :" << (float)clock_q * 1000 / CLOCKS_PER_SEC << " ms"  << endl;
           quickfile.clear() ;

           radixfile = inputfile ;
           clock_r = clock() ;
           radix_Sort( radixfile, _max, gnum ) ;
           clock_r = clock() - clock_r ;
           cout << "Radix sort :" << (float)clock_r * 1000 / CLOCKS_PER_SEC << " ms"  << endl;
           radixfile.clear() ;

           Time temptime ;
           temptime.filen = fileNum ;
           temptime.s = clock_s ;
           temptime.b = clock_b ;
           temptime.m = clock_m ;
           temptime.q = clock_q ;
           temptime.r = clock_r ;
           temptime.ba = clock_ba ;

           timefile.push_back( temptime ) ;

           ofstream tempin2 ;
           string tempinName2 = "sort_time.txt" ;
           tempin2.open( tempinName2 ) ;
           tempin2 << "file" << "\t" << "select" << "\t" << "bubble" << "\t" << "merge" << "\t" << "quick" << "\t" << "radix" << "\t" << "bubbleA" << "\n" ;

           for ( int j = 0 ; j < timefile.size() ; j++ ){
               tempin2 << timefile[j].filen << "\t" ;
               tempin2 << timefile[j].s << "\t" ;
               tempin2 << timefile[j].b << "\t" ;
               tempin2 << timefile[j].m << "\t" ;
               tempin2 << timefile[j].q << "\t" ;
               tempin2 << timefile[j].r << "\t" ;
               tempin2 << timefile[j].ba << "\t" ;
               tempin2 << "\n" ;

               //timefile[j].filen << "\t" << timefile[j].s << "\t" << timefile[j].b << "\t" << timefile[j].filem << "\t" << timefile[j].q << "\t" << timefile[j].r <<
           }

           tempin2.close() ;
           inputfile.clear() ;
      } //if end

    } //while

  }

};



void PrintMenu(){

  cout << endl << "******** Sorting Algorithms *********";
  cout << endl << "* 0. QUIT                           *";
  cout << endl << "* 1. Selection sort vs. Bubble sort *";
  cout << endl << "* 2. Merge sort vs. Quick sort      *";
  cout << endl << "* 3. Radix sort                     *";
  cout << endl << "*************************************";
  cout << endl << "Input a command(0, 1, 2, 3): ";
} // PrintMenu()

int main() {
    PrintMenu() ;
    int mission ;
    Mission Miss ;

    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )      Miss.Mission1() ;
      else if ( mission == 2 ) Miss.Mission2() ;
      else if ( mission == 3 ) Miss.Mission3() ;
      else if ( mission == 4 ) Miss.Mission4() ;
      else if ( mission > 1 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      gnum = 0 ;
      cin >> mission ;
    } // while end

} //
