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
struct lineVisited {
	int lineNumber;			//line number that was visited 
	struct lineVisited * next;	//next line number visited 
};

struct lineVisited * visitedLines = NULL;	//pointer to head of visted lines list


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
			curr = curr->next; 
			continue;
		}


		int jumping = 0;						//jumping flag	
		if(strstr(curr->value, "jmp")) { jumping = 1; }			//set flag for jump instruction 

		int adding = 0;							//add/sub flag
		if( *(curr->value + 4) == '+' ) { adding = 1; }			//set adding flag

		int l = strlength(curr->value);					//get length of string
		int offset = 5;							//offset to go over opp code
		char * toAdd = substring(curr->value, offset, l-offset); 	//get substring for add/sub
		offset  = atoi(toAdd);						//get int value of add/sub value 
		free(toAdd);							//free substring memory 
			
		if(jumping) {	
			for(int i = 0; i < offset; i++) {
				curr = adding ? curr->next : curr->prev;	//got to next or previous instruction 	
			}
		}
		else {
			accumulator = adding ? accumulator + offset : accumulator - offset;		//add or subtract value to accumlator 
			curr = curr->next;								//go to next instruction 
		}
	}

	printf("Accumulator: %d\n", accumulator);

}




//Adds new lineVisted node to visted lines list
//@param line_number -- line number of instruction
void addLineVisited(int line_number) {

	struct lineVisited * newLine = malloc(sizeof(struct lineVisited));	//create memory for new node 	
	newLine->lineNumber = line_number;					//set line number
	newLine->next = NULL;							//init to null
	
	if(visitedLines) {
		struct lineVisited * currLine = visitedLines;			//get pointer to front of list
		while(currLine->next) { currLine = currLine->next; }		//go to last node
		currLine->next = newLine;					//add new node to end
	}	
	else { visitedLines = newLine; }					//init list to new node 

}

//Checks if the line number provided is in the visited lines list
//@param line -- line number to check 
//
//@return 1 if exists, 0 if not
int lineHasBeenVisited(int line) {
	struct lineVisited * curr = visitedLines;
	while(curr) {
		if(curr->lineNumber == line) return 1;
		curr = curr->next;
	}

	return 0;
}

//Follows instructions from start and checks for loops
//@param accumulator -- value to continue on with 
//@param lineNumber -- current linenumber 
//@param start -- instruction to go with
//@param flag -- set to 1 if success, otherwise 0
//
//@return accumulator value  
int continueInstructions(int accumulator, int lineNumber,  struct input * start, int * flag) {
	
	struct input * curr = start;
	while(curr) {
		
		printf("Handling line %s\n", curr->value);		

		//check for loops 
		if(lineHasBeenVisited(lineNumber)) { *flag = 0; return accumulator; }

		//add to list 
		addLineVisited(lineNumber);		

		//check for nop command
		if(strstr(curr->value, "nop")) { 
			curr = curr->next; 
			lineNumber++;
			continue;
		}


		int jumping = 0;						//jumping flag	
		if(strstr(curr->value, "jmp")) { jumping = 1; }			//set flag for jump instruction 

		int adding = 0;							//add/sub flag
		if( *(curr->value + 4) == '+' ) { adding = 1; }			//set adding flag

		int l = strlength(curr->value);					//get length of string
		int offset = 5;							//offset to go over opp code
		char * toAdd = substring(curr->value, offset, l-offset); 	//get substring for add/sub
		offset  = atoi(toAdd);						//get int value of add/sub value 
		free(toAdd);							//free substring memory 
			
		if(jumping) {	
			for(int i = 0; i < offset; i++) {
				curr = adding ? curr->next : curr->prev;		//got to next or previous instruction 	
				lineNumber = adding ? lineNumber + 1: lineNumber - 1;	//increment line number 
			}
		}
		else {
			accumulator = adding ? accumulator + offset : accumulator - offset;		//add or subtract value to accumlator 
			curr = curr->next;								//go to next instruction 
			lineNumber++;									//increment line number
		}
		

	}

	//Success
	*flag = 1;
	return accumulator;
}

void part2() {
	
	struct input * curr = inputList;		//get pointer to first instruction 
	int accumulator = 0;				//current accumulator value
	int instructions = 0;				//number of instructions gone to 
	int instrBefore = 0;				//number of instructions before devitation 
	int lineNumber = 0;				//current line number 
	int pathFound = 1;				//if correct path found
	
	int result = continueInstructions(accumulator, lineNumber, curr, &pathFound);
	
	if(!pathFound) printf("Result: %d\n", result);

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
