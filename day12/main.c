#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../utils/util.h"

/*
 * It's day 12, and that means we're 
 * on a boat. The days problem has us navigating 
 * the waters and findinding the Manhattan 
 * distance the boat has traveled.  
 */

void part1() {

	int heading = 90;		//start facing east
	int northSouth = 0;		//north south tracker
	int eastWest = 0;		//east west tracker

	struct input * curr = inputList;	//get pointer to first input 
	while(curr) {
	
		char c = *curr->value;								//get direction char
		char * amountString = substring(curr->value, 1, strlength(curr->value) - 1);	//get value substring
		int  amount = atoi(amountString);						//get int representation 
		free(amountString);								//free substring memory 
		
		/* Handle Directions */
		switch(c) {					
			case 'N': 				
				northSouth += amount;	
				break;
			case 'S':
				northSouth -= amount;
				break;
			case 'E': 
				eastWest += amount;
				break;
			case 'W': 
				eastWest -= amount;
				break;
			case 'R':
				heading += amount;
				heading %= 360;			//handle overflow
				break;
			case 'L':
				heading -= amount;
				if(heading < 0) heading += 360;	//handler underflow?
				break;
			case 'F':
				if(heading == 90) { eastWest += amount; }
				else if(heading == 180) { northSouth -= amount; }
				else if(heading == 270) { eastWest -= amount; }
				else if(heading == 0) { northSouth += amount; }
				else { printf("HEADING ERROR\n"); }				
		}
	
		//printf("Dir: %c, Amt: %d, New Heading: %d, Updated Cords: (%d, %d)\n", c, amount, heading, eastWest, northSouth);	
	
		curr = curr->next;				//go to next input node
	} 

	//print results
	printf("Manhattan Distance: %d\n", abs(northSouth) + abs(eastWest));	

}

void part2() {

	int waypointEW = 10;		//starting east west cord of waypoint
	int waypointNS = 1;		//starting north south cord of waypoint

	int xPos = 0;
	int yPos = 0;
	
	struct input * curr = inputList;	//get pointer to first input 
	while(curr) {
	
		char c = *curr->value;								//get direction char
		char * amountString = substring(curr->value, 1, strlength(curr->value) - 1);	//get value substring
		int  amount = atoi(amountString);						//get int representation 
		free(amountString);								//free substring memory 
		
		/* Handle Directions */
		switch(c) {					
			case 'N': 				
				waypointNS += amount;	
				break;
			case 'S':
				waypointNS -= amount;
				break;
			case 'E': 
				waypointEW += amount;
				break;
			case 'W': 
				waypointEW -= amount;
				break;
			case 'R':
				if(amount == 90) {
					int oldNS = waypointNS;
					waypointNS = -waypointEW;	
					waypointEW = oldNS;
				}
				else if(amount == 180) {
					waypointNS *= -1;
					waypointEW *= -1;
				}	
				else if(amount == 270) {
					int oldNS = waypointNS;
					waypointNS = waypointEW;
					waypointEW = -oldNS;
				}
				break;
			case 'L':
				if(amount == 270) {
					int oldNS = waypointNS;
					waypointNS = -waypointEW;	
					waypointEW = oldNS;
				}
				else if(amount == 180) {
					waypointNS *= -1;
					waypointEW *= -1;
				}	
				else if(amount == 90) {
					int oldNS = waypointNS;
					waypointNS = waypointEW;
					waypointEW = -oldNS;
				}
				break;
			case 'F':
				xPos += waypointEW * amount;
				yPos += waypointNS * amount;
		}
	
		//printf("Dir: %c, Amt: %d, New Heading: %d, Updated Cords: (%d, %d)\n", c, amount, heading, eastWest, northSouth);	
	
		curr = curr->next;				//go to next input node
	} 

	//print results
	printf("Manhattan Distance: %d\n", abs(xPos) + abs(yPos));	

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
