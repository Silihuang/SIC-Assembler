#include <iomanip> 
#include <iostream> // cout, endl
#include <fstream> // open, is_open
#include <string.h> // string
#include <vector> // vector
#include <cstdlib> // atoi, system
#include <iomanip> // setw, setprecision
#include <ctime> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <functional>
#include <sstream>
#include <math.h>
#include <ctype.h>

using namespace std ;
ifstream inFile ;
fstream	 outFile ;

static vector <string> Table1 ; // 語法 
static vector <string> Table2 ; // 假指令 
static vector <string> Table3 ; // register
static vector <string> Table4 ; // 符號 
static vector <string> Table5 ; // label 
static vector <string> Table6 ; // 數字 
static vector <string> Table7 ; // String 
 
string UpperToLower( string line ) { // 大寫轉小寫 
	
	for( int i = 0 ; i < line.length() ; i++ ) {
		
		if ( line[i] >= 'A' && line[i] <= 'Z' ) {
			line[i] = line[i] + 32 ;
		} // if 
				
	} // for

	return line ;
	
} // UpperToLower

 
string LowerToUpper( string line ) { // 大寫轉小寫 
	
	for( int i = 0 ; i < line.length() ; i++ ) {
		
		if ( line[i] >= 'a' && line[i] <= 'z' ) {
			line[i] = line[i] - 32 ;
		} // if 
				
	} // for

	return line ;
	
} // UpperToLower
	

void SetTable() {
	
	string line = "" ;
	inFile.open( ( "Table1.table"), ios :: in ) ; 
	Table1.push_back(line) ; // 第0位空的 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // 去除後面的空白 
 	  	Table1.push_back( line ) ;
 	  	
	} // while
	inFile.close() ; 
	
	line = "" ;
	inFile.open( ( "Table2.table"), ios :: in ) ; 
	Table2.push_back(line) ; // 第0位空的 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // 去除後面的空白 
 	  	Table2.push_back( line ) ;
 	  	
	} // while
	inFile.close() ; 	

	line = "" ;
	inFile.open( ("Table3.table"), ios :: in ) ; 
	Table3.push_back(line) ; // 第0位空的 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // 去除後面的空白 
 	  	Table3.push_back( line ) ;
 	  	
	} // while
	inFile.close() ; 
	
	line = "" ;
	inFile.open( ("Table4.table"), ios :: in ) ; 
	Table4.push_back(line) ; // 第0位空的 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // 去除後面的空白 
 	  	Table4.push_back( line ) ;
 	  	
	} // while
	inFile.close() ; 
	
	for( int i = 0 ; i < 100 ; i++ ) { // 0 ~ 99 HASH FUNCTION = MOD 100 
		Table5.push_back("") ;
	} // for
	for( int i = 0 ; i < 100 ; i++ ) { // 0 ~ 99 HASH FUNCTION = MOD 100 
		Table6.push_back("") ;
	} // for
		for( int i = 0 ; i < 100 ; i++ ) { // 0 ~ 99 HASH FUNCTION = MOD 100 
		Table7.push_back("") ;
	} // for
					 
} // SetTable

int IsSyntax( string line ) {  // 是否為語法 

	line = UpperToLower(line) ; // opcode小寫 
	for ( int i = 1 ; i < Table1.size() ; i++ ) { 

		if ( line == Table1.at(i) ) return i ;
			
	} // for
	return 0 ; 
	
} // IsSyntax()  

int IsDirective( string line ) {  // 是否為假指令 

	line = LowerToUpper( line ) ; // 小寫變大寫 
	for ( int i = 1 ; i < Table2.size() ; i++ ) { 
		if ( line == Table2.at(i) ) return i ;
			
	} // for
	
	return 0 ; 
	
} // IsDirective() 

int IsExtraWord( string line ) {  // 是否為register 
	
	for ( int i = 1 ; i < Table3.size() ; i++ ) { 
		
		if ( line == Table3.at(i) ) return i ;
			
	} // for
	
	return 0 ; 
	
} // IsExtraWord()  


int IsSymbol( char ch ) {  // 是否為符號 

	for ( int i = 1 ; i < Table4.size() ; i++ ) { // 第0位是空的 

		if ( ch == Table4.at(i)[0] ) return i ;
			
	} // for
	
	return 0 ; // 位置0為空的，回傳代表false 
	
} // IsSymbol()  

