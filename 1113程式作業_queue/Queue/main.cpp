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
#include <ctime>

using namespace std;

typedef char Str100[ 100 ] ;
typedef struct task {

  public:
    string rawR ;
    int oid ;
    int arrival ;
    int duration ;
    int timeout ;

}; // task

typedef struct data {

  public:
    int oid ;
    int cid ;
    int delay ;
    int abort_departure ;


}; // task

static int gnum = 0 ;
static int cR = 0, cS = 0, cW = 0 , ciS = 0, ciW = 0;

class Mission{

  public:

  vector<task> inputfile, inputfile2, que, que2 ;
  vector<data> abortList, timeOutList, doneList ;

  void output_file( string fileNum, string which_type ){
      ofstream tempout ;
      string fileName = which_type + fileNum + ".txt" ;
      tempout.open ( fileName ) ;

      float a, t, d ;
      tempout << "\t[Abort List]\n" ;
      if ( which_type == "one" ) tempout << "\tOID\tDelay\tAbort\n" ;
      if ( which_type == "two" ) tempout << "\tOID\tCID\tDelay\tAbort\n" ;
      int total_delay = 0 ;
      for ( int i = 1 ; !abortList.empty() ; i++ ) {
        tempout << "(" << i << ")" << "\t" ;
        tempout << abortList[0].oid << "\t" ;
        if ( which_type == "two" ) tempout << abortList[0].cid << "\t" ;
        tempout << abortList[0].delay << "\t" ;
        tempout << abortList[0].abort_departure << "\n" ;
        total_delay = total_delay + abortList[0].delay ;
        abortList.erase( abortList.begin() ) ;
        a = i ;
      }

      tempout << "\t[Timeout List]\n" ;
      if ( which_type == "one" ) tempout << "\tOID\tDelay\tDeparture\n" ;
      if ( which_type == "two" ) tempout << "\tOID\tCID\tDelay\tDeparture\n" ;
      for ( int i = 1 ; !timeOutList.empty() ; i++ ) {
        tempout << "(" << i << ")" << "\t" ;
        tempout << timeOutList[0].oid << "\t" ;
        if ( which_type == "two" ) tempout << timeOutList[0].cid << "\t" ;
        tempout << timeOutList[0].delay << "\t" ;
        tempout << timeOutList[0].abort_departure << "\n" ;
        total_delay = total_delay + timeOutList[0].delay ;
        timeOutList.erase( timeOutList.begin() ) ;
        t = i ;
      }

      tempout << "\t[Done List]\n" ;
      for ( int i = 1 ; !doneList.empty() ; i++ ) {
        tempout << "(" << i << ")" << "\t" ;
        tempout << doneList[0].oid << "\t" ;
        if ( which_type == "two" ) tempout << doneList[0].cid << "\t" ;
        tempout << doneList[0].delay << "\t" ;
        tempout << doneList[0].abort_departure << "\n" ;
        doneList.erase( doneList.begin() ) ;
        d = i ;
      }

      float fp = ( a+t ) / ( a+t+d ) ;
      fp = fp * 100 ;
      fp = (double)((int)(fp*100)/100.0);
      tempout << "[Total Delay]\n" << total_delay << " minute.\n" ;
      tempout << "[Failure Percentage]\n" << fp << "%." ;

      tempout.close() ;
      inputfile.clear() ;
      abortList.clear() ;
      timeOutList.clear() ;
      doneList.clear() ;
      que.clear() ;
  }

