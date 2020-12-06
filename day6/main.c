#include <stdio.h>
#include "../utils/util.h"

/*
 * Today's challenge is about checking answers 
 * each group has answered yes to. Part 1 has 
 * us calculate the sum of all the questions 
 * each member in the group answered yes to. 
 */


//Finds the number of questions that every member in the group said yes to
//@param input -- starting line of groups input 
//
//@return number of questions answered yes by group
int getNumGroupYes(struct input * input) {

	int questions[26];			//array to keep track of what questions have been answered
 
	//loop through groups 
	while(input && *(input->value) != '\n') {
		
					
		input = input->next;		//go to next input node 
	} 

}

void part1() {

	int sum = 0;				//sum of all group answered questions
	struct input * curr = inputList;	//get pointer to first input node
	

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
