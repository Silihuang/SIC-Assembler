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

static vector <string> Table1 ; // �y�k 
static vector <string> Table2 ; // �����O 
static vector <string> Table3 ; // register
static vector <string> Table4 ; // �Ÿ� 
static vector <string> Table5 ; // label 
static vector <string> Table6 ; // �Ʀr 
static vector <string> Table7 ; // String 
 
string UpperToLower( string line ) { // �j�g��p�g 
	
	for( int i = 0 ; i < line.length() ; i++ ) {
		
		if ( line[i] >= 'A' && line[i] <= 'Z' ) {
			line[i] = line[i] + 32 ;
		} // if 
				
	} // for

	return line ;
	
} // UpperToLower

 
string LowerToUpper( string line ) { // �j�g��p�g 
	
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
	Table1.push_back(line) ; // ��0��Ū� 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // �h���᭱���ť� 
 	  	Table1.push_back( line ) ;
 	  	
	} // while
	inFile.close() ; 
	
	line = "" ;
	inFile.open( ( "Table2.table"), ios :: in ) ; 
	Table2.push_back(line) ; // ��0��Ū� 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // �h���᭱���ť� 
 	  	Table2.push_back( line ) ;
 	  	
	} // while
	inFile.close() ; 	

	line = "" ;
	inFile.open( ("Table3.table"), ios :: in ) ; 
	Table3.push_back(line) ; // ��0��Ū� 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // �h���᭱���ť� 
 	  	Table3.push_back( line ) ;
 	  	
	} // while
	inFile.close() ; 
	
	line = "" ;
	inFile.open( ("Table4.table"), ios :: in ) ; 
	Table4.push_back(line) ; // ��0��Ū� 
	while( getline( inFile, line ) ) {
		
		line.erase( line.find_last_not_of(" ") + 1) ; // �h���᭱���ť� 
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

int IsSyntax( string line ) {  // �O�_���y�k 

	line = UpperToLower(line) ; // opcode�p�g 
	for ( int i = 1 ; i < Table1.size() ; i++ ) { 

		if ( line == Table1.at(i) ) return i ;
			
	} // for
	return 0 ; 
	
} // IsSyntax()  

int IsDirective( string line ) {  // �O�_�������O 

	line = LowerToUpper( line ) ; // �p�g�ܤj�g 
	for ( int i = 1 ; i < Table2.size() ; i++ ) { 
		if ( line == Table2.at(i) ) return i ;
			
	} // for
	
	return 0 ; 
	
} // IsDirective() 

int IsExtraWord( string line ) {  // �O�_��register 
	
	for ( int i = 1 ; i < Table3.size() ; i++ ) { 
		
		if ( line == Table3.at(i) ) return i ;
			
	} // for
	
	return 0 ; 
	
} // IsExtraWord()  


int IsSymbol( char ch ) {  // �O�_���Ÿ� 

	for ( int i = 1 ; i < Table4.size() ; i++ ) { // ��0��O�Ū� 

		if ( ch == Table4.at(i)[0] ) return i ;
			
	} // for
	
	return 0 ; // ��m0���Ū��A�^�ǥN��false 
	
} // IsSymbol()  

int IsLabel( string line ) {  // �O�_��LABEL

	for ( int i = 0 ; i < Table5.size() ; i++ ) { 
		
		if ( line == Table5.at(i) ) return i ;
			
	} // for

	int local = 0 ; // �n��i�h����m 
	for ( int i = 0 ; i < line.length() ; i++ ) {
		local = local + line[i] ; // ASCII�`�M 
	} // for
	if ( local > 99 ) {
		local = local % 100 ;
	} // if 
	if ( Table5.at(local) != "" ) { // �N��w�g����ƤF�Aindex+1 
		local++ ;
		if ( local > 99 ) local = local % 100 ;
	} // if 
	Table5.at(local) = line ; // ���s�b�A�s�W�����Ahash function�� ASCII CODE	
	return local ; // �D1~4table �ݭn�ۦ�W�[ 
	
} // IsLabel()  

int IsDigits( string line, bool Hex ) {  // �O�_���Ʀr 

	if( Hex == false ) { // ���O16�i��Ʀr�ɭn�P�O 
	
		for ( int i = 0 ; i < line.length() ; i++ ) { 

			if ( line[i] > '9' || line[i] < '0' && line[i] != '.' ) {
				return 0 ; // �D�Ʀr�^�� 0			
			} // if 
 
		} // for
		
	} // if 

	for ( int i = 0 ; i < Table6.size() ; i++ ) { 
		
		if ( line == Table6.at(i) ) {
			return i ; // �w�s�b�A�^�Ǭ�����m			
		} // if 
			 
	} // for
	
	int local = 0 ; // �n��i�h����m 
	if ( Hex ) {

		for( int i = 0 ; i < line.length() ; i++ ) {  // 16�i���ܦ�10�i��  �Acarry���i�� 
			
			if ( line[i] <= 'F' && line[i] >= 'A' ) { 
			
				int value = line[i] - 'A' + 10 ; // 16�i���ܦ�10�i��
				int ten = value/10 ; // �Q���
				int single = value%10 ; // �Ӧ�� 
				local = ten + '0' + single + '0' ;
							
			} // if
			else {
				local = local + line[i] ; // ASCII�`�M			
			} // else	
			
		} // for	
			
	} // if 
	else {
		
		for ( int i = 0 ; i < line.length() ; i++ ) {
		
			local = local + line[i] ; // ASCII�`�M 			

		} // for	
			
	} // else

	if ( local > 99 ) {   // Hash Mod 100
		local = local % 100 ;
	} // if 
	if ( Table6.at(local) != "" ) { // �N��w�g����ƤF�Aindex+1 
		local++ ;
		if ( local > 99 ) local = local % 100 ;
	} // if 
	Table6.at(local) = line ; // ���s�b�A�s�W�����Ahash function�� ASCII CODE
	return local ; // �D1~4table �ݭn�ۦ�W�[ 
	
} // IsDigits()   

int IsString( string line ) {  // �O�_��String
	
	for ( int i = 0 ; i < Table7.size() ; i++ ) { 
		
		if ( line == Table7.at(i) ) return i ;
			
	} // for

	int local = 0 ; // �n��i�h����m  
	for ( int i = 0 ; i < line.length() ; i++ ) {
		local = local + line[i] ; // ASCII�`�M 
	} // for
	if ( local > 99 ) {
		local = local % 100 ;
	} // if 
	if ( Table7.at(local) != "" ) { // �N��w�g����ƤF�Aindex+1 
		local++ ;
		if ( local > 99 ) local = local % 100 ;
	} // if 
	Table7.at(local) = line ; // ���s�b�A�s�W�����Ahash function�� ASCII CODE
	return local ; // �D1~4table �ݭn�ۦ�W�[ 
	
} // IsString()  

void ReadFile( string input ) {  // Ū�� 

   	string data = "" ; // Ū�J�@���   	 
	outFile.open( (input+"_Output.txt").c_str(), ios :: out ) ; // �g�� 	 
	  	
  	while( getline( inFile, data ) ) { // �@��@��Ū
  	
  		string line = "" ; // data�̪������r�� 	
		data = data + "\n" ; // �[�W����H�K�g��+�P�_	
  		outFile << data ; // �g�i�@�� 		
  	    for( int i = 0 ; i < data.length() ; i++ ) {  
  	 
  	  		if ( IsSymbol( data[i] ) != 0 ) { // �Y�O,�e���i�঳Symbol 

  	  			int j = IsSymbol( data[i] ) ;
  	  			//if ( data[i] != ',' )  outFile << "(4," << j << ")" ;  // �Ÿ� 
  				if ( data[i] == '\''  ) {  // ' �᭱��String�A�e���|����C 	
				  	outFile << "(4," << j << ")" ;  // �Ÿ� 				  			
  					string word, front = "" ;  //  word�sstring �� 16�i�쪺�Ʀr , front �s�OX or C  
  					if ( data[i-1] == 'C' ) front = "C" ;
					else if ( data[i-1] == 'X') front = "X" ;
					
  					i++ ; // �[����i����m��String���Ĥ@�� 
  					while( data[i] != '\''  ) {
					  word = word + data[i] ;  
					  i++ ;
					} // while   
					i++ ; // i �{�b��m��' �ݭn�A+1�H�K�s��line  
					
					if ( front == "X" ) {  // 16�i�� 
						int k = IsDigits( word, true ) ;   // front���i�ର X'' or C'' 
						outFile << "(6," << k << ")" ;  						
					} // if 
					else if ( front == "C") { // �r�� 
						int k = IsString( word ) ;   // front���i�ର X'' or C'' 
						outFile << "(7," << k << ")" ; 					
					} // else if  
							
				} // if 
				else if ( data[i] == '.') {  // SIC��'.'������ 	
		
  					while ( i <= data.length() ) { // �N���ѵ��]���A				  
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
				else if ( line != "" ) {   // line ���F�� 
		  			if ( IsDigits(line, false ) != 0 ) {         // �Ʀr 
  			  			int j = IsDigits(line, false ) ; 
  			  			outFile << "(6," << j << ")" ; 		  	
						} // if 
					else if ( IsSyntax(line) != 0 ) {       // �y�k 
						int j = IsSyntax(line) ; 
						outFile << "(1," << j << ")" ;  					
					} // else if 
					else if ( IsDirective(line) != 0 ) {                            //�����O�AStart�BEnd 
						int j = IsDirective(line) ;
						outFile << "(2," << j << ")" ;  
					} // else if 
					else if ( IsExtraWord(line) != 0 ) {							//�B�~��r 
						int j = IsExtraWord(line) ;
						outFile << "(3," << j << ")" ; 					
					} // else if 				
					else if ( IsLabel(line) != 0 ) {
						int j = IsLabel(line) ;
						outFile << "(5," << j << ")" ; 										
					} // else if 						

				} // else if 
				if ( data[i] != ',' )  outFile << "(4," << j << ")" ;  // �Ÿ� 
				line = "" ; // ���A���s�]�w							
			} //  if                                                    ���i�� 
  			else if ( data[i] == '\t' || data[i] == '\n' || data[i] == ' ' && data[i] != '.' && line != "" && line != "C" ) { // WhiteSpace�A�P�_line�̪����e�AString�B�Ʀr�BLabel�B�B�~��r�B�y�k�B���� 
																		// X��SIC�N��16�i��AC��SIC�N��String 									
  			  	if ( IsDigits(line, false ) != 0 ) {         // �Ʀr 
  			  		int j = IsDigits(line, false ) ; 
  			  		outFile << "(6," << j << ")" ; 		  	
				} // if 
				else if ( IsSyntax(line) != 0 ) {       // �y�k 
					int j = IsSyntax(line) ; 
					outFile << "(1," << j << ")" ;  					
				} // else if 
				else if ( IsDirective(line) != 0 ) {                            //�����O�AStart�BEnd 
					int j = IsDirective(line) ;
					outFile << "(2," << j << ")" ;  
				} // else if 
				else if ( IsExtraWord(line) != 0 ) {							//�B�~��r 
					int j = IsExtraWord(line) ;
					outFile << "(3," << j << ")" ; 					
				} // else if 				
				else if ( IsLabel(line) != 0 ) {
					int j = IsLabel(line) ;
					outFile << "(5," << j << ")" ; 										
				} // else if 	
				line = "" ; // ���A���s�]�w							
			} // else if	
			else if ( data[i] != '\t' && data[i] != '\n' && data[i] != ' ' ) { 	// �I��o�Ǥ������A���P�_
   
				line = line + data[i] ;
				
			} // else if 	
		} // for
		outFile << "\n" ; 	
  	} // while 
		
} // ReadFile() 

int main(int argc, char** argv) {
	
    string InputNum = "" ;
	SetTable() ; // �]�w Table1 ~ Table7 �A 5 ~ 7 �ݭn���s�W�@�� �Ĥ@����Ƥ~�|�b1 �Ӥ��O0 
	do 
	{		
		cout << endl << "Input a FileNum : " ;		
		cin >> InputNum ; 
		inFile.open( ( InputNum + ".txt" ).c_str(), ios :: in ) ; // �}��Input��
		
	} while (  inFile.is_open() == 0 );
		  
	ReadFile( InputNum ) ;  // Ū�� 	
	inFile.close() ;
	outFile.close() ;
	return 0;
	
} // main 
