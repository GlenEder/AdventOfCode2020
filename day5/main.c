#include <stdio.h>
#include "../utils/util.h"

/*
 * Day 5 is about those dang bording passes. 
 * The use binary space partitioning to represent 
 * where the seat of the ticket is. There are 
 * a total of 128 rows and 8 columns. Our goal
 * for part 1 is to find the seat, and use its 
 * seat position to calculate the highest id.
 * 
 * Seat Id = Row * 8 + Column
 *
 */

int main(int argc, char *argv[]) {

	//check program args
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}	

	//read the input file
	readInput(argv[1]);

}
