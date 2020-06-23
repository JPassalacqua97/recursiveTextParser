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
bool leftPerentecyCheck();
bool rightPerentecyCheck();
bool U();
bool I();
bool C();
bool L();
bool D();
bool lookAheadIsInUOperators();
bool checkForSpecialCaseExponent();
bool lookAheadIsInOoperators();
bool lookAheadIsInDigits();
bool incrementLookAheadPosition();
int getLookAheadPosition();
char getLookAheadCharacter();
bool isLookAheadPositionValid();
bool lookAheadIsInAlphabet();
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
   "";}

int lookAheadPosition = 0;


bool
rdp:: parseString(string s)
{
    int count = 0;
	cout << s + " is the string we are parsing";
	//setLookAheadPosition(0);
	
	 if(A()){
	   cout << s+ " is in the language";
	   return true;
	  }
	   else
	   { cout << s + " is NOT in the language";
	    return false;
	   }
}

bool
rdp:: A ()
{
   return (I() && checkEqualsOperand() && E()); 
}

bool
rdp:: E()
{
    return(P() && O() && P() || P());
}

bool
rdp:: O()
{
    return lookAheadIsInOoperators();
}

bool
rdp:: P()
{
   return I() || L() || U() && I() || U() && L() || (leftPerentecyCheck() && E() && rightPerentecyCheck()); 
}

bool
rdp:: U()
{
    return lookAheadIsInUOperators();
}


bool
rdp:: I()
{
    return(C() ||  C() && I());
}

bool
rdp:: C()
{
    return lookAheadIsInAlphabet();
}

bool
rdp:: L()
{
    return (D() || D() && L());
}

bool
rdp:: D()
{
    return (lookAheadIsInDigits());
}

bool
rdp:: checkEqualsOperand()
{
    return (getLookAheadCharacter() == '=' && incrementLookAheadPosition());
}

bool
rdp:: leftPerentecyCheck()
{
    return (getLookAheadCharacter() == '(' && incrementLookAheadPosition());
}

bool
rdp:: rightPerentecyCheck()
{
    return (getLookAheadCharacter() == ')'&& incrementLookAheadPosition());
}

bool
rdp:: lookAheadIsInUOperators ()
{
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

bool
rdp:: lookAheadIsInOoperators ()
{
     if(isLookAheadPositionValid()){
	    	for (char c: Ooperators) {
	    		if(c == getLookAheadCharacter() || checkForSpecialCaseExponent()) {
	    		
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
	    	return false;
	    }
	    return false;
}

bool
rdp:: checkForSpecialCaseExponent()
{
   if (s.at(getLookAheadPosition()) == '*' && s.at(getLookAheadPosition()+1) == '*') {
			incrementLookAheadPosition();
			return true;
		}
		else {
		}
		return false; 
}

bool
rdp:: lookAheadIsInAlphabet()
{
    if(isLookAheadPositionValid()){
	    	for (char c: alphabet) {
	    		if(c == getLookAheadCharacter()) {
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
	  		 

	    }
	    
	    return false;
}

bool
rdp:: lookAheadIsInDigits ()
{
  if(isLookAheadPositionValid()){
	    	for (char c: digits) {
	    		if( c == getLookAheadCharacter()) {
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
	    	return false;

	    }
	    return false;  
}

bool
rdp:: incrementLookAheadPosition()
{
    if(getLookAheadPosition() +1 < s.length()) {
		++lookAheadPosition;
		}
		else{
		}
			return false;
}

int
rdp:: getLookAheadPosition ()
{
    if(isLookAheadPositionValid()){
		 return lookAheadPosition; 
		    }
		  return -1; 
}

char
rdp:: getLookAheadCharacter ()
{
  return s.at(getLookAheadPosition());  
}

bool
rdp:: isLookAheadPositionValid ()
{
    if (lookAheadPosition < s.length()){
	        return true;
	    }
	    else {
	       return false;
	    }
}


int
main()
{
    string str = "a=1";
  rdp *algorithm = new rdp();
  algorithm->parseString(str);
  return 0;
}