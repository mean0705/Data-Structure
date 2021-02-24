#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std ;

static int FileN = 0 ;
static ifstream input ;
static ifstream input2 ;
static ofstream output ;
static int Count = 0 ;

typedef struct DataBase {
    string schoolNum = "\0" ;
    string schoolName = "\0" ;
    string departmentNum = "\0" ;
    string departmentName = "\0" ;
    int student = 0 ;
    int graduated = 0 ;
    string wholeSentence = "\0" ;
} Data ;

class FunctionNVarieblesArea {
    vector<DataBase> dataBase ;

public:
    void inputData( vector<DataBase> & data ) {
        DataBase tempData ;
        string sentence = "\0" ;

        while ( getline( input, sentence ) ) {
            // cout << sentence << endl ;
            tempData.wholeSentence = sentence ;
            vector<string> cut ;
            string token ;
            istringstream cutStream( sentence ) ;

            while( getline( cutStream, token, '\t' ) )
                cut.push_back( token ) ;

            tempData.schoolNum = cut[0] ;
            tempData.schoolName = cut[1] ;
            tempData.departmentNum = cut[2] ;
            tempData.departmentName = cut[3] ;

            if ( cut[6].size() > 3 ) {
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), ',' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.student = atoi( cut[6].c_str() ) ;

            if ( cut[8].size() > 3 ) {
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), ',' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.graduated = atoi( cut[8].c_str() ) ;
            data.push_back( tempData ) ;
        } // while()
    } // inputData()

    void inputData2( vector<DataBase> & data ) {
        DataBase tempData ;
        string sentence = "\0" ;

        while ( getline( input2, sentence ) ) {
            // cout << sentence << endl ;
            tempData.wholeSentence = sentence ;
            vector<string> cut ;
            string token ;
            istringstream cutStream( sentence ) ;

            while( getline( cutStream, token, '\t' ) )
                cut.push_back( token ) ;

            tempData.schoolNum = cut[0] ;
            tempData.schoolName = cut[1] ;
            tempData.departmentNum = cut[2] ;
            tempData.departmentName = cut[3] ;

            if ( cut[6].size() > 3 ) {
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), ',' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.student = atoi( cut[6].c_str() ) ;

            if ( cut[8].size() > 3 ) {
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), ',' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.graduated = atoi( cut[8].c_str() ) ;
            data.push_back( tempData ) ;
        } // while()
    } // inputData()

    void ReadNCopy() {
        DataBase tempData ;
        dataBase.clear() ;
        string useless = "\0" ;
        getline( input, useless ) ;
        getline( input, useless ) ;
        getline( input, useless ) ;

        while ( getline( input, tempData.wholeSentence ) ) {
            Count ++ ;
            dataBase.push_back( tempData ) ;
        } // input the data to dataBase

        if ( FileN == 201 ) output.open( "copy201.txt" ) ;
        else if ( FileN == 202 ) output.open( "copy202.txt" ) ;
        else if ( FileN == 203 ) output.open( "copy203.txt" ) ;
        else if ( FileN == 204 ) output.open( "copy204.txt" ) ;
        else if ( FileN == 205 ) output.open( "copy205.txt" ) ;

        for ( int i = 0 ; i < dataBase.size() - 1 ; i ++ ) output << dataBase[i].wholeSentence << endl ;
        output << dataBase[dataBase.size()-1].wholeSentence ;
    } // ReadNCopy()

    void Filter() {
        dataBase.clear() ;
        int studentNum = 0 ;
        int graduatedNum = 0 ;
        cout << "Please enter number of students that you want to filter:" << endl ;
        cin >> studentNum ;
        cout << "Please enter number of graduated students that you want to filter:" << endl ;
        cin >> graduatedNum ;
        inputData( dataBase ) ;
        cout << studentNum << "  " << graduatedNum << endl ;

        /*for ( int i = 0 ; i < dataBase.size() ; i ++ )
            cout << dataBase[i].schoolNum << "  " << dataBase[i].schoolName << "  " << dataBase[i].student << "  " << dataBase[i].graduated << endl ;*/

        if ( FileN == 201 ) output.open( "copy201.txt" ) ;
        else if ( FileN == 202 ) output.open( "copy202.txt" ) ;
        else if ( FileN == 203 ) output.open( "copy203.txt" ) ;
        else if ( FileN == 204 ) output.open( "copy204.txt" ) ;
        else if ( FileN == 205 ) output.open( "copy205.txt" ) ;

        for ( int i = 0 ; i < dataBase.size() ; i ++ ) {
            if ( dataBase[i].student > studentNum && dataBase[i].graduated > graduatedNum ) {
                // cout << dataBase[i].student << "  " << dataBase[i].graduated << endl ;
                output << dataBase[i].wholeSentence << endl ;
                Count ++ ;
            } // find the one match
        } // filter and print
    } // Filter()

