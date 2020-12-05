#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * Day 5 is about those dang bording passes. 
 * The use binary space partitioning to represent 
 * where the seat of the ticket is. There are 
 * a total of 128 rows and 8 columns. Our goal
 * for part 1 is to find the seat, and use its 
 * seat position to calculate the highest id.
 * 
 * Seat Id = Row * 8 + Column
 *
 * Part 2 involves us finding our seat on the 
 * plane. To do this, we need to find the gap 
 * between two seats.
 *
 * After completing today's challenge I can say
 * that I have learned from previous short commings.
 * I can't remember the exact day, but I recall 
 * stating that I wish I sorted the list instead 
 * of brute forcing it. Well today was that day!
 * In part 2, as each node was added to the linked 
 * list, they were added in ascending order making 
 * finding the empty seat trivial subtraction.  
 */

struct seat {
	int id;			//seat's id
	struct seat * next; 	//pointer to next seat
};

struct seat * head = NULL;	//head of seat list

int getSeatId(char * seatId) {

	int l = strlength(seatId);		//get lenght of string	
	int maxRow = 128;			//max row of seat
	int minRow = 0;				//min row of seat				 
	int maxCol = 8;				//max column of seat
	int minCol = 0;				//min column of seat
	
	for(int i = 0; i < l; i++) {
		char c = *(seatId + i);			//get char at current position 
					
		if(c == 'F') {
			maxRow -= (maxRow - minRow) / 2; 	//go to front half
		}
		
		else if(c == 'B') {
			minRow += (maxRow - minRow) / 2;	//go to back half
		}

		else if(c == 'R') {
			minCol += (maxCol - minCol) / 2;	//go to right side 
		}
	
		else if(c == 'L') {
			maxCol -= (maxCol - minCol) / 2;	//go to left side
		}

	}

	//Return calculated seat id
	return (minRow * 8) + minCol;
	

}

void part1() {
	
	struct input * curr = inputList;		//current input node
	int maxId = -1;					//current max id
	
	//loop through input calculating seat ids
	while(curr) {
		int id = getSeatId(curr->value);	//get seat id
		if(id > maxId) maxId = id;		//set max if greater than current max id
		curr = curr->next;			//go to next input node
	}	

	printf("Max ID: %d\n", maxId);

}

//adds seat struct to list
//@param seat -- seat struct node pointer
void addSeatToList(struct seat * newSeat) {
	
	//set first node if needed
	if(head == NULL) {
		head = newSeat;
		return;
	}

	//add in order of value of id increasing 
	if(newSeat->id < head->id) {
		newSeat->next = head;	//set next to head 
		head = newSeat;		//update to new head of list
		return;
	}

	struct seat * lastSeat = head;			//pointer to previous node in seat list
	struct seat * currSeat = head->next;		//pointer to current node in seat list
	while(currSeat) {
		if(newSeat->id > currSeat->id) {
			lastSeat = currSeat;		//update last seat node 
			currSeat = currSeat->next; 	//go to next node 
		}
		else {
			
			//add new seat to list here 
			lastSeat->next = newSeat;	//set previous node's next to new seat node
			newSeat->next = currSeat;	//set new seat's next to current node
			return;
		}
	}


	//at end of list, therefore add to end of list 
	lastSeat->next = newSeat;

}


void part2() {
	
	struct input * curr = inputList;		//current input node
	while(curr) {
		int id = getSeatId(curr->value);	//get id 
		
		//create seat node 
		struct seat * newSeat = malloc(sizeof(struct seat));	//malloc seat pointer
		newSeat->id = id;					//set seat id 
		newSeat->next = NULL;					//init next to null for saftey 
		
		//add to list 
		addSeatToList(newSeat);

		curr = curr->next;			//go to next input node
	}	

	struct seat * currSeat = head;			//get pointer to first node in id list
	int prevSeatId = currSeat->id;			//save last seat id 
	int mySeat = -1;				//my seat's id
	currSeat = currSeat->next;			//go to next node to start comparisons
	free(head);					//free first node in lists memory 
	while(currSeat) {
		
		if(currSeat->id - prevSeatId == 2){ 	//check if two seats have a gap between the two
			mySeat = prevSeatId + 1; 	//set my seats id
		}
		prevSeatId = currSeat->id;		//update prev seats id
		struct seat * toFree = currSeat;	//save pointer to current seat 
		currSeat = currSeat->next;		//go to next node in seat list
		free(toFree);				//free memory of previous seat node
	}

	printf("My seat's id: %d\n", mySeat);
	
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
	cleanup();
}
