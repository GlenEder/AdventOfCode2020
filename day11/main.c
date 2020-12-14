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
//@param od -- outer dimension of (aka height)
//@param id -- inner dimension of grid (aka width)
void printMap(char * map, int od, int id) {

	printf("===Printing Map===\n");
	for(int i = 0; i < od; i++) {
		for(int j = 0; j < id; j++) {
			printf("%c", map[i * id + j]);
		}
		printf("\n");
	}

}

//Returns the number of taken tiles around 
//@param map -- pointer to map to check
//@param od -- outter dimension of map
//@param id -- inner dimension of map 
//@param x -- inner dimension value to check 
//@param y -- outter dimension value to check 
//
//@return the number of taken spots around position 
int numOccupiedAround(char * map, int od, int id, int x, int y) {

	int numAround = 0;							//number of taken chairs around counter
	for(int i = -1; i < 2; i++) {						//loop up and down 
		for(int j = -1; j < 2; j++) {					//loop left and right
		
			if(i == 0 && j == 0) continue;				//dont include current tile
						
			int yCheck = y + i;					//adjust y			
			int xCheck = x + j;					//adjust x
			if(yCheck < 0 || yCheck >= od) continue;		//check y bounds
			if(xCheck < 0 || xCheck >= id) continue;		//check x bounds

			//printf("Checking (%d,%d)\n", xCheck, yCheck);

			if(map[(y+i) * od + (x+j)] == TAKEN) {			
				numAround++;					//increment counter if taken 
			}
		}
	}

	//return number of taken tiles around
	return numAround;

}

//Applies updates to the map using the rules on AOC
//@param map -- pointer to map to update
//@param od -- height of map
//@param id -- width of map
//
//@return -- number of changes made
int updateMap(char * map, int od, int id) {

	char newMap[od * id];
	int numChanges = 0;

	for(int i = 0; i < od; i++) {
		for(int j = 0; j < id; j++) {
			int mapPos = i * od + j;
			int numAround = numOccupiedAround(map, od, id, j, i);
			if(numAround == 0 && map[mapPos] == FREE) {
				newMap[mapPos] = TAKEN;
				numChanges++;
			}	
			else if(numAround >= 4 && map[mapPos] == TAKEN) {
				newMap[mapPos] = FREE;
				numChanges++;
			}
			else {
				newMap[mapPos] = map[mapPos];
			}
		}
	}


	//set map to new map
	for(int i = 0; i < od; i++) {
		for(int j = 0; j < id; j++) {
			int mapPos = i * od + j;
			map[mapPos] = newMap[mapPos];
		}	
	}
	return numChanges;

}

//Counts the number of taken seats in the map 
//@param map -- pointer to map
//@param size -- size of map 
//
//@return number of taken seats in map 
int countTakenSeats(char * map, int size) {
	int numTaken = 0;
	for(int i = 0; i < size; i++) {
		if(map[i] == TAKEN) numTaken++;
	}
	return numTaken;
}

void part1() {

	int WIDTH  = strlength(inputList->value) - 1;	//get width of grid
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

	//printMap(map, HEIGHT, WIDTH);			//print inital map
	while(updateMap(map, HEIGHT, WIDTH))  {
		//printMap(map, HEIGHT, WIDTH);	
	}

	printf("Taken seats: %d\n", countTakenSeats(map, HEIGHT * WIDTH));
}


//Counts number of chairs around using part 2 rule set
//@param map -- pointer to map to check
//@param od -- outter dimension of map
//@param id -- inner dimension of map 
//@param x -- inner dimension value to check 
//@param y -- outter dimension value to check 
//
//@return the number of taken spots around position 
int numAroundV2(char * map, int od, int id, int x, int y) {
	
	//printf("\nChecking position (%d, %d)\n", x, y);

	int numAround = 0;
	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			if(i == 0 && j == 0) continue;				//dont include current tile
			int chairFound = 0;
			int dist = 1;
			while(!chairFound) {
						
				int yCheck = y + i * dist;				//adjust y			
				int xCheck = x + j * dist;				//adjust x
				if(yCheck < 0 || yCheck >= od) break;			//check y bounds
				if(xCheck < 0 || xCheck >= id) break;			//check x bounds

				int mapPos = yCheck * id + xCheck;
				if(map[mapPos] == TAKEN) {
					numAround++;
					chairFound++;
				}
				else if(map[mapPos] == FREE){ 
					chairFound++; 
				}
				dist++;
			}
		}
	}

	return numAround;
}

//Applies updates to the map using the rules on AOC
//@param map -- pointer to map to update
//@param od -- height of map
//@param id -- width of map
//
//@return -- number of changes made
int updateMapV2(char * map, int od, int id) {

	char newMap[od * id];
	int numChanges = 0;

	for(int i = 0; i < od; i++) {
		for(int j = 0; j < id; j++) {
			int mapPos = i * od + j;
			int numAround = numAroundV2(map, od, id, j, i);
			if(numAround == 0 && map[mapPos] == FREE) {
				newMap[mapPos] = TAKEN;
				numChanges++;
			}	
			else if(numAround >= 5 && map[mapPos] == TAKEN) {
				newMap[mapPos] = FREE;
				numChanges++;
			}
			else {
				newMap[mapPos] = map[mapPos];
			}
		}
	}


	//set map to new map
	for(int i = 0; i < od; i++) {
		for(int j = 0; j < id; j++) {
			int mapPos = i * od + j;
			map[mapPos] = newMap[mapPos];
		}	
	}
	//printf("Num changes: %d\n", numChanges);
	return numChanges;

}

void part2() {

	int WIDTH  = strlength(inputList->value) - 1;	//get width of grid
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

	//printMap(map, HEIGHT, WIDTH);			//print inital map
	while(updateMapV2(map, HEIGHT, WIDTH))  {
		//printMap(map, HEIGHT, WIDTH);
	}

	printf("Taken seats V2: %d\n", countTakenSeats(map, HEIGHT * WIDTH));
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
