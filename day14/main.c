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
 */

struct MemoryData {
	int key;			//mem address 
	char * value;			//value as bit string
	struct MemoryData * next;	//pointer to next memory address
};
struct MemoryData * firstMemoryData = NULL;	//head pointer for memory blocks

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
	
/*	printf("\nValue: %s\n", passedVal);	
	printf("Mask:  %s\n", mask);
	printf("Result:%s\n", result);
*/
	return result;	
	
}

unsigned long getSum() {
	
	unsigned long sum = 0;
	struct MemoryData * curr = firstMemoryData;
	while(curr) {
		unsigned long val = 0;		
		int l = strlength(curr->value);
		for(int i = 0; i < l; i++) {
			if(*(curr->value + i) == '1') {
				val += pow(2, l - i - 1); 
			}
		}
			
		sum += val;
		curr = curr->next;
	}

	return sum;

}

void part1() {

	struct input * curr = inputList;		//get pointer to first input node
	char * currentMask = NULL;			//pointer to current mask 
	while(curr) {
			
		/* handle mask input */
		if(strstr(curr->value, "mask")) {									//check for mask input 
			if(currentMask) { memcpy(currentMask, curr->value, strlength(curr->value) + 1); }		//free previous substring memory if exists
			int indexOfMask = indexOfChar(curr->value, '=', 0) + 2; 					//get index of start of substring
			currentMask = substring(curr->value, indexOfMask, strlength(curr->value) - indexOfMask - 1);	//get mask substring
			//printf("New mask: %s\n", currentMask);								//print mask for debugging
		} 

		/* handle memory input */
		else {
			int frontOfMem = indexOfChar(curr->value, '[', 0) + 1;				//get index of memory address
			int endOfMem = indexOfChar(curr->value, ']', frontOfMem);			//get index of end of memory address
			char * memAddy = substring(curr->value, frontOfMem, endOfMem - frontOfMem);	//get substring of memory address
			int memAddress = atoi(memAddy);							//get in rep of memory address		
			free(memAddy);									//free substring memory 
			
			int indexOfValue = indexOfChar(curr->value, '=', endOfMem) + 1; 		//get index of start of substring
			int l = strlength(curr->value) - 1;
			char * valueString = substring(curr->value, indexOfValue, l - indexOfValue);	//get substring
			int value = atoi(valueString);							//get int rep of value
			free(valueString);								//free substring memory 
			
			char * newValue = applyMask(currentMask, value);				//apply mask to value provided
			
			/* Handle adding to list/updating node */
			struct MemoryData * currMem = firstMemoryData;					//get pointer to head of list
			int updatedFlag = 0;								//flag for if memory was updated or not
			while(currMem) {
				if(currMem->key == memAddress) {		
printf("Updating memory value\n");
					memcpy(currMem->value, newValue, strlength(newValue) + 1);	//update value stored 
					free(newValue);							//free new value memory 
					//printf("Updated Value: %s\n", currMem->value);
					updatedFlag++;							//set updated flag
					break;
				}
				
				currMem = currMem->next;						//go to next memory node
			}				

			if(!updatedFlag) {
				//printf("Creating new memory data\n\taddress: %d, value: %s\n", memAddress, newValue);
				struct MemoryData * newData = malloc(sizeof(struct MemoryData));	//create memory for new node
				newData->key = memAddress;						//set key
				newData->value = malloc(sizeof(char) * (strlength(newValue) + 1));	//create memory for value string
				memcpy(newData->value, newValue, strlength(newValue) + 1);		//copy value info 
				free(newValue);								//free newValue memory				

				if(firstMemoryData) {
					currMem = firstMemoryData;					//set to head node
					while(currMem->next) { currMem = currMem->next; }		//go to end of list
					currMem->next = newData;					//add to end
				}
				else {
					firstMemoryData = newData;					//init head node
				}
			}
		}	
	
		curr = curr->next;			//go to next input 
	}

	//print memory list at end for debugging
	struct MemoryData * currMem = firstMemoryData;
	while(currMem) {
		printf("memAddress: %d, value: %s\n", currMem->key, currMem->value);
		currMem = currMem->next;
	}

	printf("Total Sum: %lu\n", getSum());
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
