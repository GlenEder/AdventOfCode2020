#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * It's day 9, and that means we're looking
 * into XMAS. That is eXchange-Masking 
 * Addition System. The system puts 25 
 * values at the beginning to start the 
 * encryption. From there, the next number 
 * must be a sum of two of the previous 25 
 * values. For part 1, we are to find the fisrt
 * number that does not follow this rule in 
 * our input. 
 */



//Given the size of the preable provided, finds the frist wrong
//value in the input file
//@param preamble -- size of preamble buffer
void findWrongSum(int preamble) {

	int sumOptions[preamble] = {0};		//create array for checking sums
	struct input * curr = inputList;	//get pointer to first input line

	//fill preamble data 
	for(int i = 0; i < preamble; i++) {
		sumOptions[i] = atoi(curr->value);	//convert input to int
		curr = curr->next;			//go to next node
	}

	//loop through input, find sum error
	while(curr) {
		int sumToFind = atoi(curr->value);	//get int value of next input 
		
	}

}


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
