import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;


public class rdp{
	
	private char[] alphabet;
	private char[] digits;
	private char[] Uoperators;
	private char[] Ooperators; //check for**
	
	/*
	Consider the following BNF grammar:
	A -> I = E
        E -> P O P | P
        O -> + | - | * | / | **   //Ooperators
        P -> I | L | UI | UL | (E)
        U -> + | - | !    //Uoperators
        I -> C | CI
        C -> a | b | ... | y | z  //alphabet
        L -> D | DL
        D -> 0 | 1 | ... | 8 | 9  //digits
	
	Known Issues :
	"a=(b+c)(d+e))"
        "a=b+cd^e"
        "a=(b+c)(d+e))"
	
	*/
	 
	 private int lookAheadPosition;
	 private int count;
	 private String s;
	 
	 rdp(){
		 this.alphabet = new char [] {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 
		 this.digits = new char[] {'0','1','2','3','4','5','6','7','8','9'};
		 this.Uoperators = new char[] {'+','-','!'};
		 this.Ooperators = new char[] {'+','-','*','/'};
		 this.s = "";
		 this.lookAheadPosition = 0;
		 this.count = 0;
	 }
	 
	public boolean parseString(String s){
	    
	    
	     this.s = s;
	     count =0;
	     setLookAheadPosition(0);
	    	 return A() || A();
	}
	//special override dont use unless in return regex

	private boolean A() {
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
	
	private boolean E() {
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
	
	private boolean O() {
		return lookAheadIsInOoperators();
	}
	
	private boolean P() {
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
	
	private boolean U() {
		return lookAheadIsInUOperators();
	}
	
	private boolean I() {
	
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
	
	private boolean C() {
		return lookAheadIsInAlphabet();
	}
	
	private boolean L() {
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
	
	private boolean D() {
		return (lookAheadIsInDigits());
	}
	
	private boolean checkEqualsOperand(){
		
        	if(isLookAheadPositionValid() && getLookAheadCharacter() == '='){ 
        	incrementLookAheadPosition();  
        	return true; 
        	}
        	else {
        	    return false;
        	}
	}
	//use push and pop eventually this is buggy
	private boolean leftParenthesesCheck(){
	    if(isLookAheadPositionValid() && getLookAheadCharacter() == '('){
	        incrementLookAheadPosition(); 
	        return true;
	    } 
	    else {
	        return false;
	    }
	}
	//use push and pop eventually this is buggy
	private boolean rightParenthesesCheck(){
	    
	    if ( isLookAheadPositionValid() && getLookAheadCharacter() == ')'){ 
	        incrementLookAheadPosition();
	        return true;
	    }
	    else{
	      return false;  
	    } 
	}
	
	private boolean lookAheadIsInAlphabet(){
	    
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
	
	private boolean lookAheadIsInUOperators(){
	    
	    if(isLookAheadPositionValid()){
	    	for (char c: Uoperators) {
	    		if(c == getLookAheadCharacter()) {
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}//iterate through Uoperator list return true if found
            return false;
	    }	
	    return false;
	    
	}
	
	private boolean checkForSpecialCaseExponent() {
		if(s.charAt(getLookAheadPosition()) == '*' && s.charAt(getLookAheadPosition()+1) == '*') {
			incrementLookAheadPosition();
			return true;
		}
		return false;	
	}
	
	private boolean lookAheadIsInOoperators(){
	    
	    if(isLookAheadPositionValid()){
	    	for (char c: Ooperators) {
	    		if(c == getLookAheadCharacter()|| checkForSpecialCaseExponent()) { //check for**
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}
	        //iterate through Strings list return true if found
	    }
	    return false;
	}
	
	private boolean lookAheadIsInDigits(){
	    
	    if(isLookAheadPositionValid()){
	    	for (char c: digits) {
	    		if( c == getLookAheadCharacter()) {
	    		incrementLookAheadPosition();
	    		return true;
	    		}
	    	}//iterate through Digits list return true if found
	    }
	    return false;
	}
	
	private boolean isLookAheadPositionValid(int i) {
		// TODO Auto-generated method stub
		 if (i<s.length()) {
			 lookAheadPosition =i;
	        return true;
	    }
	    else {
	       return false;
	    }
		
	}
	
	private boolean setLookAheadPosition(int i){
		if(getLookAheadPosition(i)) {
	    lookAheadPosition =i;
	    return false;
		}
		return true;
	}
	
	private boolean getLookAheadPosition(int i) {
		// TODO Auto-generated method stub
		if(isLookAheadPositionValid(i)) {
			return true;
		}
		return false;
	}
	
	private void incrementLookAheadPosition() {
		if(isLookAheadPositionValid()) {
			++lookAheadPosition;
			}
		
	}

	private int getLookAheadPosition() {
		
		if(isLookAheadPositionValid()){
			//infoM("getLookAheadPosition() = "+ lookAheadPosition +" returned TRUE : ");
		       return lookAheadPosition; 
		    }
			System.out.println("getLookAheadPosition() is invalid & this is the CURRENT lookAheadPositonCharacter"+ lookAheadPosition+ "        " + s + " is the string we are parsing");
		       return -1; 
	        
		    }
	
	private char getLookAheadCharacter(){
	    	//infoM("getLookAheadCharacter() returned : " + getLookAheadPosition()); 
		
	       return s.charAt(getLookAheadPosition()); 
	    
	    }
	
	private boolean isLookAheadPositionValid(){
	    if (lookAheadPosition >= 0 && lookAheadPosition < s.length()){
             //infoM("LookAheadPositionValid() returned TRUE :");
	        return true;
	    }
	    else {
	       return false;
	    }
	}

	
	private String printParseString(){
		if(isLookAheadPositionValid()) {
	    return s.substring(getLookAheadPosition(),s.length());
		}
		else {
			return "N/A";
		}
	}
  
    public static void main(String[] args) throws IOException {

    	String line = "";
		rdp algorithm = new rdp();      
	      
		 File in=new File("input.txt");
		 System.out.println(in.getAbsolutePath());
		 String input = in.getAbsolutePath();
		 File out = new File("output.txt");
		 System.out.println(out.getAbsolutePath());
		 String output = out.getAbsolutePath();
		 FileReader fileReader = new FileReader(input);
			FileWriter fileWriter = new FileWriter(output);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

      while((line = bufferedReader.readLine()) != null) {
          if(algorithm.parseString(line)) {
          	bufferedWriter.write("The string \""+ line +"\" is in the language. \n");
          }
          else {
          	bufferedWriter.write("The string \""+ line +"\" is not in the language.\n");
          }
      }
      bufferedReader.close();
      bufferedWriter.close();
      fileReader.close();
      fileWriter.close();
      }
}