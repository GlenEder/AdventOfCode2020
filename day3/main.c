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
 *
 * Part two has us checking different slopes.
 * 1 right, 1 down
 * 3 right, 1 down
 * 5 right, 1 down 
 * 7 right, 1 down 
 * 1 right, 2 down (what a surprise)
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
	
		//printf("Pos: %d, charAt: %c, row: %s\n", currPos, *(curr->value + currPos), curr->value); 	
		
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


int checkSlope(int x, int y) {

	
	int lLength = strlength(inputList->value);	//get length of input line
	lLength--;					//account for null term
	int rightMovement = x;				//how far right we move each time
	int downMovement = y;				//how far down we move each time
	int currPos = 0;				//curret x position on map 
	
	int numTrees = 0;				//tree counter 
	struct input * curr = inputList;		//get pointer to beginning of list

	int movedDown = 0;				//how far we've moved down
	int onFinalRow = 0;				//signal to exit while loop 
	
	//loop through lines, checking for those cheeky tress
	while(curr && !onFinalRow) {
	
		//printf("Pos: %d, charAt: %c, row: %s\n", currPos, *(curr->value + currPos), curr->value); 	
		
		//see if current position is a good old tree
		if(*(curr->value + currPos) == '#') numTrees++;
		
		currPos += rightMovement;		//increase position of sled
		currPos %= lLength;			//go back to zero if at end	

		for(movedDown = 0; movedDown < downMovement; movedDown++) {
			if(curr->next == NULL) {
				curr = inputList;	//move back to top of list for overflow
				onFinalRow = 1;		//get out of loop to signal final row
			}
			else {
				curr = curr->next;	//move to next input in list 
			}
		}
	}

	//keep going on if required 
	for(movedDown; movedDown < downMovement; movedDown++) {
		curr = curr->next;
	}
	
	//check for one last tree
	if( *(curr->value + currPos) == '#') numTrees++; 

	return numTrees;
}

void part2() {

	
	//find trees hit on each slope
	int trees1 = checkSlope(1, 1);
	int trees3 = checkSlope(3, 1);
 	int trees5 = checkSlope(5, 1);
	int trees7 = checkSlope(7, 1);
	int trees2 = checkSlope(1, 2);
 	
	//find the product 
	int product = trees1 * trees3 * trees5 * trees7 * trees2;
	
	//spill the beans
	printf("That's alot of trees: %d\n", product);
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
	part2();
	cleanup();
}
