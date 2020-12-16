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

void part1() {

	struct input * curr = inputList;		//get pointer to first input node
	char * currentMask = NULL;			//pointer to current mask 
	while(curr) {
			
		if(strstr(curr->value, "mask")) {	//check for mask input 
			if(currentMask) { free(currentMask); }
			int indexOfMask = indexOfChar(curr->value, '=', 0) + 1; 
			currentMask = substring(curr->value, indexOfMask, strlength(curr->value) - indexOfMask);
			printf("New mask: %s\n", currentMask);
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
