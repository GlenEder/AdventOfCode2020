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
	lLength--;					//account for terminating char	
	int rightMovement = 3;				//how far right we move each row
	int currPos = 0;				//curret x position on map 
	
	
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
