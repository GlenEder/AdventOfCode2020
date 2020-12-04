#include <stdio.h>
#include "../utils/util.h"

/*
 * Day four's problem is to find valid passports.
 * A valid passport must have all eight fields 
 * present. A passport is all the lines of input
 * that are between two new lines. 
 * 
 */

struct passport {
 	char * byr;	//birth year
	char * iyr;	//issue year
	char * eyr;	//expiration year
	char * hgt;	//height 
	char * hcl;	//hair color
	char * ecl;	//eye color
	char * pid;	//passport id
	char * cid;	//country id
};

//goes through input list and creates passport 
void genPassports() {

}

void part1() {

}

int main(int argc, char *argv[]) {

	//check for args 
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}

	//read input 
	if( readInput(argv[1]) < 1 ) { return -1; };	//exit if error occurs reading input file
	
	part1();	//call part1 implementation 
	cleanup();	//clean up input list
}
