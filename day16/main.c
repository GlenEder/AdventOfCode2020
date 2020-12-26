#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * For day 16 we are at first checking for
 * invalid numbers on our tickets. The ranges
 * for valid inputs are contained in the first
 * segment of the input file. Ignoring our
 * ticket, we are to find the sum of of all
 * the invalid numbers in the tickets.
 */


struct node * addRange(char * inputSegment, struct node * firstRange) {

	int fNumIndex = indexOfNumber(inputSegment, 0);							//get index of first number in string
	int fDiv = indexOfChar(inputSegment, '-', fNumIndex);					//get index of first '-'
	char * fNumString = positionsSubstring(inputSegment, fNumIndex, fDiv);	//get substring of lower value
	int firstLower = atoi(fNumString);										//int rep of substring value
	free(fNumString);														//free substring memory

	int sNumIndex = indexOfNumber(inputSegment, fDiv);						//get index of second number
	int sEnd = indexOfChar(inputSegment, ' ', sNumIndex);					//get index of space
	if(sEnd < 0) {
		sEnd = strlength(inputSegment);										//if no space, get index of end of string
	}

	char * sNumString = positionsSubstring(inputSegment, sNumIndex, sEnd);	//get second number substring
	int secLower = atoi(sNumString);										//convert to int
	free(sNumString);														//free substring memory

	/* Add range to ranges list */
	if(firstRange) {
		addNewKeyedNode(firstRange, &firstLower, &secLower, sizeof(int), sizeof(int));
	}
		/* Create first range node */
	else {
		/* Make key the lower value of the range, and the value the upper value of the range */
		firstRange = createKeyedList(&firstLower, &secLower, sizeof(int), sizeof(int));
	}

	return firstRange;
}

void part1() {

	struct input * curr = inputList;
	struct node * firstRange = NULL;

	/* get ranges from input file */
	while(strcompare(curr->value, "\n")) {
		firstRange = addRange(curr->value, firstRange);												//add first range
		int backIndex = indexOfChar(curr->value, 'o', indexOfNumber(curr->value, 0));				//get index of o in or
		char * secondRange = positionsSubstring(curr->value, backIndex, strlength(curr->value));	//get substring of second range
		firstRange = addRange(secondRange, firstRange);												//add second range to list
		curr = curr->next;																			//go to next input node
	}

	/* print list for debugging */
	struct node * currRange = firstRange;
	while(currRange) {
		printf("Range: %d - %d\n", *(int *)currRange->key, *(int *)currRange->value);
		currRange = currRange->next;
	}


	deleteList(firstRange);																			//free list memory
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
