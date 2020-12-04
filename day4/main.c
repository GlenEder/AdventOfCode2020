#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * Day four's problem is to find valid passports.
 * A valid passport must have all eight fields 
 * present. A passport is all the lines of input
 * that are between two new lines. 
 *
 * Note that a only missing a cid field is valid still 
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

	//get data part of line 
	char * data = substring(fieldData, 4, strlength(fieldData) - 4);
	
	//get first char of field to switch on 		
	char c = *fieldData;	
	switch(c) {
		case 'b':							//birth year field
			pass->byr = data;
			break;
		case 'i':							//issue year field
			pass->iyr = data;
			break;
		case 'e':
			if(*(fieldData + 1) == 'y') {				//expiration year field
				pass->eyr = data;
			}
			else {
				pass->ecl = data;				//eye color field
			}
			break;
		case 'h':							
			if(*(fieldData + 1) == 'c') {				//hair color field
				pass->hcl = data;
			}
			else {							//height field
				pass->hgt = data;
			}
			break;
		case 'p':							//passport id field
			pass->pid = data;
			break;
		case 'c':							//country code field 
			pass->cid = data;
			break;
	}	
	
	
}

//goes through input list and fills passport struct 
//@param passport * -- pointer to passport object to fill  
//
//@return 1 if successful in getting new passport, -1 if fail
int getNextPassport(struct passport * pass) {
	

	//base case to get out 
	if(currInput == NULL) { return -1; }

	
	//go through input lines till new line is hit 
	while(currInput && *(currInput->value) != '\n') {		

		int start = 0;					//start of passport param 
		int end = 0;					//end of passport param 
		int lineLength = strlength(currInput->value);	//get input line length 
		for(int i = 0; i < lineLength; i++) {
			char c = *(currInput->value + i);	//get char at position i
			if(c == ' ' || c == '\n') { 	
				end = i;								//set end pos of param
				int subLength = end - start;						//calc length of substring
				char * fieldString = substring(currInput->value, start, subLength);	//get substring for field
				setField(fieldString, pass); 						//handle the field string 		
				start = i + 1;								//update start of next field 	
				free(fieldString);							//free memory of substring
			}
		}

		currInput = currInput->next;
	}
	
	//move currInput one more time for next time this is called
	if(currInput) currInput = currInput->next;

	return 1;
}


//Sets all the fields of the given passport to null and frees the memory of the data there
//@param pass -- passport struct to reset
void resetPassport(struct passport * pass) {
	free(pass->byr);
	pass->byr = NULL;
	free(pass->iyr);
	pass->iyr = NULL;
	free(pass->eyr);
	pass->eyr = NULL;
	free(pass->hgt);
	pass->hgt = NULL;
	free(pass->hcl);
	pass->hcl = NULL;
	free(pass->ecl);
	pass->ecl = NULL;
	free(pass->pid);
	pass->pid = NULL;
	free(pass->cid);
	pass->cid = NULL;
}


void part1() {
	
	//initalize passport struct 
	struct passport * currPass = malloc(sizeof(struct passport)); 
	currPass->byr = malloc(sizeof(char *));
	currPass->iyr = malloc(sizeof(char *));
	currPass->eyr = malloc(sizeof(char *));
	currPass->hgt = malloc(sizeof(char *));
	currPass->hcl = malloc(sizeof(char *));
	currPass->ecl = malloc(sizeof(char *));
	currPass->pid = malloc(sizeof(char *));
	currPass->cid = malloc(sizeof(char *));

	int validPassports = 0;	
	int passesChecked = 0;
	
	while( getNextPassport(currPass) == 1 ) {
		//check for null values, this indicates incomplete passport
		if(	currPass->byr &&
			currPass->iyr &&
			currPass->eyr &&
			currPass->hgt &&
			currPass->hcl &&
			currPass->ecl &&
			currPass->pid 
		  ) {
			validPassports++;
		}

		printf("\rPassports Checked: %d", ++passesChecked);
		resetPassport(currPass);
	} 
	
	//free up passport struct 
	free(currPass);
	printf("\nValid Passports: %d\n", validPassports);
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
