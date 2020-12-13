#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * Day 10 has us violating saftey standards 
 * and daisy chaining adapters together. 
 * Part 1 wants us to chain all adapters 
 * together and find the number of 1 difference 
 * and 3 difference adapters. 
 * 
 */

//Creates a sorted node list using the input values
//@return pointer to first node in list
struct node * createSortedList() {
	
	//Create first node in list
	int nodeValue = atoi(inputList->value);				//get int value of input
	struct node * first = createList(&nodeValue, sizeof(int));	//create first node
	
	//add rest of input	
	struct input * currInput = inputList->next;			//get pointer to next input in list
	while(currInput) {

		
	
		currInput = currInput->next;				//go to next input 
	}

	//return pointer to beginning of sorted list
	return first;
}

void part1() {

	struct node * adapters = createSortedList();			//get sorted list of adapters 
	printf("First node: %d\n", *(int *)adapters->value);		

	deleteList(adapters);	
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