    void Merge() {
        vector<DataBase> mergeDataBase1 ;
        vector<DataBase> mergeDataBase2 ;
        inputData( mergeDataBase1 ) ;
        inputData2( mergeDataBase2 ) ;
        bool NoSame = false ;

        /*for ( int i = 0 ; i < mergeDataBase2.size() ; i ++ ) {
            for ( int j = 0 ; j < mergeDataBase1.size() ; j ++ ) {
                if( mergeDataBase2[i].schoolNum == mergeDataBase1[j].schoolNum ) {
                    if( mergeDataBase2[i].departmentNum == mergeDataBase1[j].departmentNum &&
                       mergeDataBase2[i].departmentNum != mergeDataBase1[j + 1].departmentNum ) // 下一個就是別系 = 本系最後一個
                        mergeDataBase1.insert( mergeDataBase1[j + 1], mergeDataBase2[i] ) ;
                } // same school num & same department num

                else if( mergeDataBase2[i].schoolNum == mergeDataBase1[j].schoolNum ){
                    if( mergeDataBase2[i].schoolNum != mergeDataBase1[j + 1].schoolNum ) // 下一個就是別校 = 本校最後一個
                        mergeDataBase1.insert( mergeDataBase1[j + 1], mergeDataBase2[i] );
                } // same school num & not same departmnet num

                else
                    NoSame = true;// not same school num & not same department num
            } // for


            if ( NoSame ) {
                mergeDataBase1.push_back( mergeDataBase2[i] ) ;
                NoSame = false;
            } // if
        } // for*/
    } // Merge()

} ;

