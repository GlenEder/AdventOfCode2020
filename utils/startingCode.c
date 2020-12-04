#include <stdio.h>
#include "../utils/util.h"

/*
 * Day four's problem is to find valid passports.
 * A valid passport must have all eight fields 
 * present. A passport is all the lines of input
 * that are between two new lines. 
 * 
 */

void part1() {

}

int main(int argc, char *argv[]) {

	//check for args 
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}

	//read input 
	if( readInput(argv[1]) < 1 ) { return -1; };	//exit if error occurs reading input file
	
	part1();	//call part1 implementation 
	cleanup();	//clean up input list
}
