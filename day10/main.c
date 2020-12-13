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
		
		nodeValue = atoi(currInput->value);			//get in value of current input 
		if(nodeValue < *(int *)first->value) {
			struct node * newNode = createList(&nodeValue, sizeof(int));	//create new head node
			newNode->next = first;						//set next to old head
			first = newNode;						//upate head node
		}
		else {
			
			/* loop through current sorted list to find spot to add */
			struct node * currSorted = first->next;				//get pointer to next node in sorted list
			struct node * prevSorted = first;				//save pointer to prev for when adding node
			int added = 0;							//flag for adding at end
			while(currSorted) {
				
				if(nodeValue < *(int *)currSorted->value) {
					struct node * newNode = createList(&nodeValue, sizeof(int));	//create new node for list
					newNode->next = currSorted;					//set next for new node
					prevSorted->next = newNode;					//set next for prev node
					added = 1;							//flag added node
					break;								//get out of loop
				}
				
				/* handle going to next node in list */ 
				prevSorted = currSorted;					
				currSorted = currSorted->next;				
			}

			
			if(!added) { addNewNode(prevSorted, &nodeValue, sizeof(int)); } 			//add new node to end of list
			
		}
	
		currInput = currInput->next;				//go to next input 
	}

	//return pointer to beginning of sorted list
	return first;
}

void part1() {

	struct node * adapters = createSortedList();			//get sorted list of adapters 
	struct node * curr = adapters;
	while(curr) {
		printf("%d\n", *(int *)curr->value);	
		curr = curr->next;
	}	
	
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
