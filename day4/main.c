#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * Day four's problem is to find valid passports.
 * A valid passport must have all eight fields 
 * present. A passport is all the lines of input
 * that are between two new lines. 
 * 
 */

struct passport {
 	char * byr;	//birth year
	char * iyr;	//issue year
	char * eyr;	//expiration year
	char * hgt;	//height 
	char * hcl;	//hair color
	char * ecl;	//eye color
	char * pid;	//passport id
	char * cid;	//country id
};

//keep track of where we are in the input list while getting passports
struct input * currInput;

//Looks at the string passed to it and sets the corrisponding field in pass
void setField(char * fieldData, struct passport * pass) {
	printf("Analyzing %s\n", fieldData);
}

//goes through input list and fills passport struct 
//@param passport * -- pointer to passport object to fill  
void getNextPassport(struct passport * pass) {

	//go through input lines till new line is hit 
	while(*(currInput->value) != '\n') {
	
		int start = 0;					//start of passport param 
		int end = 0;					//end of passport param 
		int lineLength = strlength(currInput->value);	//get input line length 
		for(int i = 0; i < lineLength; i++) {
			char c = *(currInput->value + i);	//get char at position i
			if(c == ' ' || c == '\n') { 	
				end = i;							//set end of param
				int subLength = end - start;
				setField(substring(currInput->value, start, subLength), pass); 	//handle the field string 		
				start = i + 1;							//update start of next field
			}
		}

		currInput = currInput->next;
	}
	
	//move currInput one more time for next time this is called
	currInput = currInput->next;
}

void part1() {

	struct passport * currPass = malloc(sizeof(struct passport));	//create passport 
	getNextPassport(currPass);
}

int main(int argc, char *argv[]) {

	//check for args 
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}

	//read input 
	if( readInput(argv[1]) < 1 ) { return -1; };	//exit if error occurs reading input file
	
	currInput = inputList;	//initalize currInput 
	part1();		//call part1 implementation 
	cleanup();		//clean up input list
}
