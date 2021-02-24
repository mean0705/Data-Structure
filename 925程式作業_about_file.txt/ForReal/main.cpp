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
    string rawR ;//
    string cname ;//
    string drealname ;
    string dname ;//
    int tNo ;
    int sNo ;
    int gNo ;

}; // college Type

static int gnum = 0 ;

class Mission{

  public:

  vector<cT> cSet201, cSet202, cSet203, cSet204, cSet205 ;

  void Save( int filenum ){ // 存進打開的文件檔
    ofstream tempout ;
    if ( filenum == 201 )
        tempout.open ( "copy201.txt" ) ;
    else if ( filenum == 202 )
        tempout.open ( "copy202.txt" ) ;
    else if ( filenum == 203 )
        tempout.open ( "copy203.txt" ) ;
    else if ( filenum == 204 )
        tempout.open ( "copy204.txt" ) ;
    else if ( filenum == 205 )
        tempout.open ( "copy205.txt" ) ;
    else ;

        for ( int i = 0 ; i < gnum ; i++ ) {
            if ( filenum == 201 )      tempout << cSet201[i].rawR << "\n" ;
            else if ( filenum == 202 ) tempout << cSet202[i].rawR << "\n" ;
            else if ( filenum == 203 ) tempout << cSet203[i].rawR << "\n" ;
            else if ( filenum == 204 ) tempout << cSet204[i].rawR << "\n" ;
            else if ( filenum == 205 ) tempout << cSet205[i].rawR << "\n" ;
            else ;
        }
     tempout.close() ;
  } // Save



