#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * For day 16 we are at first checking for
 * invalid numbers on our tickets. The ranges
 * for valid inputs are contained in the first
 * segment of the input file. Ignoring our
 * ticket, we are to find the sum of of all
 * the invalid numbers in the tickets.
 */

/* Ticket Section code was made during Part 2*/
struct ticketSection {
	int id;							//line number of section in input
	int validPositions;				//using positions 0-19 for setting valid positions
	int lowerRange[2];				//lower range of valid numbers
	int upperRange[2];				//upper range of valid numbers
	struct ticketSection * next;	//next section
};

struct ticketSection * firstTicketSection = NULL;


/*
 * Adds data to ticket section nodes
 * @param id -- ticket section id
 * @param low -- lower value in range to add
 * @param high -- upper value in range to add
 * @param isUpperRange -- if is the upper range of the two ranges
 */
void addTicketSectionData(int id, int low, int high, int isUpperRange) {

	//check to see if node exists already
	struct ticketSection * currSection = firstTicketSection;
	while(currSection) {

		//compare id's
		if(currSection->id == id) {

			//add range
			if(isUpperRange) {
				currSection->upperRange[0] = low;
				currSection->upperRange[1] = high;
			}
			else {
				currSection->lowerRange[0] = low;
				currSection->lowerRange[1] = high;
			}

			//exit function
			return;
		}

		//go to next section
		currSection = currSection->next;
	}



	//If section doesn't exist add to list
	struct ticketSection * newSection = (struct ticketSection *)malloc(sizeof(struct ticketSection));
	newSection->id = id;
	newSection->validPositions = 1048575;	//decimal equal of 20 1's in binary
	//add range
	if(isUpperRange) {
		newSection->upperRange[0] = low;
		newSection->upperRange[1] = high;
	}
	else {
		newSection->lowerRange[0] = low;
		newSection->lowerRange[1] = high;
	}

	//assign first ticket
	if(firstTicketSection == NULL) {
		firstTicketSection = newSection;
	}
	else {
		//Add to end of list
		struct ticketSection * currSection = firstTicketSection;
		while(currSection->next != NULL) { currSection = currSection->next; }
		currSection->next = newSection;
	}
}

//Checks if the number is within a range
//@param number -- value to check
//@param firstRange -- first range node in ranges list
//
//@return TRUE if valid, FALSE otherwise
int isValidNumber(int number, struct node * firstRange) {

	while(firstRange) {
		if(number >= *(int *)firstRange->key && number <= *(int *)firstRange->value)
			return TRUE;
		firstRange = firstRange->next;
	}

	return FALSE;
}


//Adds range to ranges list given the input string
//@param inputSegment -- string to find range in
//@param firstRange -- pointer to head of range list
//@param sectionId -- id of section to add data to			/* Part 2 addition */
//
//@return pointer to head of updated range list
struct node * addRange(char * inputSegment, struct node * firstRange, int sectionId) {

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
	int sectionCount = 0;

	/* get ranges from input file */
	while(strcompare(curr->value, "\n")) {
		firstRange = addRange(curr->value, firstRange, sectionCount);								//add first range
		int backIndex = indexOfChar(curr->value, 'o', indexOfNumber(curr->value, 0));				//get index of o in or
		char * secondRange = positionsSubstring(curr->value, backIndex, strlength(curr->value));	//get substring of second range
		firstRange = addRange(secondRange, firstRange, sectionCount);								//add second range to list
		curr = curr->next;																			//go to next input node
		sectionCount++;																				//increment section id counter
	}

	//print list for debugging
/*	struct node * currRange = firstRange;
	while(currRange) {
		printf("Range: %d - %d\n", *(int *)currRange->key, *(int *)currRange->value);
		currRange = currRange->next;
	}
*/

	/* Get to nearby tickets to check */
	while(*curr->value != 'n') { curr = curr->next; }			//skip to line 'nearby tickets'
	curr = curr->next;											//to to next to start checking the first ticket

	/* loop through tickets and check for bad values */
	int sumOfBadNums = 0;
	while(curr) {

		char * token = strtok(curr->value, ",");
		while(token) {
			int number = atoi(token);
			if(!isValidNumber(number, firstRange)) { sumOfBadNums += number; }
			token = strtok(NULL, ",");
		}


		curr = curr->next;
	}

	printf("Sum of bad values: %d\n", sumOfBadNums);
	deleteList(firstRange);																			//free list memory
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
	//part2();

	//free memory in input list
	cleanup();
}
