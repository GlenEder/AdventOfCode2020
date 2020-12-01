#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

struct input * inputList = NULL;		

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

	newInput->value = malloc(length * sizeof(char *));		//create memory to store value
	if(newInput->value == NULL) { free(newInput); return -1; }	//free created node if value malloc fails	
	memcpy(newInput->value, value, length);				//set node value		

	//check that there is something already in list
	if(inputList) {
		struct input * currInput = inputList;				//curr input struct looking at
		struct input * lastInput;

		//get to end of list
		while(currInput) {
			lastInput = currInput; 
			currInput = currInput->next;
		}	

		lastInput->next = newInput;	//add new input to end of list
	}
	
	//input list is empty
	else {
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

	printf("File <%s> opened\n", inputfile);
	
	char * line;					//current line being read from file
	size_t length = 0;				//holds address of variable that holds input buffer size	 	
	ssize_t lLength = 0;				//size of input

	//read file line by line 
	while((lLength = getline(&line, &length, fp)) != -1) {
		printf("Read line(%ld): %s", lLength, line);	//print read line for debugging		
		addInputToList(line, lLength);
	} 	
	
	free(line);			//free memory 
	fclose(fp);			//close file reader
	return 1;			//return success signal 
}


