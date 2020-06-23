#include <iostream>

using namespace std;
class rdp{

public:

bool parseString(string); 
int main(void);
rdp(); 
~rdp(); 

private:

bool A();
bool checkEqualsOperand();
bool E();
bool O();
bool P();
bool leftParenthesesCheck();
bool rightParenthesesCheck();
bool U();
bool I();
bool C();
bool L();
bool D();
string printParseString();
bool lookAheadIsInUOperators();
bool checkForSpecialCaseExponent();
bool lookAheadIsInOoperators();
bool lookAheadIsInDigits();
void incrementLookAheadPosition();
int getLookAheadPosition();
//int getLookAheadPosition(int);
bool getLookAheadPositions(int);
char getLookAheadCharacter();
bool isLookAheadPositionValid();
bool isLookAheadPositionValid(int);
bool lookAheadIsInAlphabet();
bool setLookAheadPosition(int);
int i;
string s;
char alphabet[26];
char digits[10];
char Uoperators[3];
char Ooperators[4];

};

rdp::rdp ():alphabet
{
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}

, digits

{
'0','1','2','3','4','5','6','7','8','9'}

,Uoperators
{
'+','-','!'}

,Ooperators
{
'+','-','*','/'}

,s("")
{

}
int i = 0;
int setLookAheadPosition = 0;
int lookAheadPosition = 0;
   
rdp::~rdp()
{
}



bool rdp:: parseString(string s){
	   
	     setLookAheadPosition(0);
	    	 return A();
	}
	//special override dont use unless in return regex

bool rdp:: A() {
		if(I())
			if(checkEqualsOperand()) 
				if(E()) {
					//incrementLookAheadPosition();
					if(!isLookAheadPositionValid())
						return true;
					else 
						return A();
				}
		
		
		
		return false;
		
		
		
	}
	
bool rdp:: E() {
		int temp = getLookAheadPosition();
		if(P()) 
			if(O())
				if(P())
					return true;
				else 
					setLookAheadPosition(temp);
			else 
				setLookAheadPosition(temp);
		if(P())
			return true;
		else
			setLookAheadPosition(temp);
		return false;
		
		//return(P() && O() && P()|| P());
	}
	
bool rdp:: O() {
		return lookAheadIsInOoperators();
	}
	
bool rdp:: P() {
		int temp = getLookAheadPosition();
		if(I()) 
			return true;
		if(L())
			return true;
		if(U()) {
			if(I())
				return true;
		
		else
			setLookAheadPosition(temp);
		}
		if(U()) {
			if(L())
				return true;
		}
		else
			setLookAheadPosition(temp);
		if(leftParenthesesCheck()) {
			if(E()) {
				if(rightParenthesesCheck())
					return true;
			}
			else {
				setLookAheadPosition(temp);
			}
		}
		else {
			setLookAheadPosition(temp);
		}
		return false;
					
		//return (I() || L() || U() && I()|| U() && L() || leftParenthesesCheck() && E() && rightParenthesesCheck()); 
	}
	
bool rdp:: U() {
		return lookAheadIsInUOperators();
	}
	
bool rdp:: I() {
	
		int temp = getLookAheadPosition();
		if(C())
			return true;
		if(C()) {
			if(I())
				return true;
		}
		else {
			setLookAheadPosition(temp);
		}
		
		return false;
		//return(C() ||  C() && I());
	}
	
bool rdp:: C() {
		return lookAheadIsInAlphabet();
	}
	
bool rdp:: L() {
		int temp = getLookAheadPosition();
		if(D())
			return true;
		if(D())
			if(L())
				return true;
		setLookAheadPosition(temp);
		return false;
		//return (D() || D() && L() );
	}
	
bool rdp:: D() {
		return (lookAheadIsInDigits());
	}
	
