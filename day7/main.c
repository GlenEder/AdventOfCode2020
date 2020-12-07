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


//Returns the bags name for the given input line 
//@param bagInfo -- input line about bag
//
//@return pointer to sub string of the bag name
char * getBagNameFromInput(char * bagInfo) {

	char *frontHalf = strstr(bagInfo, "bags ");			//get pointer to end of bag name
	int indexOfFront = frontHalf - bagInfo - 1;			//get index of end of name
	char *currBagName = substring(bagInfo, 0, indexOfFront);	//get bag name

	return currBagName;
}

//Recusive function that may haunt me 
int canHoldOurBag(char * bagName) {

	//printf("Checking bag %s\n", bagName);

	/* void if looking at our bag */
	if(!strcompare(bagName, "shiny gold"))  {
		return 0;
	}

	
	//go through input list and find bag info line
	struct input * currLine = inputList;
	char * bagInfo;
	while(currLine) {
		
		char *res = strstr(currLine->value, bagName);		//get pointer to bag name
		if(res) {
			if(res - currLine->value == 0) {
				bagInfo = currLine->value;		//set local pointer
				//printf("Bag Info: %s\n", bagInfo);
				break;					//get out of loop
			}
		}
		currLine = currLine->next;				//go to next node 		
	}


	/* Check if bag can directly hold our bag */
	char *shinyBag = strstr(bagInfo, "shiny gold bag");
	if(shinyBag) {	
		//Add current bag to list of bags that can hold ours 
		struct shinyBag * newBag = malloc(sizeof(struct shinyBag *));
		newBag->name = bagName;
		newBag->next = NULL;
		addBag(newBag);
		return 1;
	}
	

	/* Recursivly check bags */
	char *backHalf = strstr(bagInfo, "contain");			//get pointer to back 
	int indexOfBack = backHalf - bagInfo;				//get index of contain in input string
	indexOfBack += 8;						//adjust to get first bag it contains 
	
	int endOfInput = indexOfChar(bagInfo, '.', 0);				//get index of end of line
	char *bags = substring(bagInfo, indexOfBack, endOfInput - indexOfBack); 
	

	int indexOfComma = -2;
	int done = 0;
	int canHoldBag = 0;
	while(!done) {
		int start = indexOfComma + 2;
		indexOfComma = indexOfChar(bags, ',', start);		//get new position of the comma 
		char * bagName;						//bag name to look further into 
		if(indexOfComma < 0) {
			int end = strlength(bags);
			bagName = substring(bags, start, end - start); 
			done = 1;
		}
		else {
			bagName = substring(bags, start, indexOfComma);
		}

		
		//see if back holds no other bags		
		if(strstr(bagName, "no other bag"))  {
			free(bagName);
			continue;
		} 

		
		char * res = strstr(bagName, "bag");
		int end = res - bagName - 1;	
		int numberOffset = 2;
		char * subBagName = substring(bagName, numberOffset, end - numberOffset);
		
		
		//Check if current bag is already in list 
		if(bagIsInList(subBagName)) {
			free(subBagName);
			canHoldBag = 1;
			continue;
		} 

		int canHold = canHoldOurBag(subBagName);
		if(canHold) canHoldBag = 1;
		free(bagName); 
	}
	
	free(bags);
	return canHoldBag;

}

void part1() {

	struct input * curr = inputList;	//get pointer to first input node
	int total = 0;				//total number of bags that can be on outside
	while(curr) {
		char * currBag = getBagNameFromInput(curr->value);
		if(canHoldOurBag(currBag)) {
			total++;
			//printf("Bag can hold our bag!\n\n\n");
		}
		else {
			free(currBag);	
		}
		curr = curr->next;
	}

	printf("Total: %d\n", total);

}

//returns the totatl number of bags that are held inside the provided bag 
//@param bagName -- name of bag to find how many bags are inside 
//
//@return number of total bags inside given bag
int getBagsInsideBag(char * bagName) {

	printf("Checking for bags inside bag: %s\n", bagName);

	/* Go through input list and find bag info line */
	struct input * currLine = inputList;
	char * bagInfo;							//place to store the bags info 
	while(currLine) {
		
		char *res = strstr(currLine->value, bagName);		//get pointer to bag name
		if(res) {
			if(res - currLine->value == 0) {
				bagInfo = currLine->value;		//set local pointer
				//printf("Bag Info: %s\n", bagInfo);
				break;					//get out of loop
			}
		}
		currLine = currLine->next;				//go to next node 		
	}


	/* We now have the bags info */

	/* Recursivly check bags */
	char *backHalf = strstr(bagInfo, "contain");			//get pointer to back 
	int indexOfBack = backHalf - bagInfo;				//get index of contain in input string
	indexOfBack += 8;						//adjust to get first bag it contains 
	
	int endOfInput = indexOfChar(bagInfo, '.', 0);				//get index of end of line
	char *bags = substring(bagInfo, indexOfBack, endOfInput - indexOfBack); 
	

	int indexOfComma = -2;
	int done = 0;
	int totalBags = 0;
	while(!done) {
		int start = indexOfComma + 2;
		indexOfComma = indexOfChar(bags, ',', start);		//get new position of the comma 
		char * bagName;						//bag name to look further into 
		if(indexOfComma < 0) {
			int end = strlength(bags);
			bagName = substring(bags, start, end - start); 
			done = 1;
		}
		else {
			bagName = substring(bags, start, indexOfComma);
		}

		
		//see if back holds no other bags		
		if(strstr(bagName, "no other bag"))  {
			free(bagName);
			continue;
		} 

		
		printf("Subbag info: %s\n", bagName);
		totalBags += *bagName - '0';		//convert char to int value we want 	
			
		
		free(bagName); 
	}
	
	free(bags);
	return totalBags;
	

}

void part2() {

	/* need to find line about our bag first */
	struct input * currLine = inputList;
	while(currLine) {
		char * bagname = getBagNameFromInput(currLine->value);
		if(!strcompare(bagname, "shiny gold")) {
			printf("Total inner bags: %d\n", getBagsInsideBag(bagname));
			free(bagname);
			return;
		}
		currLine = currLine->next;
	}

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
