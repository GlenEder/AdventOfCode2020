#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../utils/util.h"

/*
 * It's time for me to work on day 14!
 * I graduated college today so I'm 
 * hoping this will go just as well.
 * We are working with bit masks. Using
 * the the most recent mask in the input, 
 * we are to edit "memory address"'s 
 * values, utilizing the mask with the
 * value provided. 
 *
 * Note: All values to set fit in an int
 *
 * Part 1 should not have taken so long, 
 * however I am dumb and forget to init
 * the next pointer to null when creating
 * new nodes.
 * 
 * Part 2 I read wrong so this is going to 
 * take a bit longer than I want it to. The 
 * value is set to all the memory addresses 
 * that the mask emits.  
 */

struct node * firstMem = NULL;

//Applys the given mask to the value 
//@param mask -- mask to use on value
//@parma value -- value to be masked
//
//@return bit string result of mask on value
char * applyMask(char * mask, int value) {	

	char * result = malloc(sizeof(char) * 37);		//create memory for new value  
	char passedVal[37] = {0};				//create temp array for storing value bits
	for(int i = 0; i < 4; i++) { passedVal[i] = '0'; }	//init extra four to 0
	
	int j = 4;
	for(int i = sizeof(value) * 8 - 1; i >= 0; i--, j++) {
		passedVal[j] = (value & (1 << i)) ? '1' : '0';		//shift through bits and assign value
	}

	int length = strlength(mask);							//get length of mask 
	for(int i = 0; i < length; i++) {
		char maskChar = *(mask + i);						//get mask char 
		*(result + i) = maskChar == 'X' ? passedVal[i] : maskChar;		//set result value based on mask 
		
		//printf("Val: %c, Mask: %c, Result: %c\n", passedVal[i], maskChar, *(result + i));
	}	

	*(result + 36) = 0;
/*	
	printf("\nValue: %s\n", passedVal);	
	printf("Mask:  %s\n", mask);
	printf("Result:%s\n", result);
*/
	return result;	
	
}

//Calculates the sum of the values in the memory list
//@return sum of memory list
unsigned long getSum() {
	
	unsigned long sum = 0;
	struct node * curr = firstMem;
	while(curr) {
		unsigned long val = 0;		
		int l = strlen((char *)curr->value);
		for(int i = 0; i < l; i++) {
			if(*((char *)curr->value + i) == '1') {
				val += pow(2, l - i - 1); 
			}
		}
			
		sum += val;
		curr = curr->next;
	}

	return sum;

}

void part1() {

	struct input * curr = inputList;			        //get pointer to first input node
	char * currentMask = malloc(sizeof(char) * 38);		//pointer to current mask 
	while(curr) {
			
		/* handle mask input */
		if(strstr(curr->value, "mask")) {									                                //check for mask input
			int indexOfMask = indexOfChar(curr->value, '=', 0) + 2; 					                        //get index of start of substring
			char * newMask = substring(curr->value, indexOfMask, strlength(curr->value) - indexOfMask - 1); 	//get mask substring
			memcpy(currentMask, newMask, strlength(newMask) + 1); 						                        //copy new mask into masks memory
			free(newMask);                                                                                      //free substring memory
		} 

		/* handle memory input */
		else {
			int frontOfMem = indexOfChar(curr->value, '[', 0) + 1;				        //get index of memory address
			int endOfMem = indexOfChar(curr->value, ']', frontOfMem);          			//get index of end of memory address
			char * memAddy = substring(curr->value, frontOfMem, endOfMem - frontOfMem);	//get substring of memory address
			unsigned long memAddress = atoi(memAddy);												//get in rep of memory address
			free(memAddy);																//free substring memory
			
			int indexOfValue = indexOfChar(curr->value, '=', endOfMem) + 1; 				//get index of start of substring
			int l = strlength(curr->value) - 1;												//get length of input string
			char * valueString = substring(curr->value, indexOfValue, l - indexOfValue);	//get substring
			int value = atoi(valueString);													//get int rep of value
			free(valueString);																//free substring memory
			
			char * newValue = applyMask(currentMask, value);								//apply mask to value provided
			
			/* Handle adding to list/updating node */
			struct node * currMem = firstMem;					//get pointer to head of list
			int updated = FALSE;								//updated flag
			while(currMem) {
				unsigned long currKey = *(unsigned long *)currMem->key;			//get key of current node
				if(currKey == memAddress) {										//check key against new memory slot
					memcpy(currMem->value, newValue, strlen(newValue) + 1);		//copy new value into nodes memory
					free(newValue);												//free newValues memory
					updated = TRUE;												//set updated flag
				}

				//go to next node
				currMem = currMem->next;
			}


			if(!updated) {
				/* Create a new node */
				if(firstMem) {
					addNewKeyedNode(firstMem, &memAddress, newValue, sizeof(unsigned long), sizeof(char) * strlen(newValue) + 1);
				}
				else {
					firstMem = createKeyedList(&memAddress, newValue, sizeof(unsigned  long), sizeof(char) * strlen(newValue) + 1);
				}
			}

		}
		curr = curr->next;			//go to next input 
	}

/*	//print memory list at end for debugging
	struct MemoryData * currMem = firstMemoryData;
	while(currMem) {
		printf("memAddress: %d, value: %s\n", currMem->key, currMem->value);
		currMem = currMem->next;
	}
*/
	printf("Total Sum: %lu\n", getSum());
	deleteList(firstMem);
}



