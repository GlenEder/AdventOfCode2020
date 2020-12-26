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
		printf("%s", curr->value);
		curr = curr->next;
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