int main() {
    int command = 0 ;
    bool continueOrNot = false ;
    FunctionNVarieblesArea Class ;

    do {
        cout << "*****************************************" << endl ; // welcome message
        cout << "*****    File Object Manipulator    *****" << endl ;
        cout << "***** 0 : Quit                      *****" << endl ;
        cout << "***** 1 : Read, count and copy      *****" << endl ;
        cout << "***** 2 : Filter and update         *****" << endl ;
        cout << "***** 3 : Merge two files           *****" << endl ;
        cout << "*****************************************" << endl ;
        cout << endl << "Please enter your choice :" << endl ;

        cin >> command ; // read in user command

        if ( command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit

        else if ( command > 3 || command < 0 ) {
            cout << "Error command! please enter an acceptable command :" << endl << endl ;
            continueOrNot = true ;
        } // wrong command

        else if ( command == 1 ) { // read, count and copy
            bool function1Confirm = false ;

            do {
                cout << "Please enter the file  ( 201 - 205 ) you want to read and copy or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == 0 ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else if ( FileN != 201 && FileN != 202 && FileN != 203 && FileN != 204 && FileN != 205 )
                    cout << "*****  input" << FileN << ".txt does not exist!  *****" << endl ;

                else {
                    if ( FileN == 201 ) input.open( "input201.txt" ) ;
                    else if ( FileN == 202 ) input.open( "input202.txt" ) ;
                    else if ( FileN == 203 ) input.open( "input203.txt" ) ;
                    else if ( FileN == 204 ) input.open( "input204.txt" ) ;
                    else if ( FileN == 205 ) input.open( "input205.txt" ) ;
                    function1Confirm = true ;
                    continueOrNot = true ;
                    Class.ReadNCopy() ;
                } // 204
            } while( ! function1Confirm ) ;

            cout << "Data Count: " << Count << endl ;
            Count = 0 ;
            FileN = 0 ;
            input.close() ;
            output.close() ;
        } // mission 1

        else if ( command == 2 ) {
            bool function2Confirm = false ;

            do {
                cout << "Please enter the file ( 201 - 205 ) you want to filter or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == 0 ) {
                    function2Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else if ( FileN != 201 && FileN != 202 && FileN != 203 && FileN != 204 && FileN != 205 )
                    cout << "*****  copy" << FileN << ".txt does not exist!  *****" << endl ;

                else if ( FileN == 201 ) {
                    input.open( "copy201.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy201.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 201
                } // test if you have already create a copy file

                else if ( FileN == 202 ) {
                    input.open( "copy202.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy202.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 202
                } // test if you have already create a copy file

                else if ( FileN == 203 ) {
                    input.open( "copy203.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy203.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 203
                } // test if you have already create a copy file

                else if ( FileN == 204 ) {
                    input.open( "copy204.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy204.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 204
                } // test if you have already create a copy file

                else if ( FileN == 205 ) {
                    input.open( "copy205.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy205.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 205
                } // test if you have already create a copy file
            } while ( ! function2Confirm ) ;

            cout << "Data Count: " << Count << endl ;
            Count = 0 ;
            FileN = 0 ;
            input.close() ;
            output.close() ;
        } // mission 2

        else if ( command == 3 ) {
            int firstFile = 0 ;
            int secondFile = 0 ;
            bool firstOpen = false ;

            while ( ! firstOpen ) {
                cout << "Please enter the first file ( 201 - 205 ) that you want to merge or [0] to quit:" << endl ;
                cin >> firstFile ;

                if ( firstFile == 0 ) {
                    continueOrNot = true ;
                    firstOpen = true ;
                } // quit

                else if ( firstFile != 201 && firstFile != 202 && firstFile != 203 && firstFile != 204 && firstFile != 205 )
                    cout << "*****  copy" << firstFile << ".txt does not exist!  *****" << endl ;

                else if ( firstFile == 201 ) {
                    if ( fopen( "copy201.txt", "r" ) == NULL ) cout << "*****  copy201.txt does not exist!  *****" << endl ;
                    else firstOpen = true ;
                } // 201

                else if ( firstFile == 202 ) {
                    if ( fopen( "copy202.txt", "r" ) == NULL ) cout << "*****  copy202.txt does not exist!  *****" << endl ;
                    else firstOpen = true ;
                } // 202

                else if ( firstFile == 203 ) {
                    if ( fopen( "copy203.txt", "r" ) == NULL ) cout << "*****  copy203.txt does not exist!  *****" << endl ;
                    else firstOpen = true ;
                } // 203

                else if ( firstFile == 204 ) {
                    if ( fopen( "copy204.txt", "r" ) == NULL ) cout << "*****  copy204.txt does not exist!  *****" << endl ;
                    else firstOpen = true ;
                } // 204

                else if ( firstFile == 205 ) {
                    if ( fopen( "copy205.txt", "r" ) == NULL ) cout << "*****  copy205.txt does not exist!  *****" << endl ;
                    else firstOpen = true ;
                } // 205
            } // if the first input is acceptable

            while ( firstOpen && ! continueOrNot ) {
                cout << "Please enter the second file ( 201 - 205 ) that you want to merge or [0] to quit:" << endl ;
                cin >> secondFile ;

                if ( secondFile == 0 ) continueOrNot = true ;

                else if ( secondFile != 201 && secondFile != 202 && secondFile != 203 && secondFile != 204 && secondFile != 205 && secondFile != 0 ) {
                    cout << "*****  copy" << secondFile << ".txt does not exist!  *****" << endl ;
                } // wrong filename

                else if ( secondFile == 201 ) {
                    if ( fopen( "copy201.txt", "r" ) == NULL ) cout << "*****  copy201.txt does not exist!  *****" << endl ;
                    // else
                } // 201

                else if ( secondFile == 202 ) {
                    if ( fopen( "copy202.txt", "r" ) == NULL ) cout << "*****  copy202.txt does not exist!  *****" << endl ;
                    // else
                } // 202

                else if ( secondFile == 203 ) {
                    if ( fopen( "copy203.txt", "r" ) == NULL ) cout << "*****  copy203.txt does not exist!  *****" << endl ;
                    // else
                } // 203

                else if ( secondFile == 204 ) {
                    if ( fopen( "copy204.txt", "r" ) == NULL ) cout << "*****  copy204.txt does not exist!  *****" << endl ;
                    // else
                } // 204

                else if ( secondFile == 205 ) {
                    if ( fopen( "copy205.txt", "r" ) == NULL ) cout << "*****  copy205.txt does not exist!  *****" << endl ;
                    // else FunctionNVarieblesArea.Merge( firstFile, secondFile ) ;
                } // 205
            } // second file
        } // mission 3

    } while( continueOrNot ) ;
} // main()