bool rdp:: checkEqualsOperand(){
		
        	if(isLookAheadPositionValid() && getLookAheadCharacter() == '='){ 
        	incrementLookAheadPosition();  
        	return true; 
        	}
        	else {
        	    return false;
        	}
	}
	//use push and pop eventually this is buggy
bool rdp:: leftParenthesesCheck(){
	    if(isLookAheadPositionValid() && getLookAheadCharacter() == '('){
	        incrementLookAheadPosition(); 
	        return true;
	    } 
	    else {
	        return false;
	    }
	}
	//use push and pop eventually this is buggy
bool rdp:: rightParenthesesCheck(){
	    
	    if ( isLookAheadPositionValid() && getLookAheadCharacter() == ')'){ 
	        incrementLookAheadPosition();
	        return true;
	    }
	    else{
	      return false;  
	    } 
	}
	
bool rdp:: lookAheadIsInAlphabet(){
	    
	    if(isLookAheadPositionValid()){
	    	for (char c: alphabet) {
	    		if(c == getLookAheadCharacter()) {
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
	  		 //iterate through Uoperator list return true if found

	    }
	    
	    return false;
	    
	}
	
bool rdp:: lookAheadIsInUOperators(){
	    
	    if(isLookAheadPositionValid()){
	    	for (char c: Uoperators) {
	    		if(c == getLookAheadCharacter()) {
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
            return false;
	    }	
	    return false;
	    
	}
	
bool rdp:: checkForSpecialCaseExponent() {
		if(s.at(getLookAheadPosition()) == '*' && s.at(getLookAheadPosition()+1) == '*') {
			incrementLookAheadPosition();
			return true;
		}
		return false;	
	}
	
bool rdp:: lookAheadIsInOoperators(){
	    
	    if(isLookAheadPositionValid()){
	    	for (char c: Ooperators) {
	    		if(c == getLookAheadCharacter()|| checkForSpecialCaseExponent()) { //check for**
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
	        
	    }
	    return false;
	}
	
bool rdp:: lookAheadIsInDigits(){
	    
	    if(isLookAheadPositionValid()){
	    	for (char c: digits) {
	    		if( c == getLookAheadCharacter()) {
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
	    }
	    return false;
	}
	
bool rdp:: isLookAheadPositionValid(int i) {
		 if (i<s.length()) {
			 lookAheadPosition =i;
	        return true;
	    }
	    else {
	       return false;
	    }
		
	}
	
bool rdp:: setLookAheadPosition(int i){
		if(getLookAheadPositions(i)) {
	    lookAheadPosition =i;
	    return false;
		}
		return true;
	}
	
bool rdp:: getLookAheadPositions(int i) {
		if(isLookAheadPositionValid(i)) {
			return true;
		}
		return false;
	}
	
void rdp:: incrementLookAheadPosition() {
		if(isLookAheadPositionValid()) {
			++lookAheadPosition;
			}
		
	}

int rdp:: getLookAheadPosition() {
		
		if(isLookAheadPositionValid()){
		       return lookAheadPosition; 
		    }
		       return -1; 
	        
		    }
	
char rdp:: getLookAheadCharacter(){
	       return s.at(getLookAheadPosition()); 
	    
	    }
	
bool rdp:: isLookAheadPositionValid(){
	    if (lookAheadPosition >= 0 && lookAheadPosition < s.length()){
	        return true;
	    }
	    else {
	       return false;
	    }
	}

	
string rdp:: printParseString(){
		if(isLookAheadPositionValid()) {
	    return s.substr(getLookAheadPosition(),s.length());
		}
		else {
			return "N/A";
		}
	}

int
main()
{
    string str = "a=1";
    string str2 = "a=1+2";
    string str3 = "a=(1)";
  rdp *algorithm = new rdp();
 // algorithm->parseString(str);
  
  if(algorithm->parseString(str)) {
          	cout << "The string \""+ str +"\" is in the language. \n";
          }
          else {
          	cout << "The string \""+ str +"\" is not in the language.\n";
          }
}
