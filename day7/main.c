#include <stdio.h>
#include "../utils/util.h"

/*
 * Part1 for day 7 has us back checking. We
 * must find how many bags our bag can go in
 * using the rules for bags. These rules are 
 * the input. 
 *
 * Note every line follows the pattern:
 * 	<name of bag> contain <number> <another bag name>, <number> <another bag name>, ...
 * 
 */

//linked list node that holds name of bag that can directly/or indirectly hold our bag
struct shinyBag {
	char * name;			//name of bag that can hold our shiny gold bag
	struct shinuBag * next;		//next bag that can hold our shingy bag
};


void part1() {

	

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
