#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

struct input * inputList = NULL;		//initalize inputList header

//Frees all memory taken in input list
void cleanup() {
	
	while(inputList) {
		struct input * toFree = inputList;	//get pointer to current list node
		inputList = inputList->next;		//move looping pointer to next node
		free(toFree->value);			//free value memory 
		free(toFree);				//free nodes memory 
	}

    inputList = NULL;
}

//Creates new input node and adds to end of input list
//@param value -- pointer to input string to store
//@param length -- size of input string
//@return -- returns 1 if success, -1 on fail
int addInputToList(char * value, ssize_t length) {

	struct input * newInput = (struct input *)malloc(sizeof(struct input));	//create new input  	
	
	//check for proper memory allocation 		
	if(newInput == NULL) {
		printf("ERROR: Failed to allocate input struct.\n");
		return -1;
	}

	newInput->visited = 0;						//set visited to 0
	newInput->value = malloc(length * sizeof(char *));		//create memory to store value
	if(newInput->value == NULL) { free(newInput); return -1; }	//free created node if value malloc fails	
	memcpy(newInput->value, value, length);				//set node value		

	//check that there is something already in list
	if(inputList) {
		struct input * currInput = inputList;				//curr input struct looking at
		struct input * lastInput;

		//get to end of list
		while(currInput) {
			lastInput = currInput; 		//update last pointer
			currInput = currInput->next;	//go to next node in list
		}	
		newInput->prev = lastInput;	//set prev pointer 
		lastInput->next = newInput;	//add new input to end of list
	}
	
	//input list is empty
	else {
		newInput->prev = NULL;		//set prev to null
		newInput->next = NULL;		//set next to null
		inputList = newInput;		//set first node in list
	}

	return 1;
}

//Reads file 
//@param inputfile -- character pointer to input file string
int readInput(char * inputfile) {

	FILE *fp;			//create file pointer
	fp = fopen(inputfile, "r");	//open file for reading
	
	if(fp == NULL) return -1;	//ensure that file opened 

	//printf("File <%s> opened\n", inputfile);
	
	char * line = NULL;					//current line being read from file
	size_t length = 0;				//holds address of variable that holds input buffer size	 	
	ssize_t lLength = 0;				//size of input

	//read file line by line 
	while((lLength = getline(&line, &length, fp)) != -1) {
		//printf("Read line(%ld): %s", lLength, line);	//print read line for debugging
		addInputToList(line, lLength);
	} 	
	
	free(line);			//free memory
	fclose(fp);			//close file reader
	return 1;			//return success signal 
}

//Prints input list to console
void printInput() {
    printf("===Input===\n");
    struct input * curr = inputList;
    while(curr) {
        printf("%s\n", curr->value);
        curr = curr->next;
    }
}

//Creates a copy of string in memory
//@param string -- string to copy
//
//@return pointer to new string
char * copyString(char * string) {
    int length = strlength(string);
    char * copy = (char *)calloc(length + 1, sizeof(char *));
    memcpy(copy, string, length);
    return copy;
}

//Returns pointer to c string that is substring of provided string 
//@param string -- pointer to character array to get substring of 
//@param start -- index of array to start at
//@param length -- how far to go in string (includes start index value)
//
//@return pointer to desired substring 
char * substring(char * string, int start, int length) {
		
	char * toReturn = malloc( (length + 1) * sizeof(char));		//create char array to store substring in 
		
	for(int i = 0; i < length; i++) {
		*(toReturn + i)  = *(string + start + i);			//store characters in return array
	}

	*(toReturn + length)  = '\0'; 					//set null term

	return toReturn;
}

//Returns pointer to c string that is substring of provided string
//@param string -- pointer to character array to get substring of
//@param start -- index of array to start at
//@param end -- position of end  of substring
//
//@return pointer to desired substring
char * positionsSubstring(char * string, int start, int end) {
	int length = end - start;										//calc length to use legacy substring method
	if(length < 0) return NULL;										//error check on length
	return substring(string, start, length);						//call legacy substring method
}

//Returns index of character in string 
//@param string -- string to look in 
//@param toFind -- character looking for 
//@param start -- starting index to look for
//
//@return value of index, -1 if not found
int indexOfChar(char * string, char toFind, int start) {

	char * curr = string + start;		//get starting position
	int index = start;			//index tracker 
	while(*curr) {
		if(*curr == toFind) {
			return index;		//return index if char found
		}
	
		index++;			//increment index tracker
		curr++;				//go to next character
	}

	return -1;				//char not found
}


//Returns length of string provided
//@param string -- string to find length of 
//
//@return length of provided string
int strlength(char * string) {
	int length = 0;				//length counter
	while(*(string++)) { length++; }		//increment counter
	return length;				//return length counter
}

