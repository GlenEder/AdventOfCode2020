#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * Day 11 is musical chairs; well not really. 
 * We are to find the number of empty seats 
 * after the given rules result in no change 
 * of seating arragement. 
 */

#define FLOOR '.'
#define FREE 'L'
#define TAKEN '#'

//Prints the map provided 
//@param map -- map to be printed
void printMap(char * map, int od, int id) {

	printf("===Printing Map===\n");
	for(int i = 0; i < od; i++) {
		for(int j = 0; j < id; j++) {
			printf("%c", map[i * id + j]);
		}
		printf("\n");
	}

}

void part1() {

	int WIDTH  = strlength(inputList->value);	//get width of grid
	int HEIGHT = 0;					//height of grid
	struct input * curr = inputList;		//pointer to beginning of input list
	while(curr) { HEIGHT++; curr = curr->next; }	//find height of grid

	//initalize map	
	char map[HEIGHT * WIDTH];			//map array
	int y = 0;					//current y level
	curr = inputList;				//reset pointer to first input 
	while(curr) {
		for(int i = 0; i < WIDTH; i++) {
			char c = *(curr->value + i);	//get char at position
			map[y * WIDTH + i] = c;		//set map
		}
		y++;					//increment y level
		curr = curr->next;			//go to next counter
	}

	printMap(map, HEIGHT, WIDTH);			//print map

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
