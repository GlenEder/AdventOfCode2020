#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * The goal of day 2 is to find all valid passwords 
 * that follow the rule provided in each line.
 * Given input "1-3 a: abcde", there must contain at 
 * least 1 instance 'a' and at most 3 instances of 'a'
 * in the following passcode. Which in the provided input 
 * will pass.
 * 
 * Part 2 has us instead checking to see if the chars at 
 * the positions indicated by the values (originally the
 * range 1-3 in prev example) are not equal, but one of 
 * the two chars is equal to the required char. 
 * 
 * To improve upon this solution, I would move the bulk of 
 * the input handling code (ie. substring calls and what not) 
 * to a different method as both parts used the same code there.
 * Ideally it could return a struct that contained the password, 
 * first number, second number, and the required char.  
 */


void part1() {

	struct input * curr = inputList;		//get pointer to beginning of input list
	unsigned int numValid = 0;			//counter for valid passwords found
	
	//loop through input list
	while(curr) {
	
		int dashIndex = indexOfChar(curr->value, '-', 0);			//get index of spliting dash '-' in input
		char * minReqStr = substring(curr->value, 0, dashIndex);		//get substring of first param
		int minReq = atoi(minReqStr);						//get int value of substring	 
		free(minReqStr);							//free memory for substring
		
		int firstSpaceIndex = indexOfChar(curr->value, ' ', dashIndex);		//get index of first space in input
		int maxReqLength = firstSpaceIndex - dashIndex + 1;			//calc substring length 
		char * maxReqStr = substring(curr->value, dashIndex + 1, maxReqLength); //get second param value
		int maxReq = atoi(maxReqStr);						//get int value of second param 
		free(maxReqStr);							//free substring memory 
				
		int reqCharIndex = firstSpaceIndex + 1;					//index of char password requires 
		char reqChar = *(curr->value + reqCharIndex);				//get char password requires 
		
		int colonIndex = indexOfChar(curr->value, ':', reqCharIndex);		//finde index of colon in input
		int passLength = strlength(curr->value) - colonIndex;			//calc length of password 		 	
		char * password = substring(curr->value, colonIndex + 2, passLength);	//get password from input to check   
	
			
		//Verify password
		int reqCharsFound = 0;
		for(int i = 0; i < passLength; i++) {
			if(*(password + i) == reqChar) reqCharsFound++;			//check if char matches reqirement
		}
		
		//check chars found against requirements
		if(reqCharsFound >= minReq && reqCharsFound <= maxReq) numValid++;	//increase number of valid passwords counter

		free(password);								//free memory password was using  
		curr = curr->next;							//go to next input in list
	}

	//print results
	printf("Number Valid Passwords: %u\n", numValid);	
	
}

void part2() {

	struct input * curr = inputList;		//get pointer to beginning of input list
	unsigned int numValid = 0;			//counter for valid passwords found
	
	//loop through input list
	while(curr) {
	
		int dashIndex = indexOfChar(curr->value, '-', 0);			//get index of spliting dash '-' in input
		char * minReqStr = substring(curr->value, 0, dashIndex);		//get substring of first param
		int minReq = atoi(minReqStr);						//get int value of substring	 
		free(minReqStr);							//free memory for substring
		
		int firstSpaceIndex = indexOfChar(curr->value, ' ', dashIndex);		//get index of first space in input
		int maxReqLength = firstSpaceIndex - dashIndex + 1;			//calc substring length 
		char * maxReqStr = substring(curr->value, dashIndex + 1, maxReqLength); //get second param value
		int maxReq = atoi(maxReqStr);						//get int value of second param 
		free(maxReqStr);							//free substring memory 
				
		int reqCharIndex = firstSpaceIndex + 1;					//index of char password requires 
		char reqChar = *(curr->value + reqCharIndex);				//get char password requires 
		
		int colonIndex = indexOfChar(curr->value, ':', reqCharIndex);		//finde index of colon in input
		int passLength = strlength(curr->value) - colonIndex;			//calc length of password 		 	
		char * password = substring(curr->value, colonIndex + 2, passLength);	//get password from input to check   
	
			
		//Verify password
		char firstPosChar = *(password + minReq - 1);				//get char at first position 
		char secPosChar = *(password + maxReq - 1);				//get char at second position 
		if( (firstPosChar == reqChar || secPosChar == reqChar) && 
		     firstPosChar != secPosChar) {
			numValid++;							//increment number valid counter
		}
		
		free(password);								//free memory password was using  
		curr = curr->next;							//go to next input in list
	}

	//print results
	printf("Number Valid Passwords(V2): %u\n", numValid);	
}

int main(int argc, char *argv[]) {

	//verify program args
	if(argc != 2) { 
		printf("Ussage: <program> <input file>\n");
		return -1;
	}

	//read input file
	if( readInput(argv[1]) != 1 ) { return -1; } 	//exit program on read file error
	
	part1();	
	part2();
	cleanup();
}