  void do_que ( int & time ){
      data tempdata ;
      while ( time <= inputfile[0].arrival ){

            if ( que[0].timeout > time ){
                if ( que[0].arrival > time )
                    time = que[0].arrival ;
                time = time + que[0].duration ;
                if ( que[0].timeout >= time ){
                    tempdata.oid = que[0].oid ;
                    tempdata.cid = 1 ;
                    tempdata.delay = time - que[0].arrival - que[0].duration ;
                    tempdata.abort_departure = time ;
                    doneList.push_back( tempdata ) ;
                    que.erase( que.begin() ) ;
                }
                else{
                    tempdata.oid = que[0].oid ;
                    tempdata.cid = 1 ;
                    tempdata.delay = time - que[0].arrival - que[0].duration ;
                    tempdata.abort_departure = time ;
                    timeOutList.push_back( tempdata ) ;
                    que.erase( que.begin() ) ;
                }
            }
            else{
                tempdata.oid = que[0].oid ;
                tempdata.cid = 1 ;
                tempdata.delay = time - que[0].arrival ;
                tempdata.abort_departure = time ;
                abortList.push_back( tempdata ) ;
                que.erase( que.begin() ) ;
            }

            if ( que.empty() ) break ;
      }
  }

  void do_que2 ( int & time ){
      data tempdata ;
      while ( time <= inputfile[0].arrival ){

            if ( que2[0].timeout > time ){
                if ( que2[0].arrival > time )
                    time = que2[0].arrival ;
                time = time + que2[0].duration ;
                if ( que2[0].timeout >= time ){
                    tempdata.oid = que2[0].oid ;
                    tempdata.cid = 2 ;
                    tempdata.delay = time - que2[0].arrival - que2[0].duration ;
                    tempdata.abort_departure = time ;
                    doneList.push_back( tempdata ) ;
                    que2.erase( que2.begin() ) ;
                }
                else{
                    tempdata.oid = que2[0].oid ;
                    tempdata.cid = 2 ;
                    tempdata.delay = time - que2[0].arrival - que2[0].duration ;
                    tempdata.abort_departure = time ;
                    timeOutList.push_back( tempdata ) ;
                    que2.erase( que2.begin() ) ;
                }
            }
            else{
                tempdata.oid = que2[0].oid ;
                tempdata.cid = 2 ;
                tempdata.delay = time - que2[0].arrival ;
                tempdata.abort_departure = time ;
                abortList.push_back( tempdata ) ;
                que2.erase( que2.begin() ) ;
            }

            if ( que2.empty() ) break ;
      }
  }

  void input_empty_do_que( int & c1_time ){
      data tempdata ;
      if ( que[0].timeout > c1_time ){
          if ( que[0].arrival > c1_time )
                c1_time = que[0].arrival ;
          c1_time = c1_time + que[0].duration ;
          if ( que[0].timeout >= c1_time ){
                  tempdata.oid = que[0].oid ;
                  tempdata.cid = 1 ;
                  tempdata.delay = c1_time - que[0].arrival - que[0].duration ;
                  tempdata.abort_departure = c1_time ;
                  doneList.push_back( tempdata ) ;
                  que.erase( que.begin() ) ;
          }
          else{
              tempdata.oid = que[0].oid ;
              tempdata.cid = 1 ;
              tempdata.delay = c1_time - que[0].arrival - que[0].duration ;
              tempdata.abort_departure = c1_time ;
              timeOutList.push_back( tempdata ) ;
              que.erase( que.begin() ) ;
          }
      }
      else{
          tempdata.oid = que[0].oid ;
          tempdata.cid = 1 ;
          tempdata.delay = c1_time - que[0].arrival ;
          tempdata.abort_departure = c1_time ;
          abortList.push_back( tempdata ) ;
          que.erase( que.begin() ) ;
      }
  }

