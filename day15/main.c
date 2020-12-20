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

	int * latest = malloc(sizeof(int) * 30000000);
	int * oldest = malloc(sizeof(int) * 30000000);

	//intialize values
	for(int i = 0; i < 30000000; i++) {
		latest[i] = -1;
		oldest[i] = -1;
	}
	for(int i = 0; i < inputLength; i++) {
		latest[input[i]] = i;
	}

	//initalize next turn
	int turn = inputLength;
	int maxTurn = 30000000;
	int lastValueStated = input[inputLength - 1];

	for(turn; turn < maxTurn; turn++) {
		int turnDif = turn - latest[lastValueStated] - 1;
		if(turnDif == 0) {
			int old = oldest[lastValueStated];
			turnDif = old == -1 ? -1 : turn - old - 1;
		}
		//printf("Turn %d, Looking For %d, Val @Loc %d, Dif in Turn %d\n", turn, lastValueStated, latest[lastValueStated], turnDif);

		if(turnDif < 0) lastValueStated = 0;
		else lastValueStated = turnDif;

		//printf("\tSetting %d to turn %d\n", lastValueStated, turn);

		oldest[lastValueStated] = latest[lastValueStated];
		latest[lastValueStated] = turn;
	}

	printf("Last Value: %d\n", lastValueStated);
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
