#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 *
 * The goal of day 1 is to find the two values in the input 
 * that sum to 2020 and calculate their product. 
 *
 *
 *
 */


int main(int argc, char *argv[]) {

	//verify program params
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");	
		return -1;
	} 
		
	//handle reading input
	readInput(argv[1]);
	
	//Brute force this shit 
	struct input * curr = inputList;		//get pointer to first input 
	
	//loop through inputs
	while(curr) {
		int currValue = atoi(curr->value);	//get int rep of input value
			
		struct input * inputToAdd = curr->next;	//get pointer to next input in line
		
		//loop through rest of input to check for matches
		while(inputToAdd) {
			int toAdd = atoi(inputToAdd->value);
			if( (currValue + toAdd) == 2020 ) {
				printf("Key: %d\n", toAdd * currValue);
				return 1;
			}

			//go to next node
			inputToAdd = inputToAdd->next;
		}

		//go to next node 
		curr = curr->next;
	}

}
