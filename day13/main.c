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
 * Note: All bus stops are prime numbers
 *
 * Part 2 appears much harder as we need to 
 * find the time stamp at which all the buses 
 * appeared right after each other (with their 
 * respective offsets of course). They already 
 * told us that it would be an extremely large 
 * number. 
 *
 * This one was hard. Not hard to do, but hard 
 * to do quickly. The first time I attempted this
 * I only incremented by the looping of the first 
 * bus stop (In my case, 17). This was horribly 
 * slow. Then after looking around and thinking 
 * on it, I tried a method where I incremented by 
 * the highest matched bus stop as it would have the 
 * biggest impact on matching. This was considerbly 
 * faster than the previous method (roughly 33X
 * quicker). This however was still not enough, and 
 * my laptop was not happy with me at this point. 
 * So I checked AOC's reddit and saw lots of mentions 
 * of the Chinese Remainder Theroem. How this was 
 * implemented in this was by understanding that 
 * once the next stop was matched, the next time this
 * matching would happen would be the addition of their 
 * product added to the current timestamp. So once our 
 * 17 is matched with 37, the new increment will be
 * 629. Then on the next match (my case 571), the 
 * new increment is now 359159. As you can see 
 * this makes the process speed up extremely fast. 
 * This only works because the bus stops are all 
 * prime numbers, as noted above.   
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
	int id;				//bus stops id, also how often it comes by
	int minAfter;			//offset for timestamp from previous bus in list
	struct BusStop * next;		//pointer to next bus stop
};

struct BusStop * firstStop = NULL;	//head of bus stop list


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

	char * token;							//pointer to future tokens 
	int timeBetweenStop = 1;					//starting time between stops
	while((token = strsep(&inputList->next->value, ","))) {		//loop through and tokenize the input 
		if(*token == 'x') {					
			timeBetweenStop++;						//increment offset for stop
		}
		else {
			int bus = atoi(token);						//get bus id
			struct BusStop * newStop = malloc(sizeof(struct BusStop));	//create memory for bus stop
			newStop->id = bus;						//set id for bus
			newStop->minAfter = timeBetweenStop;				//set offset for busstop
			newStop->next = NULL;						//init next to NULL

			timeBetweenStop = 1;						//reset offset counter 
			if(firstStop == NULL) {		
				firstStop = newStop;					//set first stop for list
				firstStop->minAfter = 0;				//set first stops offset 
			}
			else {
				struct BusStop * currStop = firstStop;			//get pointer to first bus stop
				while(currStop->next) {					//get to end of bus stop list
					currStop = currStop->next;			
				}	
				currStop->next = newStop;				//add new bus stop to end of list
			}
		}
	}

	
	//printBuses(firstStop);							//print buses for debugging			
 
	/* Get last bus stop id */
	struct BusStop * currStop = firstStop;						//bus stop interator 
	int numStops = 0;								//number of stops counter 
	while(currStop) {								//count number of stops we have
		currStop = currStop->next;
		numStops++;
	}
	unsigned long timestamp = firstStop->id;					//inital timestamp to check 
	unsigned long increment = firstStop->id;					//inital increment for timestamp
	int numStopsConnected = 1;							//tracker of number of stops connected 
	while(numStopsConnected != numStops) {						//loop until all stops are connceted 

		printf("\rChecking timestamp: %lu", timestamp);				//print over itself to show its running  		
		int numConnected = areConnected(timestamp, firstStop, 0);		//call recursive method  
		if(numConnected > numStopsConnected) {					//see if we connected more stops
	
			currStop = firstStop;						//move stop pointer back to beginnning 
			for(int i = 0; i < numConnected; i++) {				//go to all stops that are connected 
						
				if(i >= numStopsConnected) {				
					increment *= currStop->id;			//if new stop connected, product in its stop id
				}
								
				currStop = currStop->next;				//go to next bus stop
			}
	
			numStopsConnected = numConnected;				//update number of buses connected 
		}
					
		timestamp += increment;							//increment timestamp 
	}

	printf("\nResult %lu\n", timestamp - increment);				//print result (adjust for extra timestamp addition)
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
