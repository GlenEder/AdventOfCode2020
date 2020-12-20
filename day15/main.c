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
 * 30,000,000. This seemed easy at first but
 * the method I used for part 1 is O(n^2).
 * That's pretty scary now that we are looking
 * at such large numbers. So I looked around at
 * what others were doing and hashmaps were
 * common but C does not have a hashmap library
 * and I'm already days behind now so I saw that
 * others used some big boy arrays.
 *
 * After today's challenge, I can say that I
 * will be much more aware of the optimization
 * of my algorithms. Such a simple problem tanked
 * my computer because of an O(n^2) solution.
 * Never again will I let this happen
 * 				-Glen, Probably
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

	int * latest = malloc(sizeof(int) * 30000000);				//array that holds the last spoken turn of a value
	int * oldest = malloc(sizeof(int) * 30000000);				//array that holds the next oldest turn of a value

	//intialize values to -1
	for(int i = 0; i < 30000000; i++) {
		latest[i] = -1;
		oldest[i] = -1;
	}

	//initalize input
	for(int i = 0; i < inputLength; i++) {
		latest[input[i]] = i;						//sets array[value] to turn number
	}

	//initalize next turn
	int turn = inputLength;							//adjust turn counter for input
	int maxTurn = 30000000;							//max turns
	int lastValueStated = input[inputLength - 1];	//last value stated

	//loop through number of turns desired
	for(turn; turn < maxTurn; turn++) {
		int turnDif = turn - latest[lastValueStated] - 1;				//calculate turn diff
		if(turnDif == 0) {												//if 0, check for older location
			int old = oldest[lastValueStated];							//get older location
			turnDif = old == -1 ? -1 : turn - old - 1;					//calc turn diff, set to -1 if new number
		}
		//printf("Turn %d, Looking For %d, Val @Loc %d, Dif in Turn %d\n", turn, lastValueStated, latest[lastValueStated], turnDif);

		if(turnDif < 0) lastValueStated = 0;							//set 0 if new number is stated
		else lastValueStated = turnDif;									//set new value to turn diff

		//printf("\tSetting %d to turn %d\n", lastValueStated, turn);

		oldest[lastValueStated] = latest[lastValueStated];				//update oldest location
		latest[lastValueStated] = turn;									//update latest location
	}

	printf("Last Value: %d\n", lastValueStated);					//print the last value stated for our output
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
