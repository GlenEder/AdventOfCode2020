#include <stdio.h>
#include <stdlib.h>
#include "../utils/util.h"

/*
 * It's day 17 and after my long break
 * from this challenge I am back (I admit
 * that I tried to finish day 16 part 2
 * last night but that will be done another
 * day). Today's challenge has us simulate
 * six cycles of this boot cycle.
 */

//Total number of cycles to go through
const int totalCycles = 6;
//Current cycle tracker
int currentCycle = 0;
//current number of z layers
int numberOfLayers = 1;

void part1() {

	//list of grid items
	struct node * cords = NULL;

	//x and y trackers for creating cords
	int x = 0;
	int y = 0;

	//read input data in
	struct input * currInput = inputList;
	while(currInput) {

		//get first character in input line
		char * c = currInput->value;
		//loop till hit end of line
		while(*c) {
			if(*c == '\n') break;
			struct coordinate * cord = createCoordinate(x, y, 0);
			//set active value based on input
			int active = *c == '#' ? 1 : 0;
			//create grid item with coordinate and active value
			struct gridItem * item = createGridItem(cord, &active, sizeof(int));

			//add to cords list
			if(cords) {
				addNewNode(cords, item, sizeof(item));
			}
			//create first node in list
			else {
				cords = createList(item, sizeof(item));
			}

			//increase x
			x++;
			//go to next char
			c++;
		}
		//reset x value and increase y value
		x = 0;
		y++;

		//go to next input line
		currInput = currInput->next;
	}

	//print cords for debugging
	struct node * currCord = cords;
	while(currCord) {
		struct gridItem * currItem = (struct gridItem *)currCord->value;
		printf("%d -- ", *(int *)currItem->value);
		printCoordinate(currItem->coordinate);
		currCord = currCord->next;
	}


	//Preform boot up cycles
	while(currentCycle++ < totalCycles) {

		//check if odd cycle
		if(currentCycle % 2) {
			//odd cycle increases in z direction


		}
		else {
			//even cycle increases grid dimension

		}

	}

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
