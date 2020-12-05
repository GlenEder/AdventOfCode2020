#include <stdio.h>
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
 */

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

			
		//printf("minR: %d, maxR: %d\n", minRow, maxRow);
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

int main(int argc, char *argv[]) {

	//check program args
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}	

	//read the input file
	readInput(argv[1]);
	
	part1();
}
