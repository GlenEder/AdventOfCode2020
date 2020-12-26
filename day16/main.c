#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * For day 16 we are at first checking for
 * invalid numbers on our tickets. The ranges
 * for valid inputs are contained in the first
 * segment of the input file. Ignoring our
 * ticket, we are to find the sum of of all
 * the invalid numbers in the tickets.
 */

void part1() {

	struct input * curr = inputList;

	/* get ranges from input file */
	while(strcompare(curr->value, "\n")) {

		int fNumIndex = indexOfNumber(curr->value, 0);							//get index of first number in string
		int fDiv = indexOfChar(curr->value, '-', fNumIndex);					//get index of first '-'
		char * fNumString = positionsSubstring(curr->value, fNumIndex, fDiv);	//get substring of lower value

		int firstLower = atoi(fNumString);										//int rep of substring value
		free(fNumString);														//free substring memory

		int sNumIndex = indexOfNumber(curr->value, fDiv);
		int sEnd = indexOfChar(curr->value, ' ', sNumIndex);
		char * sNumString = positionsSubstring(curr->value, sNumIndex, sEnd);

		int secLower = atoi(sNumString);
		free(sNumString);


		printf("Numbers %d - %d\n", firstLower, secLower);


		curr = curr->next;														//go to next input node
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
