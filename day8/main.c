#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * The problem for day 8 is to find the value 
 * of the accumulator right before the input 
 * instructs repeat. There are commands: nop,
 * acc, and jmp. The instrutions follow the 
 * format of <opcod> <+-><number>. 
 *
 */


void part1() {

	struct input * curr = inputList;		//get pointer to first command
	int accumulator = 0;				//accumulator tracker 
	int looped = 0;					//boolean for loop
	
	while(!looped) {

		//check for nop command
		if(strstr(curr->value, "nop")) { curr = curr->next; }	
	
		if(strstr(curr->value, "acc")) {
			int l = strlength(curr->value);					//get length of string
			int offset = 5;							//offset to go over opp code
			char * toAdd = substring(curr->value, offset, l-offset); 	//get substring for add/sub
			printf("ToAdd: %s\n", toAdd);	
			free(toAdd);
		}

		looped = 1;
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
