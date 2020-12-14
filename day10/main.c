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
 * Part 2 wants us to find the number of different 
 * ways we can arrange our adapters to plug from 
 * the wall into the phone. 
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
	struct node * curr = adapters;					//pointer for looping through list of adapters

	//Add phone's built in adapter to end
	while(curr->next) { curr = curr->next; }			//go to end of list
	int phonesAdapterVal = 3 + *(int *)curr->value;			//calc phones value
	addNewNode(curr, &phonesAdapterVal, sizeof(int));		//add to list
	
	curr = adapters;						//reset looping pointer to front of list

	int oneDifs = 0;						//number of 1 jolt differences 
	int threeDifs = 0;						//number of 3 jolt differences
	int currJolt = 0;						//starting number of jolts	

	while(curr) {
		
		int adapterVal = *(int *)curr->value;			//get value of current adapter in list
		int joltDif = adapterVal - currJolt;			//calc difference between adapter and current jolts 
		if(joltDif == 1) { oneDifs++; }				//increment one jolt dif count
		if(joltDif == 3) { threeDifs++; }			//increment three jolt dif count 			

		if(joltDif > 3) break;					//don't have any adapter that will connect so exit 
		
		currJolt = adapterVal;					//update current jolt level
		curr = curr->next;					//go to next adapter in list
	}	

	printf("Results:\n\tOne Difs: %d\n\tThree Difs: %d\n\tProduct %d\n",oneDifs, threeDifs,  oneDifs * threeDifs);	//print result 
	deleteList(adapters);								//cleanup memory 
}

//Combo struct to help reduce recurion load
struct Combo {
	int key;			
	unsigned long numCombos;
	struct Combo * next;
};

struct Combo * comboList = NULL;

void printComboList() {
	printf("===Combo List===\n");
	struct Combo * curr = comboList;
	while(curr) {
		printf("\tKey: %d, Combos: %lu\n", curr->key, curr->numCombos);
		curr = curr->next;
	}
}

unsigned long numberOfCombos(struct node * start) {

	/* base case of start node being the phone */
	if(start->next == NULL) return 1;
	
	unsigned long numCombs = 0;						//number of combos current node has 
	
	/* check comboList for this adapter */
	struct Combo * currCombo = comboList;
	while(currCombo) {
		if(currCombo->key == *(int *)start->value) {
			 return currCombo->numCombos; 			//if adapter has already been calc'd return its combos 
		}		
		currCombo = currCombo->next;
	}


	/* combo hasn't been checked yet, time for recursion */
	int startingVal = *(int *)start->value;				//save jolt rating of starting node
	struct node * nextAdapter = start->next;
	while(nextAdapter) { 
		if(*(int *)nextAdapter->value - startingVal < 4) {		//check that adapters can connect 
			numCombs += numberOfCombos(nextAdapter);		//recursion call
		}
		else { break; }						//get out of loop
		nextAdapter = nextAdapter->next;			//go to next adapter
	}
	

		
	/* create combo struct */
	struct Combo * newCombo = malloc(sizeof(struct Combo));		//create memory for new combo 
	newCombo->key = startingVal;					//set key
	newCombo->numCombos = numCombs;					//set num combos 
	newCombo->next = NULL;

	
	/* add combo to combo list */
	if(comboList == NULL) { 					//handle adding first combo to list
		comboList = newCombo;
		//printComboList(); 
		return numCombs; 
	}
	currCombo = comboList;						//reset currCombo pointer to front of list
	while(currCombo->next) { currCombo = currCombo->next; }		//go to last combo in list
	currCombo->next = newCombo;					//add new combo to list

	//printComboList();

	/* return number of combos found */
	return numCombs;	

}

void part2() {

	struct node * adapters = createSortedList();			//get sorted list of adapters 
	struct node * curr = adapters;					//pointer for looping through list of adapters

	//Add phone's built in adapter to end
	while(curr->next) { curr = curr->next; }			//go to end of list
	int phonesAdapterVal = 3 + *(int *)curr->value;			//calc phones value
	addNewNode(curr, &phonesAdapterVal, sizeof(int));		//add to list
	

	//Add wall(0) to adapters list 
	int wall = 0;							//value of wall jolts
	adapters = prependNewNode(adapters, &wall, sizeof(int));	//add wall to front of list
	curr = adapters;						//reset looping pointer to front of list
	

	printf("Number of combos: %lu\n", numberOfCombos(curr));
	deleteList(adapters);		
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
