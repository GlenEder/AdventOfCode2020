#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * Day 11 is musical chairs; well not really. 
 * We are to find the number of empty seats 
 * after the given rules result in no change 
 * of seating arragement. 
 */

#define FLOOR 0
#define FREE 1
#define TAKEN 2

void part1() {

	int WIDTH  = strlength(inputList->value);	//get width of grid
	int HEIGHT = 0;					//height of grid
	struct input * curr = inputList;		//pointer to beginning of input list
	while(curr) { HEIGHT++; curr = curr->next; }	//find height of grid

	//initalize map	
	int map[WIDTH][HEIGHT];


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
