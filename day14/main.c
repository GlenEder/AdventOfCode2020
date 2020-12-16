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

long applyMask(char * mask, int value) {

	
	
}

void part1() {

	struct input * curr = inputList;		//get pointer to first input node
	char * currentMask = NULL;			//pointer to current mask 
	while(curr) {
			
		/* handle mask input */
		if(strstr(curr->value, "mask")) {									//check for mask input 
			if(currentMask) { free(currentMask); }								//free previous substring memory if exists
			int indexOfMask = indexOfChar(curr->value, '=', 0) + 1; 					//get index of start of substring
			currentMask = substring(curr->value, indexOfMask, strlength(curr->value) - indexOfMask - 1);	//get mask substring
			printf("New mask: %s\n", currentMask);								//print mask for debugging
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
			printf("Value %d\n", value);		
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
