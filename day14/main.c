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

	struct input * curr = inputList;			//get pointer to first input node
	char * currentMask = malloc(sizeof(char) * 38);		//pointer to current mask 
	while(curr) {
			
		/* handle mask input */
		if(strstr(curr->value, "mask")) {									//check for mask input 
			int indexOfMask = indexOfChar(curr->value, '=', 0) + 2; 					//get index of start of substring
			char * newMask = substring(curr->value, indexOfMask, strlength(curr->value) - indexOfMask - 1);	//get mask substring
			memcpy(currentMask, newMask, strlength(newMask) + 1); 						//copy new mask into masks memory 
			free(newMask);
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
					memcpy(currMem->value, newValue, strlength(newValue) + 1);	//update value stored 
					free(newValue);							//free new value memory 
					updatedFlag++;							//set updated flag
					break;
				}
				
				currMem = currMem->next;						//go to next memory node
			}				

			if(!updatedFlag) {
				struct MemoryData * newData = malloc(sizeof(struct MemoryData));	//create memory for new node
				newData->key = memAddress;						//set key
				newData->next = NULL;							//set next to null
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

/*	//print memory list at end for debugging
	struct MemoryData * currMem = firstMemoryData;
	while(currMem) {
		printf("memAddress: %d, value: %s\n", currMem->key, currMem->value);
		currMem = currMem->next;
	}
*/
	printf("Total Sum: %lu\n", getSum());
}



//Applys the given mask to the value 
//@param mask -- mask to use on value
//@parma value -- value to be masked
//
//@return bit string result of mask on value
char * applyMaskV2(char * mask, int value) {	
	
	printf("Val: %d\n", value);	
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

	printf("\nValue: %s\n", passedVal);	
	printf("Mask:  %s\n", mask);
	printf("Result:%s\n", result);

	return result;	
	
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