  void input_empty_do_que2( int & c2_time ){
      data tempdata ;
      if ( que2[0].timeout > c2_time ){
          if ( que2[0].arrival > c2_time )
                c2_time = que2[0].arrival ;
          c2_time = c2_time + que2[0].duration ;
          if ( que2[0].timeout >= c2_time ){
              tempdata.oid = que2[0].oid ;
              tempdata.cid = 2 ;
              tempdata.delay = c2_time - que2[0].arrival - que2[0].duration ;
              tempdata.abort_departure = c2_time ;
              doneList.push_back( tempdata ) ;
              que2.erase( que2.begin() ) ;
          }
          else{
              tempdata.oid = que2[0].oid ;
              tempdata.cid = 2 ;
              tempdata.delay = c2_time - que2[0].arrival - que2[0].duration ;
              tempdata.abort_departure = c2_time ;
              timeOutList.push_back( tempdata ) ;
              que2.erase( que2.begin() ) ;
          }
      }
      else{
          tempdata.oid = que2[0].oid ;
          tempdata.cid = 2 ;
          tempdata.delay = c2_time - que2[0].arrival ;
          tempdata.abort_departure = c2_time ;
          abortList.push_back( tempdata ) ;
          que2.erase( que2.begin() ) ;
      }
  }

  void que_is_filled_abort(){
      data tempdata ;
      tempdata.oid = inputfile[0].oid ;
      tempdata.cid = 0 ;
      tempdata.delay = 0 ;
      tempdata.abort_departure = inputfile[0].arrival ;
      abortList.push_back( tempdata ) ;
  }

  void Shell_sort( string fileNum, int total ){
    ofstream tempout ;
    string fileName = "sort" + fileNum + ".txt" ;
    tempout.open ( fileName ) ;
    task temptype1 ;
    task temptype2 ;
    int i = total ;
    cS = clock() ;
    for( i = i/2 ; i > 0 ; i = i/2 ){
        for ( int j = i ; j < total ; j++ ){
            for ( int k = j-i ; k >= 0 ; k = k-i ){
                if ( inputfile[k].arrival < inputfile[k+i].arrival ){
                    break ;
                }
                else if ( inputfile[k].arrival == inputfile[k+i].arrival ){
                    if ( inputfile[k].oid > inputfile[k+i].oid ){
                        temptype1 = inputfile[k] ;
                        temptype2 = inputfile[k+i] ;
                        inputfile.erase( inputfile.begin()+k+i ) ;
                        inputfile.erase( inputfile.begin()+k ) ;
                        inputfile.insert( inputfile.begin()+k, temptype2 ) ;
                        inputfile.insert( inputfile.begin()+k+i, temptype1 ) ;
                    }
                    else
                        break ;
                }
                else if ( inputfile[k].arrival > inputfile[k+i].arrival ){
                    temptype1 = inputfile[k] ;
                    temptype2 = inputfile[k+i] ;
                    inputfile.erase( inputfile.begin()+k+i ) ;
                    inputfile.erase( inputfile.begin()+k ) ;
                    inputfile.insert( inputfile.begin()+k, temptype2 ) ;
                    inputfile.insert( inputfile.begin()+k+i, temptype1 ) ;
                }

            }
        }
    }

    cS = clock() - cS ;
    cout << "Sorting data: " << (float)cS * 1000 / CLOCKS_PER_SEC << " clocks (" << (float)cS * 1000 << ".00 ms)." << endl;
    tempout << "OID\tArrival\tDuration\tTimeOut\n" ;
    cW = clock() ;
    for ( int i = 0 ; i < total ; i++ ) {
        tempout << inputfile[i].rawR << "\n" ;
    }
    cW = clock() - cW ;
    cout << "Writing data: " << (float)cW * 1000 / CLOCKS_PER_SEC << " clocks (" << (float)cW * 1000 << ".00 ms)." << endl;
    tempout.close() ;


  } // Save

