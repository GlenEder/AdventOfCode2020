#ifndef UTIL_H_
#define UTIL_H_

struct input {
	char * value;		//value of input field
	int visited;		//if node has been visited before or not
	struct input * next;	//next input that was read in 
};

//Methods 
void 	cleanup(void);
int 	readInput(char *);
char *	substring(char *, int, int);	
int 	indexOfChar(char *, char, int);
int 	strlength(char *);
int 	strcompare(char *, char *);

//Global Variables
extern struct input * inputList; 

#endif
