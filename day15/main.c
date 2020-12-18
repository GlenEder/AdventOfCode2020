#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * Day 15 appears to be a modified version
 * of telephone. Each turn a "person"
 * states the a number, starting with the
 * input values. After the input values,
 * the value stated follows the rules:
 * if the previous value is the first time
 * it is mentioned, the value stated will be 0.
 * Otherwise, the value stated is the turn
 * number - the last turn it was stated.
 *
 * Part 2 wants us to find the value at turn
 * 30,000,000.
 */

int input[] = {9,6,0,10,18,2,1};		//input for day 15
int inputLength = 7;

/*
int input[] = {0, 3, 6};				//test input for day 15
int inputLength = 3;					//should result in 436
*/

void part1() {

	int output[2020] = {0};				//outputs for each turn
	int turn = 0;						//turn tracker

	/* insert our input to output array */
	for(int i = 0; i < inputLength; i++, turn++) {
		output[turn] = input[i];
	}

	while(turn < 2020) {

		int lastPos = turn - 1;			//get last position filled
		int prev = output[lastPos];		//get previous value

		for(int i = lastPos - 1; i >= 0; i--) {
			if(output[i] == prev) {
				//printf("Found %d at pos %d\n", prev, i);
				output[turn] = lastPos - i;			//calculate difference in position
				break;								//get out of loop
			}
		}

		//printf("%d,", output[turn]);
		turn++;							//go to next turn
	}


	//print last turns value
	printf("Value at 2020: %d\n", output[2019]);
}

void part2() {

	int turn = 0;						//turn tracker
	int maxTurn = 30000000;				//max turn for part 2
	int output[maxTurn];				//outputs for each turn

	/* insert our input to output array */
	for(int i = 0; i < inputLength; i++, turn++) {
		output[turn] = input[i];
	}

	while(turn < maxTurn) {

		int lastPos = turn - 1;			//get last position filled
		int prev = output[lastPos];		//get previous value
		int valSet = FALSE;				//set in for loop flag

		for(int i = lastPos - 1; i >= 0; i--) {
			if(output[i] == prev) {
				//printf("Found %d at pos %d\n", prev, i);
				output[turn] = lastPos - i;			//calculate difference in position
				valSet = TRUE;						//set flag
				break;								//get out of loop
			}
		}

		if(!valSet){ output[turn] = 0; }			//set output to 0 if value was not set before

		//printf("%d,", output[turn]);
		turn++;							//go to next turn
	}


	//print last turns value
	printf("Value at %d: %d\n", maxTurn, output[maxTurn - 1]);
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
