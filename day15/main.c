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

/*
int input[] = {9,6,0,10,18,2,1};		//input for day 15
int inputLength = 7;
*/


int input[] = {0, 3, 6};				//test input for day 15
int inputLength = 3;					//should result in 436


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

	struct node * headOutput = createKeyedList(&turn, &input[0], sizeof(int), sizeof(int));
	//printf("Created head output %d, %d", *(int *)headOutput->key, *(int *)headOutput->value);

	/* insert our input to output linked list */
	for(int i = 1; i < inputLength; i++) {
		turn++;
		headOutput = prependNewKeyedNode(headOutput, &turn, &input[i], sizeof(int), sizeof(int));
	}

	//printf("Input took us to turn %d\n", turn);

	turn++;											//increment turn before loop
	while(turn < maxTurn) {

		int prev = *(int *)headOutput->value;		//get previous output value
		struct node * curr = headOutput->next;			//get previous output node
		int newValue = 0;							//new value to add to output list
		//printf("\nTurn %d, Checking for %d -- ", turn, prev);
		while(curr) {
			int val = *(int *)curr->value;					//get current nodes value
			//printf("%d,", val);
			if(val == prev) {
				int lastSeen = *(int *)curr->key;			//get key of last seen value
				//printf(" Found @ pos %d ", lastSeen);
				newValue = turn - lastSeen - 1;					//calc difference between nodes keys
				break;
			}

			curr = curr->next;								//go to next node
		}

		headOutput = prependNewKeyedNode(headOutput, &turn, &newValue, sizeof(int), sizeof(int));
		//printf(" ====> Added output %d %d\n", *(int *)headOutput->key, *(int *)headOutput->value);
		printf("\rTurn: %d", turn);
		turn++;							//increment turn counter
	}


	//print last turns value
	printf("\nValue at %d: %d\n", maxTurn, *(int *)headOutput->value);
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
