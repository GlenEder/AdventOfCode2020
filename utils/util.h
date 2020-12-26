#ifndef UTIL_H_
#define UTIL_H_

#define TRUE 1
#define FALSE 0

struct input {
	char * value;		//value of input field
	int visited;		//if node has been visited before or not
	struct input * next;	//next input that was read in 
	struct input * prev;	//previous input that was read in 
};

struct node {
	void * key;
	void * value;
	struct node * next;
};

//Interger based node for linked list
struct intNode {
	int  value;		//value of node
	struct intNode * next;	//next node in list  
};	

//Methods 
void 	cleanup(void);
int 	readInput(char *);
char *	substring(char *, int, int);	
int 	indexOfChar(char *, char, int);
int 	strlength(char *);
int 	strcompare(char *, char *);
int 	indexOfNumber(char *, int);
int 	addIntNode(int);

/* node list methods */
struct node * 	createList(void *, size_t);
struct node * 	createKeyedList(void *, void *, size_t, size_t);
struct node * 	addNewNode(struct node *, void *, size_t);
struct node * 	addNewKeyedNode(struct node *, void *, void *, size_t, size_t);
struct node * 	prependNewNode(struct node *, void *, size_t);
struct node * 	prependNewKeyedNode(struct node *, void *, void *, size_t, size_t);
struct node * 	removeFirstNode(struct node *);
void 			deleteList(struct node *);

//Global Variables
extern struct input * inputList; 
extern struct intNode * firstIntNode;

#endif
