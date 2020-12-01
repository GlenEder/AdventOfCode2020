#ifndef UTIL_H_
#define UTIL_H_

struct input {
	char * value;		//value of input field
	struct input * next;	//next input that was read in 
};

//Methods 
int readInput(char *);


//Global Variables
extern struct input * inputList; 

#endif
