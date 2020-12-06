#include <stdio.h>
#include <math.h>
#include "../utils/util.h"

/*
 * Today's challenge is about checking answers 
 * each group has answered yes to. Part 1 has 
 * us calculate the sum of all the questions 
 * each member in the group answered yes to. 
 * 
 * Note that the input is all lower case
 */

struct input * input = NULL;		//global input list pointer 

//Finds the number of questions that every member in the group said yes to
//@param input -- starting line of groups input 
//
//@return number of questions answered yes by group
int getNumGroupYes() {
	
	if(input == NULL) { return -1; } 	//signal done with input list	

	int total = 0;				//number of questions everyone in group answered yes 
	int groupQ = 0;				//bit wise value to keep track of groups questions 
	
	//loop through groups 
	while(input && *(input->value) != '\n') {
		
		int l = strlength(input->value);		//get length of input 
		int used[26] = {0};				//keep track of questions answered 		
		int answer = 0;					//int to AND with groupQ 
		for(int i = 0; i < l; i++) {
			char c = *(input->value + i);		//get char at position 
			int pos = c - 'a';			//get position of char in array
			
			//ensure we haven't already seen this value before 
			if(used[pos] == 0) {
				int toAdd = pow(2, pos);	//get spot that it takes 
				answer += toAdd;		//set spot to 1
				used[pos] = 1;			//set flag to not repeat this value 
			}
		}

		groupQ = groupQ | answer;			//preform OR operation to keep values everyone has answered 
		input = input->next;				//go to next input node
	} 

	//go to next node for next call of this method
	if(input) input = input->next;	

	//calc total questions answered by all
	while(groupQ) {
		if(groupQ & 1) { total++; }			//check if 1 in binary position 
		groupQ >>= 1;					//shift bits right 
	}

	return total;
}

void part1() {

	int sum = 0;				//sum of all group answered questions
	int groupsVal = 0;			//number of questions to add to sum 
	input = inputList;			//set input global to front of input list
	while((groupsVal = getNumGroupYes()) >= 0) {
		printf("Groups Value: %d\n", groupsVal);
		sum += groupsVal;	
	}
	
	printf("Sum: %d\n", sum);
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
