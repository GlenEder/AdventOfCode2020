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
 */

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


void part1() {
	
	initPreamble(5);
	struct node * curr = preamble;
	while(curr) {
		printf("%d\n", *(int *)curr->value);
		curr = curr->next;
	}

	deleteList(preamble);
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
