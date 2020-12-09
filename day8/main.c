#include <stdio.h>
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