  void Insertion_sort( string fileNum, int total ){
    ofstream tempout ;
    string fileName = "insertion_sort" + fileNum + ".txt" ;
    tempout.open ( fileName ) ;
    task temptype1 ;
    task temptype2 ;
    int i = total ;
    ciS = clock() ;
    int j, tmp;

    for (i = 1; i < total; i++) {
            j = i;
            while (j > 0 && inputfile2[j-1].arrival <= inputfile2[j].arrival ) {
                if ( inputfile2[j-1].arrival == inputfile2[j].arrival ){
                    if ( inputfile2[j-1].oid > inputfile2[j].oid ){
                        temptype1 = inputfile2[j] ;
                        temptype2 = inputfile2[j-1] ;
                        inputfile2.erase( inputfile2.begin()+j ) ;
                        inputfile2.erase( inputfile2.begin()+j-1 ) ;
                        inputfile2.insert( inputfile2.begin()+j-1, temptype2 ) ;
                        inputfile2.insert( inputfile2.begin()+j, temptype1 ) ;
                    }
                    else
                        break ;
                }
                else if ( inputfile2[j-1].arrival < inputfile2[j].arrival ){
                    temptype1 = inputfile2[j] ;
                    temptype2 = inputfile2[j-1] ;
                    inputfile2.erase( inputfile2.begin()+j ) ;
                    inputfile2.erase( inputfile2.begin()+j-1 ) ;
                    inputfile2.insert( inputfile2.begin()+j-1, temptype2 ) ;
                    inputfile2.insert( inputfile2.begin()+j, temptype1 ) ;
                }

                j-- ;
            }
      }

      for( i = i/2 ; i > 0 ; i = i/2 ){
        for ( int j = i ; j < total ; j++ ){
            for ( int k = j-i ; k >= 0 ; k = k-i ){
                if ( inputfile2[k].arrival < inputfile2[k+i].arrival ){
                    break ;
                }
                else if ( inputfile2[k].arrival == inputfile2[k+i].arrival ){
                    if ( inputfile2[k].oid > inputfile2[k+i].oid ){
                        temptype1 = inputfile2[k] ;
                        temptype2 = inputfile2[k+i] ;
                        inputfile2.erase( inputfile2.begin()+k+i ) ;
                        inputfile2.erase( inputfile2.begin()+k ) ;
                        inputfile2.insert( inputfile2.begin()+k, temptype2 ) ;
                        inputfile2.insert( inputfile2.begin()+k+i, temptype1 ) ;
                    }
                    else
                        break ;
                }
                else if ( inputfile2[k].arrival > inputfile2[k+i].arrival ){
                    temptype1 = inputfile2[k] ;
                    temptype2 = inputfile2[k+i] ;
                    inputfile2.erase( inputfile2.begin()+k+i ) ;
                    inputfile2.erase( inputfile2.begin()+k ) ;
                    inputfile2.insert( inputfile2.begin()+k, temptype2 ) ;
                    inputfile2.insert( inputfile2.begin()+k+i, temptype1 ) ;
                }

            }
        }
    }

    ciS = clock() - ciS ;
    cout << "Sorting data: " << (float)cS * 1000 / CLOCKS_PER_SEC << " clocks (" << (float)cS * 1000 << ".00 ms)." << endl;
    tempout << "OID\tArrival\tDuration\tTimeOut\n" ;
    cW = clock() ;
    for ( int i = 0 ; i < total ; i++ ) {
        tempout << inputfile2[i].rawR << "\n" ;
    }
    ciW = clock() - ciW ;
    cout << "Writing data: " << (float)cW * 1000 / CLOCKS_PER_SEC << " clocks (" << (float)cW * 1000 << ".00 ms)." << endl;
    tempout.close() ;
  }