//Compares the two strings provided 
//@param s1 -- first string
//@param s2 -- second string 
//
//@return 0 if same, 1 if s1 is greater, -1 if s2 is greater
int strcompare(char * s1, char * s2) {
	int l = strlength(s1);		//get length of string 
	for(int i = 0; i < l+1; i++) {
		if(*(s1 + i) > *(s2 + i)) {
			return 1;
		}
		else if (*(s1 + i) < *(s2 + i)) {
			return -1;
		}	
	}

	return 0;

}

//Finds the index of the first number in the given string after the starting value
//@param s -- string to look in for number
//@param start -- starting location in string to look at
//
//@return index of first number occurrence in string, -1 if none found
int indexOfNumber(char * s, int start) {

	s = s + start;							//start position to look at
	int pos = start;						//position tracker
	while(*s) {
		if(*s < '0' || *s > '9') {			//check if not number
			pos++;							//increase position tracker
			s++;							//go to next char
		}
		else return pos;					//return position of number
	}

	return -1;								//no number found, signal error
}

//Creates a new node and returns pointer to node
//@param value -- void pointer to value 
//@param size -- size of value to store
//
//@return pointer to new node, null if error occured 
struct node * createList(void * value, size_t size) {

	struct node * newNode = malloc(sizeof(struct node));		//create memory for new node
	if(newNode) {	
		newNode->value = malloc(size);				//get memory for value
		if(newNode->value == NULL) return NULL;			//memory check 
		memcpy(newNode->value, value, size);			//init value
		newNode->key = NULL;					//init key
		newNode->next = NULL;					//init next
	}
	return newNode;							//return pointer to new node
}

//Creates a new keyed head node
//@param key -- value of key for node
//@param value -- value of new node
//@param keySize -- size of key
//@param valueSize -- size of value to store
//
//@return pointer to new node, null on error
struct node * createKeyedList(void * key, void * value, size_t keySize, size_t valueSize) {

	struct node * newNode = createList(value, valueSize);	//use legacy code to create node
	if(newNode == NULL) return NULL;						//error check
	newNode->key = malloc(keySize);							//get memory for key
	if(newNode->key == NULL) return NULL;					//memory check
	memcpy(newNode->key, key, keySize);						//copy key data into new memory

	return newNode;											//return the new keyed node
}

//Adds a new node to the end of the list provided 
//@param list -- linked list to add node to
//@param value -- value of new node
//@param size -- size of value to store
//
//@return pointer to new node, null on error
struct node * addNewNode(struct node * list, void * value, size_t size) {

	if(list == NULL) return NULL;					//check that list provided is not null 

	struct node * newNode = malloc(sizeof(struct node));		//create memory for new node
	if(newNode == NULL) { return NULL; }				//check for memory error

	newNode->value = malloc(size);					//get memory for value
	if(newNode->value == NULL) return NULL;				//memory check 
	memcpy(newNode->value, value, size);				//init value
	newNode->key = NULL;								//init key
	newNode->next = NULL;								//init next
	
	while(list->next) { list = list->next; }			//go to end of list
	list->next = newNode;						//add node to end of list
		
	return newNode;							//return pointer to new node			
}


//Adds a new node to the end of the list provided with key field
//@param list -- linked list to add node to
//@param key -- value of key for node
//@param value -- value of new node
//@param keySize -- size of key
//@param valueSize -- size of value to store
//
//@return pointer to new node, null on error
struct node * addNewKeyedNode(struct node * list, void * key, void * value, size_t keySize, size_t valueSize) {

	struct node * newNode = addNewNode(list, value, valueSize);			//utilize legacy node creation
	if(newNode == NULL) return NULL;									//error check from node creation
	newNode->key = malloc(keySize);										//create memory for key
	if(newNode->key == NULL) return NULL;								//memory creation error check
	memcpy(newNode->key, key, keySize);									//copy value into memory

	return newNode;														//return new node with key
}

//Adds a new node to the front of the provided list
//@param head -- head of list to prepend node to 
//@param value -- value of new node	
//@param size -- size of value to store
//
//@return 
struct node * prependNewNode(struct node * head, void * value, size_t size) {

	if(head == NULL) return NULL;					//check that list provided is not null

	struct node * newNode = malloc(sizeof(struct node));		//get memory for node
	if(newNode == NULL) return NULL;				//check for error with memory get

	newNode->value = malloc(size);					//get memory for value
	if(newNode->value == NULL) return NULL;				//memory check 
	memcpy(newNode->value, value, size);				//init value
	newNode->key = NULL;						//init key to null
	newNode->next = head;						//add to front of list
		