int IsLabel( string line ) {  // 是否為LABEL

	for ( int i = 0 ; i < Table5.size() ; i++ ) { 
		
		if ( line == Table5.at(i) ) return i ;
			
	} // for

	int local = 0 ; // 要放進去的位置 
	for ( int i = 0 ; i < line.length() ; i++ ) {
		local = local + line[i] ; // ASCII總和 
	} // for
	if ( local > 99 ) {
		local = local % 100 ;
	} // if 
	if ( Table5.at(local) != "" ) { // 代表已經有資料了，index+1 
		local++ ;
		if ( local > 99 ) local = local % 100 ;
	} // if 
	Table5.at(local) = line ; // 不存在，新增紀錄，hash function用 ASCII CODE	
	return local ; // 非1~4table 需要自行增加 
	
} // IsLabel()  

int IsDigits( string line, bool Hex ) {  // 是否為數字 

	if( Hex == false ) { // 當不是16進位數字時要判別 
	
		for ( int i = 0 ; i < line.length() ; i++ ) { 

			if ( line[i] > '9' || line[i] < '0' && line[i] != '.' ) {
				return 0 ; // 非數字回傳 0			
			} // if 
 
		} // for
		
	} // if 

	for ( int i = 0 ; i < Table6.size() ; i++ ) { 
		
		if ( line == Table6.at(i) ) {
			return i ; // 已存在，回傳紀錄位置			
		} // if 
			 
	} // for
	
	int local = 0 ; // 要放進去的位置 
	if ( Hex ) {

		for( int i = 0 ; i < line.length() ; i++ ) {  // 16進位變成10進位  ，carry為進位 
			
			if ( line[i] <= 'F' && line[i] >= 'A' ) { 
			
				int value = line[i] - 'A' + 10 ; // 16進位變成10進位
				int ten = value/10 ; // 十位數
				int single = value%10 ; // 個位數 
				local = ten + '0' + single + '0' ;
							
			} // if
			else {
				local = local + line[i] ; // ASCII總和			
			} // else	
			
		} // for	
			
	} // if 
	else {
		
		for ( int i = 0 ; i < line.length() ; i++ ) {
		
			local = local + line[i] ; // ASCII總和 			

		} // for	
			
	} // else

	if ( local > 99 ) {   // Hash Mod 100
		local = local % 100 ;
	} // if 
	if ( Table6.at(local) != "" ) { // 代表已經有資料了，index+1 
		local++ ;
		if ( local > 99 ) local = local % 100 ;
	} // if 
	Table6.at(local) = line ; // 不存在，新增紀錄，hash function用 ASCII CODE
	return local ; // 非1~4table 需要自行增加 
	
} // IsDigits()   

int IsString( string line ) {  // 是否為String
	
	for ( int i = 0 ; i < Table7.size() ; i++ ) { 
		
		if ( line == Table7.at(i) ) return i ;
			
	} // for

	int local = 0 ; // 要放進去的位置  
	for ( int i = 0 ; i < line.length() ; i++ ) {
		local = local + line[i] ; // ASCII總和 
	} // for
	if ( local > 99 ) {
		local = local % 100 ;
	} // if 
	if ( Table7.at(local) != "" ) { // 代表已經有資料了，index+1 
		local++ ;
		if ( local > 99 ) local = local % 100 ;
	} // if 
	Table7.at(local) = line ; // 不存在，新增紀錄，hash function用 ASCII CODE
	return local ; // 非1~4table 需要自行增加 
	
} // IsString()  

