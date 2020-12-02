#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * The goal of day 2 is to find all valid passwords 
 * that follow the rule provided in each line.
 * Given input "1-3 a: abcde", there must contain at 
 * least 1 instance 'a' and at most 3 instances of 'a'
 * in the following passcode. Which in the provided input 
 * will pass. 
 */


void part1() {

	struct input * curr = inputList;		//get pointer to beginning of input list
	unsigned int numValid = 0;			//counter for valid passwords found
	
	//loop through input list
	while(curr) {
	
		char * minReqStr = substring(curr->value, 0, indexOfChar(curr->value, '-', 0));		//get substring of first param
		int minReq = atoi(minReqStr);		 
		printf("minReq: %d\n", minReq);
		free(minReqStr);

	
		curr = curr->next;			//go to next input in list
	}
	
}

int main(int argc, char *argv[]) {

	//verify program args
	if(argc != 2) { 
		printf("Ussage: <program> <input file>\n");
		return -1;
	}

	//read input file
	if( readInput(argv[1]) != 1 ) { return -1; } 	//exit program on read file error
	
	part1();	
}
