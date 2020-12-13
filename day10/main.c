#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * Day 10 has us violating saftey standards 
 * and daisy chaining adapters together. 
 * Part 1 wants us to chain all adapters 
 * together and find the number of 1 difference 
 * and 3 difference adapters. 
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
