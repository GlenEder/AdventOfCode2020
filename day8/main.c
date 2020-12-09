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
	
	while(1) {

		//check if visited 
		if(curr->visited) break;
		
		//set visited value for current node 
		curr->visited = 1;

		//check for nop command
		if(strstr(curr->value, "nop")) { 
			printf("here\n"); 
			//curr = curr->next; 
			continue;
		}

		printf("Also here\n");

		int jumping = 0;						//jumping flag	
		if(strstr(curr->value, "jmp")) { jumping = 1; }			//set flag for jump instruction 

		int adding = 0;							//add/sub flag
		if( *(curr->value + 4) == '+' ) { adding = 1; }			//set adding flag

		int l = strlength(curr->value);					//get length of string
		int offset = 5;							//offset to go over opp code
		char * toAdd = substring(curr->value, offset, l-offset); 	//get substring for add/sub
		offset  = atoi(toAdd);						//get int value of add/sub value 
			
		if(jumping) {
				
		}
		else {
			accumulator = adding ? accumulator + offset : accumulator - offset;		//add or subtract value to accumlator 
			curr = curr->next;								//go to next instruction 
		}

		free(toAdd);
	}

	printf("Accumulator: %d\n", accumulator);

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
