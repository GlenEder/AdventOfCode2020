#include <stdio.h>
#include "../utils/util.h"


int main(int argc, char *argv[]) {

	if(argc != 2) return -1;
		
	//call read input for testing right now
	readInput(argv[1]);

	//verify that readInput works
	struct input * curr = inputList;
	while(curr) {
		printf("Value stored: %s\n", curr->value);
		curr = curr->next;
	}
}