	return newNode;							//return pointer to new node
}

//Adds a new node to the front of the provided list with key
//@param list -- linked list to add node to
//@param key -- value of key for node
//@param value -- value of new node
//@param keySize -- size of key
//@param valueSize -- size of value to store
//
//@return pointer to new node, null on error
struct node * prependNewKeyedNode(struct node * head, void * key, void * value, size_t keySize, size_t valueSize) {

	struct node * newNode = prependNewNode(head, value, valueSize);		//utilize legacy code
	if(newNode == NULL) return NULL;									//error check from node creation call

	newNode->key = malloc(keySize);										//create memory for key
	if(newNode->key == NULL) return NULL;								//error check
	memcpy(newNode->key, key, keySize);									//fill key memory

	return newNode;														//return new node
}

//Removes the first node from list and frees its content
//@param head -- first node in list 
//
//@return pointer to new head of list
struct node * removeFirstNode(struct node * head) {
	struct node * toReturn = head->next;		//save next pointer
	free(head->key);							//free head nodes key memory
	free(head->value);							//free head nodes value memory
	free(head);									//free head node memory
	return toReturn;							//return new heads pointer
}

//Finds the length of the provided linked list
//@param start -- node to start counting from
//
//@return length of list from head
int lengthOfList(struct node * start) {
    if(start == NULL) return 0;             //NULL check
    int l = 0;                              //length counter
    while(start) {                          //loop through node list
        l++;
        start = start->next;
    }
    return l;                               //return length
}

//Frees memory of all nodes in provided list
//@param list -- first node to delete in list
void deleteList(struct node * list) {
	while(list) {
		struct node * toFree = list;		//get pointer to current node
		list = list->next;					//move to next node
		free(toFree->key);					//free this node's key memory if key was used
		free(toFree->value);				//free this node's value memory
		free(toFree);						//free node memory
	}
}


// Function to set the kth bit of n to 1
//@param n -- number to shift bit in
//@param k -- position in number to set bit
//
//@return resulting number with bit set
int setBit(int n, int k) {
    return (n | (1 << k));
}

// Function to set the kth bit of n to 0
//@param n -- number to shift bit in
//@param k -- position in number to set bit
//
//@return resulting number with bit set to 0
int clearBit(int n, int k) {
    return (n & (~(1 << k)));
}

// Function to set the kth bit of n to 1
//@param n -- number to toggle bit in
//@param k -- position in number to set bit
//
//@return resulting number with bit flipped
int toggleBit(int n, int k) {
    return (n ^ (1 << k));
}

//Finds the bit in the kth spot to return
//@param n -- number to search in
//@param k -- position in number
//
//@return the bit at the kth position
int getBit(int n, int k) {
    return (n & (1 << k));
}

//Counts number of bits in n that are set to 1
//@param n -- number to check
//
//@return number of bits set to 1 in n
int countSetBits(int n) {
    //counter for set bits
    int count = 0;
    //loop through number till no 1's remain
    for(int i = 0; i < 32; i++) {
        if(n & 1) count++;
        n >>= 1;
    }
    return count;
}

//Returns the position of the first bit found from the left
//@param n -- number to check
//
//@return position of bit in number
int getFirstBitPos(int n) {
    //counter for set bits
    int count = 0;
    //loop through number till no 1's remain
    for(int i = 0; i < 32; i++) {
        if(!(n & 1)) count++;
        else return count;
        n >>= 1;
    }
    // number had no bits set
    return -1;
}

//Creates binary string of the number in memory
//@param n -- number to convert to binary
//
//@return pointer to string in memory
char * toBinaryString(int n) {
    //calc size of string
    int buffer_size = sizeof(n) * 8 + 1;
    //get memory for string
    char * buffer = (char *)calloc(buffer_size, sizeof(char));
    //error check on malloc
    if(buffer == NULL) return NULL;
    //loop through int printing bits to buffer
    for (int i = 31; i >= 0; i--) {
        buffer[i] = (n & 1) + '0';
        n >>= 1;
    }
    //return pointer to string
    return buffer;
}

//Puts the binary rep of n into buffer
//@param buffer -- buffer of size 33 min
//@param n -- number to convert to binary
void setBinaryString(char * buffer, int n) {
    if(buffer == NULL) return;
    //loop through int printing bits to buffer
    for (int i = 31; i >= 0; i--) {
        buffer[i] = (n & 1) + '0';
        n >>= 1;
    }
}

//Sets terminal output to red
void red() {
    printf("\033[1;31m");
}

//Sets terminal output to yellow
void green() {
    printf("\033[1;32m");
}

//Resets terminal output color
void reset () {
    printf("\033[0m");
}