void ReadFile( string input ) {  // 讀檔 

   	string data = "" ; // 讀入一整行   	 
	outFile.open( (input+"_Output.txt").c_str(), ios :: out ) ; // 寫檔 	 
	  	
  	while( getline( inFile, data ) ) { // 一行一行讀
  	
  		string line = "" ; // data裡的部分字串 	
		data = data + "\n" ; // 加上換行以便寫檔+判斷	
  		outFile << data ; // 寫進一行 		
  	    for( int i = 0 ; i < data.length() ; i++ ) {  
  	 
  	  		if ( IsSymbol( data[i] ) != 0 ) { // 若是,前面可能有Symbol 

  	  			int j = IsSymbol( data[i] ) ;
  	  			//if ( data[i] != ',' )  outFile << "(4," << j << ")" ;  // 符號 
  				if ( data[i] == '\''  ) {  // ' 後面為String，前面會有個C 	
				  	outFile << "(4," << j << ")" ;  // 符號 				  			
  					string word, front = "" ;  //  word存string 或 16進位的數字 , front 存是X or C  
  					if ( data[i-1] == 'C' ) front = "C" ;
					else if ( data[i-1] == 'X') front = "X" ;
					
  					i++ ; // 加完後i的位置為String的第一位 
  					while( data[i] != '\''  ) {
					  word = word + data[i] ;  
					  i++ ;
					} // while   
					i++ ; // i 現在位置為' 需要再+1以免存到line  
					
					if ( front == "X" ) {  // 16進位 
						int k = IsDigits( word, true ) ;   // front有可能為 X'' or C'' 
						outFile << "(6," << k << ")" ;  						
					} // if 
					else if ( front == "C") { // 字串 
						int k = IsString( word ) ;   // front有可能為 X'' or C'' 
						outFile << "(7," << k << ")" ; 					
					} // else if  
							
				} // if 
				else if ( data[i] == '.') {  // SIC的'.'為註解 	
		
  					while ( i <= data.length() ) { // 將註解給跑完，				  
					  i++ ;
					} // while   
				} // else if 	
				else if ( data[i] == ',' ) {   // EX: STCH BUFFER,X
				
					if ( IsExtraWord(line) != 0 ) {						
					int j = IsExtraWord(line) ;
					outFile << "(3," << j << ")" ; 					
					} // if 				
					else if ( IsLabel(line) != 0 ) {
						int j = IsLabel(line) ;
						outFile << "(5," << j << ")" ; 										
					}	 // else if 
  					outFile << "(4," << j << ")" ;   					
				} // else if 	
				else if ( line != "" ) {   // line 有東西 
		  			if ( IsDigits(line, false ) != 0 ) {         // 數字 
  			  			int j = IsDigits(line, false ) ; 
  			  			outFile << "(6," << j << ")" ; 		  	
						} // if 
					else if ( IsSyntax(line) != 0 ) {       // 語法 
						int j = IsSyntax(line) ; 
						outFile << "(1," << j << ")" ;  					
					} // else if 
					else if ( IsDirective(line) != 0 ) {                            //假指令，Start、End 
						int j = IsDirective(line) ;
						outFile << "(2," << j << ")" ;  
					} // else if 
					else if ( IsExtraWord(line) != 0 ) {							//額外文字 
						int j = IsExtraWord(line) ;
						outFile << "(3," << j << ")" ; 					
					} // else if 				
					else if ( IsLabel(line) != 0 ) {
						int j = IsLabel(line) ;
						outFile << "(5," << j << ")" ; 										
					} // else if 						

				} // else if 
				if ( data[i] != ',' )  outFile << "(4," << j << ")" ;  // 符號 
				line = "" ; // 切，重新設定							
			} //  if                                                    有可能 
  			else if ( data[i] == '\t' || data[i] == '\n' || data[i] == ' ' && data[i] != '.' && line != "" && line != "C" ) { // WhiteSpace，判斷line裡的內容，String、數字、Label、額外文字、語法、標籤 
																		// X為SIC代表16進位，C為SIC代表String 									
  			  	if ( IsDigits(line, false ) != 0 ) {         // 數字 
  			  		int j = IsDigits(line, false ) ; 
  			  		outFile << "(6," << j << ")" ; 		  	
				} // if 
				else if ( IsSyntax(line) != 0 ) {       // 語法 
					int j = IsSyntax(line) ; 
					outFile << "(1," << j << ")" ;  					
				} // else if 
				else if ( IsDirective(line) != 0 ) {                            //假指令，Start、End 
					int j = IsDirective(line) ;
					outFile << "(2," << j << ")" ;  
				} // else if 
				else if ( IsExtraWord(line) != 0 ) {							//額外文字 
					int j = IsExtraWord(line) ;
					outFile << "(3," << j << ")" ; 					
				} // else if 				
				else if ( IsLabel(line) != 0 ) {
					int j = IsLabel(line) ;
					outFile << "(5," << j << ")" ; 										
				} // else if 	
				line = "" ; // 切，重新設定							
			} // else if	
			else if ( data[i] != '\t' && data[i] != '\n' && data[i] != ' ' ) { 	// 碰到這些不紀錄，應判斷
   
				line = line + data[i] ;
				
			} // else if 	
		} // for
		outFile << "\n" ; 	
  	} // while 
		
} // ReadFile() 

int main(int argc, char** argv) {
	
    string InputNum = "" ;
	SetTable() ; // 設定 Table1 ~ Table7 ， 5 ~ 7 需要先新增一次 第一筆資料才會在1 而不是0 
	do 
	{		
		cout << endl << "Input a FileNum : " ;		
		cin >> InputNum ; 
		inFile.open( ( InputNum + ".txt" ).c_str(), ios :: in ) ; // 開啟Input檔
		
	} while (  inFile.is_open() == 0 );
		  
	ReadFile( InputNum ) ;  // 讀檔 	
	inFile.close() ;
	outFile.close() ;
	return 0;
	
} // main 
