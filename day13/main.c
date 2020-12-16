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
 *
 * Part 2 appears much harder as we need to 
 * find the time stamp at which all the buses 
 * appeared right after each other (with their 
 * respective offsets of course). They already 
 * told us that it would be an extremely large 
 * number. 
 *  
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
		
		//printf("Time to wait on Bus %d: %d\n", bus, timeWaiting); 

		if(timeWaiting < timeWaitingOnBus) {
			idealBusID = bus;
			timeWaitingOnBus = timeWaiting;
		}
		
	}

	printf("Puzzle Key: %d\n", idealBusID * timeWaitingOnBus);

}


struct BusStop {
	int id;
	int minAfter;	
	struct BusStop * next;
};

struct BusStop * firstStop = NULL;


//Recusive function to see if the stops in the list are following each other
//@param timestamp -- current timestamp to check against
//@param stop -- pointer to stop to check 
//@param numConnected -- number of connected stops to this timestamp
//
//@return the number of connected bus stops at the timestamp 
int areConnected(unsigned long timestamp, struct BusStop * stop, int numConnected) {

	//base case, if null end of list 
	if(stop == NULL) return numConnected;
	
	//printf("Checking stop: %d, against timestamp: %lu + %d = %lu\n", stop->id, timestamp, stop->minAfter, (timestamp + stop->minAfter) % stop->id); 	
	if((timestamp + stop->minAfter) % stop->id == 0) {
			
		//recusive call to check next stop with adjusted timestamp for offset 
		return areConnected(timestamp + stop->minAfter, stop->next, numConnected + 1);
	} 

	//return number of currently connceted buses
	return numConnected;
}

//Method to print bus data
//@param bus -- pointer to start of bus list
void printBuses(struct BusStop * bus) {
	
	printf("===Bus Stops===\n");
	while(bus) {
		printf("\tBus %d, minAfter: %d\n", bus->id, bus->minAfter);
		bus = bus->next;
	}

}

void part2() {

	char * token;
	int timeBetweenStop = 1;
	while((token = strsep(&inputList->next->value, ","))) {
		if(*token == 'x') {
			timeBetweenStop++;
		}
		else {
			int bus = atoi(token);
			struct BusStop * newStop = malloc(sizeof(struct BusStop));
			newStop->id = bus;
			newStop->minAfter = timeBetweenStop;
			newStop->next = NULL;

			timeBetweenStop = 1;
			if(firstStop == NULL) {
				firstStop = newStop;
				firstStop->minAfter = 0;
			}
			else {
				struct BusStop * currStop = firstStop;
				while(currStop->next) {
					currStop = currStop->next;
				}	
				currStop->next = newStop;
			}
		}
	}

	
	printBuses(firstStop);
 
	/* Get last bus stop id */
	struct BusStop * currStop = firstStop;
	int numStops = 0;
	while(currStop) {
		currStop = currStop->next;
		numStops++;
	}
	unsigned long timestamp = firstStop->id;
	unsigned long increment = firstStop->id;
	int numStopsConnected = 1;
	while(numStopsConnected != numStops) {

		printf("\rChecking timestamp: %lu", timestamp); 
		int numConnected = areConnected(timestamp, firstStop, 0);
		if(numConnected > numStopsConnected) {
	
			currStop = firstStop;
			for(int i = 0; i < numConnected; i++) {
						
				if(i >= numStopsConnected) {
					increment *= currStop->id;
				}
								
				currStop = currStop->next;
			}
	
			numStopsConnected = numConnected;
		}
				
		
		//printf("Checking timestamp: %lu, numMatched: %d, newIncement: %lu\n", timestamp, numConnected, increment); 
	
		timestamp += increment;	
	}


	printf("\nResult %lu\n", timestamp - increment);

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
	cleanup();
	//reset input list because of strsep 
	readInput(argv[1]);
	part2();	

	//free memory in input list
	//cleanup();
}