//Applys the given mask to the value 
//@param mask -- mask to use on value
//@parma value -- value to be masked
//
//@return bit string result of mask on value
char * applyMaskV2(char * mask, int value) {	
	
	//printf("Val: %d\n", value);
	char * result = malloc(sizeof(char) * 37);		//create memory for new value  
	char passedVal[37] = {0};				//create temp array for storing value bits
	for(int i = 0; i < 4; i++) { passedVal[i] = '0'; }	//init extra four to 0
	
	int j = 4;
	for(int i = sizeof(value) * 8 - 1; i >= 0; i--, j++) {
		passedVal[j] = (value & (1 << i)) ? '1' : '0';		//shift through bits and assign value
	}

	int length = strlength(mask);							//get length of mask 
	for(int i = 0; i < length; i++) {
		char maskChar = *(mask + i);						//get mask char 
		*(result + i) = maskChar == '0' ? passedVal[i] : maskChar;		//set result value based on mask 
		
		//printf("Val: %c, Mask: %c, Result: %c\n", passedVal[i], maskChar, *(result + i));
	}	

	*(result + 36) = 0;

	//printf("\nValue: %s\n", passedVal);
	//printf("Mask:  %s\n", mask);
	//printf("Result:%s\n", result);

	return result;	
	
}

void setMemory(char * mems, int value) {
	printf("Setting memory: %s to value %d\n", mems, value);
}

void part2() {

	struct input * curr = inputList;			        //get pointer to first input node
	char * currentMask = malloc(sizeof(char) * 38);		//pointer to current mask
	while(curr) {

		/* handle mask input */
		if(strstr(curr->value, "mask")) {									                                //check for mask input
			int indexOfMask = indexOfChar(curr->value, '=', 0) + 2; 					                        //get index of start of substring
			char * newMask = substring(curr->value, indexOfMask, strlength(curr->value) - indexOfMask - 1); 	//get mask substring
			memcpy(currentMask, newMask, strlength(newMask) + 1); 						                        //copy new mask into masks memory
			free(newMask);                                                                                      //free substring memory
		}

			/* handle memory input */
		else {
			int frontOfMem = indexOfChar(curr->value, '[', 0) + 1;				        //get index of memory address
			int endOfMem = indexOfChar(curr->value, ']', frontOfMem);          			//get index of end of memory address
			char * memAddy = substring(curr->value, frontOfMem, endOfMem - frontOfMem);	//get substring of memory address
			int memAddress = atoi(memAddy);												//get in rep of memory address
			free(memAddy);																//free substring memory

			int indexOfValue = indexOfChar(curr->value, '=', endOfMem) + 1; 				//get index of start of substring
			int l = strlength(curr->value) - 1;												//get length of input string
			char * valueString = substring(curr->value, indexOfValue, l - indexOfValue);	//get substring
			int value = atoi(valueString);													//get int rep of value
			free(valueString);																//free substring memory

			char * newValue = applyMaskV2(currentMask, memAddress);								//apply mask to address
			setMemory(newValue, value);

		}
		curr = curr->next;			//go to next input
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
