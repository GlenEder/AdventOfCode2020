#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * Part1 for day 7 has us back checking. We
 * must find how many bags our bag can go in
 * using the rules for bags. These rules are 
 * the input. 
 *
 * Note every line follows the pattern:
 * 	<name of bag> contain <number> <another bag name>, <number> <another bag name>, ...
 * 
 */

//linked list node that holds name of bag that can directly/or indirectly hold our bag
struct shinyBag {
	char * name;			//name of bag that can hold our shiny gold bag
	struct shinyBag * next;		//next bag that can hold our shingy bag
};

struct shinyBag * firstBag = NULL;	//head of list for bags that can hold ours

//Adds bag to linked list of bags that can hold ours
//@param newBag -- new shinyBag node to add
void addBag(struct shinyBag * newBag) {
	
	//check if list is empty 
	if(firstBag) {
		struct shinyBag * currBag = firstBag;			//get pointer of first node
		while(currBag->next) { currBag = currBag->next;	}	//go to end of list 
		currBag->next = newBag;					//add new node to end of list 

	}
	else {
		firstBag = newBag;		//set firstBag pointer to the new bag
	}

}

//Checks to see if the bag name provided is in the bag list
//@param name -- name of bag to check 
//
//@return 1 if in list, 0 if not
int bagIsInList(char * name) {

	struct shinyBag * curr = firstBag;		//get pointer to first bag in list
	while(curr) {
		if(!strcmp(name, curr->name)) {		//check if names match 
			return 1;
		}
		curr = curr->next;			//go to next node
	}

	return 0;
}

//Recusive function that may haunt me 
int canHoldOurBag(char * bagInfo) {

	char *frontHalf = strstr(bagInfo, "bags ");			//get pointer to end of bag name
	int indexOfFront = frontHalf - bagInfo - 1;			//get index of end of name
	char *currBagName = substring(bagInfo, 0, indexOfFront);	//get bag name

	printf("Looking at bag: %s\n", currBagName);	

	/* void if looking at our bag */
	if(!strcompare(currBagName, "shiny gold"))  {
		free(currBagName);
		return 0;
	}

	/* Check if bag can directly hold our bag */
	char *shinyBag = strstr(bagInfo, "shiny gold bag");
	if(shinyBag) {	
		//Add current bag to list of bags that can hold ours 
		struct shinyBag * newBag = malloc(sizeof(struct shinyBag *));
		newBag->name = currBagName;
		newBag->next = NULL;
		addBag(newBag);
		return 1;
	}
	
	/* Check if current bag is already in list */
 	if(bagIsInList(currBagName)) return 1;

	/* Recursivly check bags */
	char *backHalf = strstr(bagInfo, "contain");			//get pointer to back 
	int indexOfBack = backHalf - bagInfo;				//get index of contain in input string
	indexOfBack += 8;						//adjust to get first bag it contains 
	
	int endOfInput = indexOfChar(bagInfo, '.', 0);				//get index of end of line
	char *bags = substring(bagInfo, indexOfBack, endOfInput - indexOfBack); 
	

	int indexOfComma = -2;
	int done = 0;
	while(!done) {
		int start = indexOfComma + 2;
		indexOfComma = indexOfChar(bags, ',', start);		//get new position of the comma 
		char * bagName;
		if(indexOfComma < 0) {
			int end = strlength(bags);
			bagName = substring(bags, start, end - start); 
			done = 1;
		}
		else {
			bagName = substring(bags, start, indexOfComma);
		}
		free(bagName); 
	}
	
	free(bags);
	free(currBagName);
	return 0;

}

void part1() {

	struct input * curr = inputList;	//get pointer to first input node
	while(curr) {
		if(canHoldOurBag(curr->value)) {
			printf("Can hold our bag!\n");
		}
	
		curr = curr->next;	
	}

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
