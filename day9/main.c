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
 *
 * Part 2 wants us to find a continous string
 * of values in the input that sum to our 
 * invalid sum. Then spit out the sum of the 
 * max and min values in the string. 
 * 
 */

int preambleSize = 25;					//size of preamble
struct node * preamble = NULL;				//preamble queue

//Initalizes preamble queue 
void initPreamble(int size) {
	struct input * curr = inputList;		//get pointer to first input
	int value = atoi(curr->value);			//get first value 
	curr = curr->next;				//go to next input node
	preamble = createList(&value, sizeof(int));	//create preamble queue
		

	for(int i = 0; i < size; i++) {
		int v = atoi(curr->value);		//get int rep of input 
		addNewNode(preamble, &v, sizeof(int));	//add new node to list
		curr = curr->next;			//go to next input 
	}
}

//Checks preamble's sums for the provided sum
//@param sum -- sum to find
//
//@return 1 if has sum, 0 otherwise
int preambleHasSum(int sum) {

	struct node * first = preamble;			//outer pointer 
	struct node * sec = preamble->next;		//inner node pointer
	
	while(first->next) {
		int firstVal = *(int *)first->value;			//get value of out
		while(sec) {
			int secVal = *(int *)sec->value;		//get innner value 
			if(firstVal + secVal == sum) { return 1; }	//sum exists
			sec = sec->next;				//go to next inner value
		}

		first = first->next;					//go to next node
		sec = first->next;					//set inner node to next node
	}

	return 0;
}


int part1() {	
	initPreamble(preambleSize);		//initalize preamble list
	struct input * curr = inputList;	//pointer to first input line

	/* skip over initalized preamble values */
	for(int i = 0; i < preambleSize; i++) {
		curr = curr->next;		
	}

	while(curr) {
	
		int sumToFind = atoi(curr->value);			//get value of current node 
		if(!preambleHasSum(sumToFind)) { 			//check if preamble has the sum
			printf("Illegal Value: %d\n", sumToFind); 	//print invalid value
			deleteList(preamble);				//free list memory 
			return sumToFind;				//get out of here
		}
	
		
		/* preamble has sum so adjust preamble to take new sum */
		preamble = removeFirstNode(preamble);			//remove first node in queue
		addNewNode(preamble, &sumToFind, sizeof(int));		//add new sum to end of list 
		
		curr = curr->next;					//go to next input line
	}
}

void part2(int sum) {

	struct input * begin = inputList;				//outer looper 
	struct input * end = inputList->next;				//inner node looper
		
	while(begin->next) {
		
		int beginVal = atoi(begin->value);			//get beginning node value
		int total = beginVal;					//init total sum value
		int max = beginVal;					//init max 
		int min = beginVal;					//init min
		while(end) {		
			int endVal = atoi(end->value);			//get inner node value	
			if(endVal > max) max = endVal;			//check for max
			if(endVal < min) min = endVal;			//check for min
			total += endVal;				//add value to sum
			if(total == sum) {				//check for our sum
				printf("Key: %d\n", min + max);		//print key
				return;					//get out
			}
			
			if(total > sum) { break; }			//get out of this string if total has passed sum
			end = end->next;				//go to next inner node
		}

		begin = begin->next;					//go to next outer node
		end = begin->next;					//set inner node to next of outer node
	}

}

int main(int argc, char *argv[]) {

	//check program args
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}	

	//read the input file
	readInput(argv[1]);
		
	int inval = part1();	
	part2(inval);	

	//free memory in input list
	cleanup();
}
