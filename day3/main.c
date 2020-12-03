#include <stdio.h>
#include "../utils/util.h"


/*
 * The problem for day 3 involves us sledding on 
 * a map (input.txt), where '.' is open and '#' 
 * are trees. The first part has us moving to the 
 * right 7 spots and down 1 row each move. We are
 * to find how many trees we run into. 
 * 
 * Note: each line is the same length, if we go past
 * that length, the input line repeats itself
 */

void part1() {
	int lLength = strlength(inputList->value);	//get length of input line
	lLength--;					//account for null term
	int rightMovement = 3;				//how far right we move each row
	int currPos = 0;				//curret x position on map 
	
	int numTrees = 0;				//tree counter 
	struct input * curr = inputList;		//get pointer to beginning of list
		
	//loop through lines, checking for those cheeky tress
	while(curr) {
	
		printf("Pos: %d, charAt: %c, row: %s\n", currPos, *(curr->value + currPos), curr->value); 	
		
		//see if current position is a good old tree
		if(*(curr->value + currPos) == '#') numTrees++;
		
		currPos += rightMovement;		//increase position of sled
		currPos %= lLength;			//go back to zero if at end	
		curr = curr->next;
	}

	//have to go one extra row for problem 
	if(*(inputList->value + currPos) == '#') numTrees++;	

	printf("Number of trees we ran into: %d\n", numTrees);
}

int main(int argc, char *argv[]) {

	//check program params
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}

	//handle reading input 
	readInput(argv[1]);
	
	part1();

}