  void ReadAndSave(){
    cT temptype ;
    int knum = 0;
    bool nofile = true ;
    ifstream tempin ;
    string trash = "\0", raw = "\0" ;
    printf( "Input 201, 202, ...[0]Quit):" ) ;
    cin >> knum ;

    while ( nofile == true ){ //判斷有無檔案
      if ( knum == 0 )
          return ;
      else if ( knum == 201 ){
        tempin.open( "input201.txt" );
        if ( ! tempin.is_open() )
            printf( "### input%d.txt does not exist! ###\n", knum ) ;
        else
            nofile = false ;
      } // if  end

      else if ( knum == 202 ){
        tempin.open( "input202.txt" );
        if ( ! tempin.is_open() )
            printf( "### input%d.txt does not exist! ###\n", knum ) ;
        else
            nofile = false ;
      } // else if  end

      else if ( knum == 203 ){
        tempin.open( "input203.txt" );
        if ( ! tempin.is_open() )
            printf( "### input%d.txt does not exist! ###\n", knum ) ;
        else
            nofile = false ;
      } // if  end

      else if ( knum == 204 ){
        tempin.open( "input204.txt" );
        if ( ! tempin.is_open() )
            printf( "### input%d.txt does not exist! ###\n", knum ) ;
        else
            nofile = false ;
      } // if  end

      else if ( knum == 205 ){
        tempin.open( "input205.txt" );
        if ( ! tempin.is_open() )
            printf( "### input%d.txt does not exist! ###\n", knum ) ;
        else
            nofile = false ;
      } // if  end

      else if ( knum > 205 && knum < 9999 ) {
        printf( "### input%d.txt does not exist! ###\n", knum ) ;
        printf( "Input 201, 202, ...[0]Quit):" ) ;
        cin >> knum ;
      } // else if
      else if ( knum < 201 && knum > 0 ) {
        printf( "### input%d.txt does not exist! ###\n", knum ) ;
        printf( "Input 201, 202, ...[0]Quit):" ) ;
        cin >> knum ;
      } // else if
      else ;

      if ( nofile == false ){  // 有檔案了就開始讀進並存入
          for ( int times = 0 ; getline( tempin, trash ) && times < 2 ; times++ );
          for ( string token ; getline( tempin, raw ) ; gnum++ ){
              temptype.rawR = raw ;
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype.cname = arr[0] ;
              temptype.dname = arr[2] ;
              temptype.drealname = arr[3] ;
              if ( arr[6].size() > 3 ){
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), ','));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
              }
              temptype.sNo = atoi( arr[6].c_str() ) ;
              if ( arr[7].size() > 3 ){
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), ','));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
              }
              temptype.tNo = atoi( arr[7].c_str() ) ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }
              temptype.gNo = atoi( arr[8].c_str() ) ;

              if ( knum == 201 )      cSet201.push_back(temptype) ;
              else if ( knum == 202 ) cSet202.push_back(temptype) ;
              else if ( knum == 203 ) cSet203.push_back(temptype) ;
              else if ( knum == 204 ) cSet204.push_back(temptype) ;
              else if ( knum == 205 ) cSet205.push_back(temptype) ;
              else ;


           } // for read

           tempin.close() ;
           Save( knum ) ;
           printf( "Number of records = %d\n", gnum ) ;
      } //if end
    } //while
  } // ReadAndSave




  void Filter(){
    ifstream tempin ;
    int filenum = 0 ;
    bool hnofile = true ;
    printf( "Input 201, 202, ...[0]Quit):" ) ;
    cin >> filenum ;
    printf( "\n" ) ;
    while ( hnofile == true ){ // 判斷有無檔案

        if ( filenum == 0 ){
            return ;
        }
        else if ( filenum == 201 ){
            tempin.open( "copy201.txt" );
            if ( ! tempin.is_open() ){
                tempin.close() ;
                printf( "### copy%d.txt does not exist! ###\n", filenum ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum ;
            }
            else{
                hnofile = false ;
            }
        }
        else if ( filenum == 202 ){
            tempin.open( "copy202.txt" );
            if ( ! tempin.is_open() ){
                tempin.close() ;
                printf( "### copy%d.txt does not exist! ###\n", filenum ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum ;
            }
            else
                hnofile = false ;
        }
        else if ( filenum == 203 ){
            tempin.open( "copy203.txt" );
            if ( ! tempin.is_open() ){
                tempin.close() ;
                printf( "### copy%d.txt does not exist! ###\n", filenum ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum ;
            }
            else
                hnofile = false ;
        }
        else if ( filenum == 204 ){
            tempin.open( "copy204.txt" );
            if ( ! tempin.is_open() ){
                tempin.close() ;
                printf( "### copy%d.txt does not exist! ###\n", filenum ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum ;
            }
            else
                hnofile = false ;
        }
        else if ( filenum == 205 ){
            tempin.open( "copy205.txt" );
            if ( ! tempin.is_open() ){
                tempin.close() ;
                printf( "### copy%d.txt does not exist! ###\n", filenum ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum ;
            }
            else
                hnofile = false ;
        } // else if
        else{
            printf( "### copy%d.txt does not exist! ###\n", filenum ) ;
            printf( "Input 201,202..." ) ;
            cin >> filenum ;
        }
        ifstream tempin ;
    } // while

    int lims = 0 ;
    int limg = 0 ;
    int limt = 0 ;
    printf( "Input a lower bound on the number of students: " ) ;
    cin >> lims ;
    printf( "\nInput a lower bound on the number of graduates: " ) ;
    cin >> limg ;
    printf( "\n" ) ;



    string trash = "\0", raw = "\0" ;
    cT temptype ;
    if ( filenum == 201 ) cSet201.clear() ;
    else if ( filenum == 202 ) cSet202.clear() ;
    else if ( filenum == 203 ) cSet203.clear() ;
    else if ( filenum == 204 ) cSet204.clear() ;
    else if ( filenum == 205 ) cSet205.clear() ;


    for ( string token ; getline( tempin, raw ) ; gnum++ ){ // 有檔案就讀進
              temptype.rawR = raw ;
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype.cname = arr[0] ;
              temptype.dname = arr[2] ;http://140.135.11.167:3030/JackySystem/index.html
              temptype.drealname = arr[3] ;
              if ( arr[6].size() > 3 ){
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), ','));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
              }
              temptype.sNo = atoi( arr[6].c_str() ) ;
              if ( arr[7].size() > 3 ){
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), ','));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
              }
              temptype.tNo = atoi( arr[7].c_str() ) ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }

              temptype.gNo = atoi( arr[8].c_str() ) ;

              if ( filenum == 201 )      cSet201.push_back(temptype) ;
              else if ( filenum == 202 ) cSet202.push_back(temptype) ;
              else if ( filenum == 203 ) cSet203.push_back(temptype) ;
              else if ( filenum == 204 ) cSet204.push_back(temptype) ;
              else if ( filenum == 205 ) cSet205.push_back(temptype) ;
              else ;


    } // for read

    ofstream tempout ; //開檔案準備比對並存入
    vector<cT> cSettemp ;
    if ( filenum == 201 ){
        cSettemp = cSet201 ;
        tempout.open( "copy201.txt" ) ;
    }
    else if ( filenum == 202 ){
        cSettemp = cSet202 ;
        tempout.open( "copy202.txt" ) ;
    }
    else if ( filenum == 203 ) {
        cSettemp = cSet203 ;
        tempout.open( "copy203.txt" ) ;
    }

    else if ( filenum == 204 ){
        cSettemp = cSet204 ;
        tempout.open( "copy204.txt" ) ;
    }
    else if ( filenum == 205 ) {
        cSettemp = cSet205 ;
        tempout.open( "copy205.txt" ) ;
    }
    else ;

    int school = 0 ;
    for ( int i = 0 ; i < cSettemp.size() ; i++ ){ // 加入限制老師人數
        if ( cSettemp[i].sNo >= lims && cSettemp[i].gNo >= limg ){
            tempout << cSettemp[i].rawR << "\n" ;
            school++ ;
        }
    } // for end

    tempout.close() ;
    printf( "Number of records = %d\n", school ) ;
  }


  void Merge() {

    string trash = "\0", raw = "\0" ;
    cT temptype ;
    int filenum1 = 0 ;
    int filenum2 = 0 ;
    char filechar1 = '\0' ;
    ifstream file1 ;
    ifstream file2 ;
    bool nofile1 = true ;
    bool nofile2 = true ;
    printf( "Input 201, 202, ...[0]Quit):" ) ;
    scanf( "%c", &filechar1 ) ;

    while ( nofile1 == true ){ // 判斷第一個檔案有無
        if ( filenum1 == 0 )
          return ;

        else if ( filenum1 == 201 ){
            file1.open( "copy201.txt" );
            if ( ! file1.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum1 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum1 ;
            }
            else
                nofile1 = false ;
        }
        else if ( filenum1 == 202 ){
            file1.open( "copy202.txt" );
            if ( ! file1.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum1 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum1 ;
            }
            else
                nofile1 = false ;
        }
        else if ( filenum1 == 203 ){
            file1.open( "copy203txt" );
            if ( ! file1.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum1 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum1 ;
            }
            else
                nofile1 = false ;
        }
        else if ( filenum1 == 204 ){
            file1.open( "copy204.txt" );
            if ( ! file1.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum1 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum1 ;
            }
            else
                nofile1 = false ;
        }
        else if ( filenum1 == 205 ){
            file1.open( "copy205.txt" );
            if ( ! file1.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum1 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum1 ;
            }

            else
                nofile1 = false ;
        } // else if
        else{
            printf( "### copy%d.txt does not exist! ###\n", filenum1 ) ;
            printf( "Input 201,202..." ) ;
            cin >> filenum1 ;
        }

        ifstream file1 ;
    } // while

    if ( filenum1 == 201 ) cSet201.clear() ;
    else if ( filenum1 == 202 ) cSet202.clear() ;
    else if ( filenum1 == 203 ) cSet203.clear() ;
    else if ( filenum1 == 204 ) cSet204.clear() ;
    else if ( filenum1 == 205 ) cSet205.clear() ;

    printf( "Input 201, 202, ...[0]Quit):" ) ;
    cin >> filenum2 ;
    while ( nofile2 == true ){ // 判斷第二個檔案有無
        if ( filenum2 == 0 )
          return ;

        if ( filenum2 == 201 ){
            file2.open( "copy201.txt" );
            if ( ! file2.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum2 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum2 ;
            }
            else
                nofile2 = false ;
        }
        else if ( filenum2 == 202 ){
            file2.open( "copy202.txt" );
            if ( ! file2.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum2 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum2 ;
            }
            else
                nofile2 = false ;
        }
        else if ( filenum2 == 203 ){
            file2.open( "copy203.txt" );
            if ( ! file2.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum2 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum2 ;
            }
            else
                nofile2 = false ;
        }
        else if ( filenum2 == 204 ){
            file2.open( "copy204.txt" );
            if ( ! file2.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum2 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum2 ;
            }
            else
                nofile2 = false ;
        }
        else if ( filenum2 == 205 ){
            file2.open( "copy205.txt" );
            if ( ! file2.is_open() ){
                printf( "### copy%d.txt does not exist! ###\n", filenum2 ) ;
                printf( "Input 201,202..." ) ;
                cin >> filenum2 ;
            }
            else
                nofile2 = false ;
        } // else if
        else{
            printf( "### copy%d.txt does not exist! ###\n", filenum2 ) ;
            printf( "Input 201,202..." ) ;
            cin >> filenum2 ;
        }

        ifstream file2 ;
    } // while

    if ( filenum2 == 201 ) cSet201.clear() ;
    else if ( filenum2 == 202 ) cSet202.clear() ;
    else if ( filenum2 == 203 ) cSet203.clear() ;
    else if ( filenum2 == 204 ) cSet204.clear() ;
    else if ( filenum2 == 205 ) cSet205.clear() ;

    for ( string token ; getline( file1, raw ) ; gnum++ ){ // 讀入檔案1
              temptype.rawR = raw ;
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype.cname = arr[0] ;
              temptype.dname = arr[2] ;
              temptype.drealname = arr[3] ;
              if ( arr[6].size() > 3 ){
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), ','));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
              }
              temptype.sNo = atoi( arr[6].c_str() ) ;
              if ( arr[7].size() > 3 ){
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), ','));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
              }
              temptype.tNo = atoi( arr[7].c_str() ) ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }
              temptype.gNo = atoi( arr[8].c_str() ) ;

              if ( filenum1 == 201 )      cSet201.push_back(temptype) ;
              else if ( filenum1 == 202 ) cSet202.push_back(temptype) ;
              else if ( filenum1 == 203 ) cSet203.push_back(temptype) ;
              else if ( filenum1 == 204 ) cSet204.push_back(temptype) ;
              else if ( filenum1 == 205 ) cSet205.push_back(temptype) ;
              else ;


    } // for read

    for ( string token ; getline( file2, raw ) ; gnum++ ){ // 讀入檔案2
              temptype.rawR = raw ;
              vector<string> arr ;
              istringstream delim(raw);
              while(getline(delim,token,'\t')) arr.push_back(token) ;

              temptype.cname = arr[0] ;
              temptype.dname = arr[2] ;
              temptype.drealname = arr[3] ;
              if ( arr[6].size() > 3 ){
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), ','));
                  arr[6].erase(find(arr[6].begin(), arr[6].end(), '"'));
              }
              temptype.sNo = atoi( arr[6].c_str() ) ;
              if ( arr[7].size() > 3 ){
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), ','));
                  arr[7].erase(find(arr[7].begin(), arr[7].end(), '"'));
              }
              temptype.tNo = atoi( arr[7].c_str() ) ;
              if ( arr[8].size() > 3 ){
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), ','));
                  arr[8].erase(find(arr[8].begin(), arr[8].end(), '"'));
              }
              temptype.gNo = atoi( arr[8].c_str() ) ;

              if ( filenum2 == 201 )      cSet201.push_back(temptype) ;
              else if ( filenum2 == 202 ) cSet202.push_back(temptype) ;
              else if ( filenum2 == 203 ) cSet203.push_back(temptype) ;
              else if ( filenum2 == 204 ) cSet204.push_back(temptype) ;
              else if ( filenum2 == 205 ) cSet205.push_back(temptype) ;
              else ;


    } // for read


    ofstream tempmerge ;
    vector<cT> cSmerge, cSettemp2 ;
    vector<cT>::iterator it ;
    if ( filenum1 == 201 )
        cSmerge = cSet201 ;
    else if ( filenum1 == 202 )
        cSmerge = cSet202 ;
    else if ( filenum1 == 203 )
        cSmerge = cSet203 ;
    else if ( filenum1 == 204 )
        cSmerge = cSet204 ;
    else if ( filenum1 == 205 )
        cSmerge = cSet205 ;

    if ( filenum2 == 201 )
        cSettemp2 = cSet201 ;
    else if ( filenum2 == 202 )
        cSettemp2 = cSet202 ;
    else if ( filenum2 == 203 )
        cSettemp2 = cSet203 ;
    else if ( filenum2 == 204 )
        cSettemp2 = cSet204 ;
    else if ( filenum2 == 205 )
        cSettemp2 = cSet205 ;

    it = cSmerge.begin() ;

    if ( filenum1 == 201 && filenum2 == 202 ) tempmerge.open( "output201_202.txt" );
    else if ( filenum1 == 201 && filenum2 == 203 ) tempmerge.open( "output201_203.txt" );
    else if ( filenum1 == 201 && filenum2 == 204 ) tempmerge.open( "output201_204.txt" );
    else if ( filenum1 == 201 && filenum2 == 205 ) tempmerge.open( "output201_205.txt" );
    else if ( filenum1 == 202 && filenum2 == 203 ) tempmerge.open( "output202_203.txt" );
    else if ( filenum1 == 202 && filenum2 == 204 ) tempmerge.open( "output202_204.txt" );
    else if ( filenum1 == 202 && filenum2 == 205 ) tempmerge.open( "output202_205.txt" );
    else if ( filenum1 == 203 && filenum2 == 204 ) tempmerge.open( "output203_204.txt" );
    else if ( filenum1 == 203 && filenum2 == 205 ) tempmerge.open( "output203_205.txt" );
    else if ( filenum1 == 204 && filenum2 == 205 ) tempmerge.open( "output204_205.txt" );
    else if ( filenum2 == 201 && filenum1 == 202 ) tempmerge.open( "output202_201.txt" );
    else if ( filenum2 == 201 && filenum1 == 203 ) tempmerge.open( "output203_201.txt" );
    else if ( filenum2 == 201 && filenum1 == 204 ) tempmerge.open( "output204_201.txt" );
    else if ( filenum2 == 201 && filenum1 == 205 ) tempmerge.open( "output205_201.txt" );
    else if ( filenum2 == 202 && filenum1 == 203 ) tempmerge.open( "output203_202.txt" );
    else if ( filenum2 == 202 && filenum1 == 204 ) tempmerge.open( "output204_202.txt" );
    else if ( filenum2 == 202 && filenum1 == 205 ) tempmerge.open( "output205_202.txt" );
    else if ( filenum2 == 203 && filenum1 == 204 ) tempmerge.open( "output204_203.txt" );
    else if ( filenum2 == 203 && filenum1 == 205 ) tempmerge.open( "output205_203.txt" );
    else if ( filenum2 == 204 && filenum1 == 205 ) tempmerge.open( "output205_204.txt" );

    int b = 0 ;
    int h = 0 ;
    bool havenext = false ;
    bool in = false ;
    for ( int a = 0 ; a < cSettemp2.size() ; a++ ){ // 開始比對
        b = 0 ;
        while (  b < cSmerge.size() ){
            if ( cSettemp2[a].cname == cSmerge[b].cname && cSettemp2[a].dname == cSmerge[b].dname
                && cSettemp2[a].drealname == cSmerge[b].drealname ){ //一開始先判斷是不是三者都相同
                   while ( cSettemp2[a].cname == cSmerge[b].cname && cSettemp2[a].dname == cSmerge[b].dname ){
                        // 如果是 繼續往下判斷 直到系的號碼不同
                        if ( cSettemp2[a].drealname == cSmerge[b].drealname ){
                            // 如果在判斷中有遇到跟自己系的名字一模一樣的 就要跟著
                            h = b ;
                            havenext = true ;
                        }
                      b++ ;
                   }
                   if ( havenext == true )
                       cSmerge.insert( it + h + 1, cSettemp2[a] ) ;
                   else
                       cSmerge.insert( it + b, cSettemp2[a] ) ;

                   in = true ;
                   break ;
            } // if end

            b++ ;

        } // while
        if ( in == false ){ // 相同學校但不同科系
            b = 0 ;
            while (  b < cSmerge.size() ){
              if ( cSettemp2[a].cname == cSmerge[b].cname ){
                     while ( cSettemp2[a].cname == cSmerge[b].cname ){
                        b++ ;
                     }
                     cSmerge.insert( it + b, cSettemp2[a] ) ;
                     in = true ;
                     break ;
              } // if end

              b++ ;

          } // while
        }

        if ( in == false ) // 沒有一樣學校的
            cSmerge.push_back (cSettemp2[a] ) ;

        it = cSmerge.begin() ;
        in = false ;

    } // for

    if ( tempmerge.is_open() ){
        for ( int i = 0 ; i < cSmerge.size() ; i++ )
            tempmerge << cSmerge[i].rawR << "\n" ;
    }
    tempmerge.close() ;

    printf( "Number of records = %d\n", cSmerge.size() ) ;
  }
};



void PrintMenu(){
  cout << endl << "*** File Object Manipulator ***";
  cout << endl << "* 0. QUIT *";
  cout << endl << "* 1. COPY (Read & Save a file) *";
  cout << endl << "* 2. FILTER (Reduce a file) *";
  cout << endl << "* 3. MERGE (Join two files) *";
  cout << endl << "*********************************";
  cout << endl << "Input a choice(0, 1, 2, 3): ";


} // PrintMenu()

int main() {
    PrintMenu() ;
    int mission ;
    Mission Miss ;

    cin >> mission ;
    while ( mission != 0 ) {
      if ( mission == 1 )      Miss.ReadAndSave() ;
      else if ( mission == 2 ) Miss.Filter() ;
      else if ( mission == 3 ) Miss.Merge() ;
      else if ( mission > 3 && mission < 9999 ) printf( "Command does Not Exist!\n" ) ;
      else break ;

      PrintMenu() ;
      gnum = 0 ;
      cin >> mission ;
    } // while end

} //
