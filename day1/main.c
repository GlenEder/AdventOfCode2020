#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 *
 * The goal of day 1 is to find the two values in the input 
 * that sum to 2020 and calculate their product. 
 *
 * Part 2 has us looking for 3 values that sum to 2020
 * and calulating their product.
 *
 * Note that provided input has no negative values
 */


void part1() {

	//Brute force this shit 
	struct input * curr = inputList;		//get pointer to first input 

	//loop through inputs
	while(curr) {
		int currValue = atoi(curr->value);	//get int rep of input value
			
		struct input * inputToAdd = curr->next;	//get pointer to next input in line
		
		//loop through rest of input to check for matches
		while(inputToAdd) {
			int toAdd = atoi(inputToAdd->value);			//get int value of toAdd input
			if( (currValue + toAdd) == 2020 ) {			//check if sum is 2020
				printf("Part1 Key: %d\n", toAdd * currValue);	//print product of two values
				return;					
			}

			//go to next node
			inputToAdd = inputToAdd->next;
		}

		//go to next node 
		curr = curr->next;
	}

	//no match was found, more like something went wrong
	printf("No match found...\n");
}


void part2() {

	//I chose C so that I could brute force stuff and it feel fast
	

	
	struct input * first = inputList;		//get pointer to beginning of input list
		
	//loop through 
	while(first) {
	
		int firstInt = atoi(first->value);	//get int rep of value
		
		struct input * second = first->next;	//get pointer to next input in list
		
		//loop through second inputs 
		while(second) {
			
			int secondInt = atoi(second->value);	//get int rep of second value
			
			//see if first two inputs are over 2020
			if( (firstInt + secondInt) >= 2020) {
				//move on because adding a third isnt going to help
				second = second->next;
			}	
			else {

				//WE NEED MORE!!!!
				struct input * third = second->next;		//get pointer to next input
				
				while(third) {
					int thirdInt = atoi(third->value);	//get int rep of third value 
				
					//check for bingo 
					if( (firstInt + secondInt + thirdInt) == 2020 ) {
						printf("Part2 Key: %d\n", firstInt * secondInt * thirdInt);	//print key 
						return;								//get out of this brute force beauty 
					}

					third = third->next;	
				}
			}

			//go to next node
			second = second->next;	
		}

		//go to next starting node
		first = first->next;
	}

}

int main(int argc, char *argv[]) {

	//verify program params
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");	
		return -1;
	} 
		
	//handle reading input
	readInput(argv[1]);
	
	part1();
	
}
