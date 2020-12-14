#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * It's time to catch the bus in day 13.
 * The first line in the input is the  
 * amount of time we need to wait before
 * we can get on a bus. The numbers on 
 * the second line are the intervals at 
 * which the buses come, all starting at 0. 
 * Our goal is to find the bus we have to  
 * wait the least amount of time on.  
 */

void part1() {
	
	int ourWaitTime = atoi(inputList->value);	//get time that we need to wait 
	int idealBusID = 0;				//id of bus that works best for us
	int timeWaitingOnBus = ourWaitTime;		//time waiting on bus
	
	char * token;
	while((token = strsep(&inputList->next->value, ","))) {
		if(*token == 'x') continue;
		int bus = atoi(token);
		int timeWaiting = bus - ourWaitTime % bus;
		
		printf("Time to wait on Bus %d: %d\n", bus, timeWaiting); 

		if(timeWaiting < timeWaitingOnBus) {
			idealBusID = bus;
			timeWaitingOnBus = timeWaiting;
		}
		
	}

	printf("Puzzle Key: %d\n", idealBusID * timeWaitingOnBus);

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