  void Mission1(){

    task temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 401, 402, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "input" + fileNum + ".txt" ;
    tempin.open( fileName );
    while ( nofile == true ){ //�P�_���L�ɮ�
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        if ( ! tempin.is_open() ){
            printf( "### %s.txt does not exist! ###\n", fileName ) ;
            printf( "Input 401, 402, ...[0]Quit):" ) ;
            cin >> fileNum ;
            string fileName = "sort" + fileNum + ".txt" ;
            tempin.open( fileName );
        }
        else{
            nofile = false ;
        }

      } // if  end



      if ( nofile == false ){// ���ɮפF�N�}�lŪ�i�æs�J
          string raw ;
          getline( tempin, raw ) ;
          cR = clock() ;
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;
              temptype.rawR = raw ;
              temptype.oid = atoi( arr[0].c_str() ) ;
              temptype.arrival = atoi( arr[1].c_str() ) ;
              temptype.duration = atoi( arr[2].c_str() ) ;
              temptype.timeout = atoi( arr[3].c_str() ) ;

              inputfile.push_back(temptype) ;


           } // for read

           cR = clock() - cR ;
           cout << "Reading data: " << (float)cR * 1000 / CLOCKS_PER_SEC << " clocks (" << (float)cR * 1000 << ".00 ms)." << endl;
           tempin.close() ;
           inputfile2 = inputfile ;
           int si = 0 ;
           Shell_sort( fileNum, gnum ) ;

           inputfile.clear() ;
      } //if end

    } //while

  } // Mission1

  void SINGLE_simulate(){
      int c1_time = 0 ;
      data tempdata ;
      while( !inputfile.empty() ){
            if ( inputfile[0].arrival >= c1_time && !que.empty() ) do_que( c1_time ) ;

            if ( que.size() == 3 ) que_is_filled_abort() ; // 選擇廚師給單子 或者可能是滿的丟進abort
            else
                que.push_back( inputfile[0] ) ;

            if ( inputfile[0].arrival >= c1_time && !que.empty() ) do_que( c1_time ) ;

            inputfile.erase( inputfile.begin() ) ;

      }

      while ( !que.empty() ){
          input_empty_do_que( c1_time ) ;
      }

      //----------------------------------output onexxx.txt file
  }

  void Mission2(){
    task temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 401, 402, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "sort" + fileNum + ".txt" ;
    tempin.open( fileName );
    while ( nofile == true ){ //�P�_���L�ɮ�
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        if ( ! tempin.is_open() ){
            printf( "### %s.txt does not exist! ###\n", fileName ) ;
            printf( "Input 401, 402, ...[0]Quit):" ) ;
            cin >> fileNum ;
            string fileName = "sort" + fileNum + ".txt" ;
            tempin.open( fileName );
        }
        else{
            nofile = false ;
        }
      } // if  end



      if ( nofile == false ){// ���ɮפF�N�}�lŪ�i�æs�J
          string raw ;
          getline( tempin, raw ) ;
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;
              temptype.rawR = raw ;
              temptype.oid = atoi( arr[0].c_str() ) ;
              temptype.arrival = atoi( arr[1].c_str() ) ;
              temptype.duration = atoi( arr[2].c_str() ) ;
              temptype.timeout = atoi( arr[3].c_str() ) ;

              inputfile.push_back(temptype) ;


           } // for read

           tempin.close() ;
           SINGLE_simulate() ;
           output_file( fileNum, "one" ) ;
           inputfile.clear() ;
      } //if end

    } //while

  }

 /* void push_back_which_que( int c1_time, int c2_time, int c3_time ){
      bool c1_big = false, c2_big = false, c3_big = false ;
      if ( inputfile[0].arrival >= c1_time ) c1_big = true ;
      if ( inputfile[0].arrival >= c2_time ) c2_big = true ;
      if ( inputfile[0].arrival >= c3_time ) c3_big = true ;

      int _min = que.size() ;
      if ( que2.size() < _min ) _min = que2.size() ;
      if ( que3.size() < _min ) _min = que3.size() ;

      if ( c1_big && ! c2_big && ! c3_big ) que.push_back( inputfile[0] ) ;
      else if ( ! c1_big && c2_big && ! c3_big ) que2.push_back( inputfile[0] ) ;
      else if ( ! c1_big && ! c2_big && c3_big ) que3.push_back( inputfile[0] ) ;
      else {
         if ( _min == que.size() ) que.push_back( inputfile[0] ) ;
         else if ( _min == que2.size() ) que2.push_back( inputfile[0] ) ;
         else if ( _min == que3.size() ) que3.push_back( inputfile[0] ) ;
         else ;
      }
  }*/

  void DOUBLE_simulate() {
      int c1_time = 0, c2_time = 0 ;
      while( !inputfile.empty() ){
            if ( inputfile[0].arrival >= c1_time && !que.empty()  ) do_que( c1_time ) ;
            if ( inputfile[0].arrival >= c2_time && !que2.empty() ) do_que2( c2_time ) ;// 單子到達的時間大於等於廚師二的時間

            if ( que.size() == 3 && que2.size() == 3 ) que_is_filled_abort() ;
            else{
                if ( inputfile[0].arrival >= c1_time && inputfile[0].arrival < c2_time )      que.push_back( inputfile[0] ) ;
                else if ( inputfile[0].arrival < c1_time && inputfile[0].arrival >= c2_time ) que2.push_back( inputfile[0] ) ;
                else {
                    if ( que.size() > que2.size() ) que2.push_back( inputfile[0] ) ;
                    else                            que.push_back( inputfile[0] ) ;
                }
            }  // 選擇廚師給單子 或者可能是滿的丟進() end

            if ( inputfile[0].arrival >= c1_time && !que.empty()  ) do_que( c1_time ) ;
            if ( inputfile[0].arrival >= c2_time && !que2.empty() ) do_que2( c2_time ) ;

            inputfile.erase( inputfile.begin() ) ;

      }

      //--------------------queue

      while ( 1 ){
        if ( que.empty() && que2.empty() ) break ;

        if ( ( c1_time > c2_time && !que2.empty() ) || que.empty() ) input_empty_do_que2( c2_time ) ; // 給q2
        else if ( ( c1_time <= c2_time && !que.empty() ) || que2.empty() ) input_empty_do_que( c1_time ) ;
      }


      //---------------queue exit---------*/
  }

  void Mission3(){
    task temptype ;
    string fileNum ;
    ifstream tempin ;
    bool nofile = true ;
    printf( "Input 401, 402, ...[0]Quit):" ) ;
    cin >> fileNum ;
    string fileName = "sort" + fileNum + ".txt" ;
    tempin.open( fileName );
    while ( nofile == true ){ //
      if ( fileNum.size() == 1 && fileNum[0] == '0' )
          return ;
      else {
        if ( ! tempin.is_open() ){
            printf( "### %s.txt does not exist! ###\n", fileName ) ;
            printf( "Input 401, 402, ...[0]Quit):" ) ;
            cin >> fileNum ;
            string fileName = "sort" + fileNum + ".txt" ;
            tempin.open( fileName );
        }
        else{
            nofile = false ;
        }

      } // if  end



      if ( nofile == false ){// ���ɮפF�N�}�lŪ�i�æs�J
          string raw ;
          getline( tempin, raw ) ;
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;
              temptype.rawR = raw ;
              temptype.oid = atoi( arr[0].c_str() ) ;
              temptype.arrival = atoi( arr[1].c_str() ) ;
              temptype.duration = atoi( arr[2].c_str() ) ;
              temptype.timeout = atoi( arr[3].c_str() ) ;

              inputfile.push_back(temptype) ;


           } // for read

           tempin.close() ;
           DOUBLE_simulate() ;
           output_file( fileNum, "two" ) ;
           inputfile.clear() ;
      } //if end

    } //while


  }
};



void PrintMenu(){
  cout << endl << "**** Simulate FIFO Queues by SQF *****";
  cout << endl << "* 0. Quit *";
  cout << endl << "* 1. Sort a file *";
  cout << endl << "* 2. Simulate one FIFO queue *";
  cout << endl << "* 3. Simulate two queues by SQF *";
  cout << endl << "*******************************";
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
      else if ( mission > 1 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      gnum = 0 ;
      cin >> mission ;
    } // while end

} //
