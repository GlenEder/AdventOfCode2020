#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * It's time for me to work on day 14!
 * I graduated college today so I'm 
 * hoping this will go just as well.
 * We are working with bit masks. Using
 * the the most recent mask in the input, 
 * we are to edit "memory address"'s 
 * values, utilizing the mask with the
 * value provided. 
 */

char * applyMask(char * mask, int value) {
	
	char * result = malloc(sizeof(char) * 37);		//create memory for new value  
	char passedVal[37] = {0};				//create temp array for storing value bits
	for(int i = 0; i < 4; i++) { passedVal[i] = '0'; }	//init extra four to 0
	
	int j = 4;
	for(int i = sizeof(value) * 8 - 1; i >= 0; i--, j++) {
		passedVal[j] = (value & (1 << i)) ? '1' : '0';
	}

	printf("\nValue: %s\n", passedVal);	
	printf("Mask:  %s\n", mask);
	int length = strlength(mask);
	for(int i = 0; i < length; i++) {
		char maskChar = *(mask + i);						//get mask char 
		*(result + i) = maskChar == 'X' ? passedVal[i] : maskChar;		//set result value based on mask 
		
		//printf("Val: %c, Mask: %c, Result: %c\n", passedVal[i], maskChar, *(result + i));
	}	
	
	printf("Result:%s\n", result);
	return result;	
	
}

void part1() {

	struct input * curr = inputList;		//get pointer to first input node
	char * currentMask = NULL;			//pointer to current mask 
	while(curr) {
			
		/* handle mask input */
		if(strstr(curr->value, "mask")) {									//check for mask input 
			if(currentMask) { free(currentMask); }								//free previous substring memory if exists
			int indexOfMask = indexOfChar(curr->value, '=', 0) + 2; 					//get index of start of substring
			currentMask = substring(curr->value, indexOfMask, strlength(curr->value) - indexOfMask - 1);	//get mask substring
			//printf("New mask: %s\n", currentMask);								//print mask for debugging
		} 

		/* handle memory input */
		else {
			int frontOfMem = indexOfChar(curr->value, '[', 0) + 1;				//get index of memory address
			int endOfMem = indexOfChar(curr->value, ']', frontOfMem);			//get index of end of memory address
			char * memAddy = substring(curr->value, frontOfMem, endOfMem - frontOfMem);	//get substring of memory address
			int memAddress = atoi(memAddy);							//get in rep of memory address		
			free(memAddy);									//free substring memory 
			
			int indexOfValue = indexOfChar(curr->value, '=', endOfMem) + 1; 		//get index of start of substring
			int l = strlength(curr->value) - 1;
			char * valueString = substring(curr->value, indexOfValue, l - indexOfValue);	//get substring
			int value = atoi(valueString);							//get int rep of value
			free(valueString);								//free substring memory 
			applyMask(currentMask, value);
		}	

		curr = curr->next;			//go to next input 
	}

}

void part2() {

}

int main(int argc, char *argv[]) {

	//check program args
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}	

	//read the input file
	readInput(argv[1]);
	
	part1();
	part2();	

	//free memory in input list
	cleanup();
}
