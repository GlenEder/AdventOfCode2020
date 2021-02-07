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
//current dimension (set based on input)
int gridDimension = 0;



void part1() {

	//Set grid dimension based on input
	gridDimension = strlength(inputList->value) - 1;

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
