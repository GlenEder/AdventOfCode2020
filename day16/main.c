#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/util.h"

/*
 * For day 16 we are at first checking for
 * invalid numbers on our tickets. The ranges
 * for valid inputs are contained in the first
 * segment of the input file. Ignoring our
 * ticket, we are to find the sum of of all
 * the invalid numbers in the tickets.
 */


//Checks if the number is within a range
//@param number -- value to check
//@param firstRange -- first range node in ranges list
//
//@return TRUE if valid, FALSE otherwise
int isValidNumber(int number, struct node * firstRange) {

	while(firstRange) {
		if(number >= *(int *)firstRange->key && number <= *(int *)firstRange->value)
			return TRUE;
		firstRange = firstRange->next;
	}

	return FALSE;
}


//Adds range to ranges list given the input string
//@param inputSegment -- string to find range in
//@param firstRange -- pointer to head of range list
//
//@return pointer to head of updated range list
struct node * addRange(char * inputSegment, struct node * firstRange) {

	int fNumIndex = indexOfNumber(inputSegment, 0);							//get index of first number in string
	int fDiv = indexOfChar(inputSegment, '-', fNumIndex);					//get index of first '-'
	char * fNumString = positionsSubstring(inputSegment, fNumIndex, fDiv);	//get substring of lower value
	int firstLower = atoi(fNumString);										//int rep of substring value
	free(fNumString);														//free substring memory

	int sNumIndex = indexOfNumber(inputSegment, fDiv);						//get index of second number
	int sEnd = indexOfChar(inputSegment, ' ', sNumIndex);					//get index of space
	if(sEnd < 0) {
		sEnd = strlength(inputSegment);										//if no space, get index of end of string
	}

	char * sNumString = positionsSubstring(inputSegment, sNumIndex, sEnd);	//get second number substring
	int secLower = atoi(sNumString);										//convert to int
	free(sNumString);														//free substring memory

	/* Add range to ranges list */
	if(firstRange) {
		addNewKeyedNode(firstRange, &firstLower, &secLower, sizeof(int), sizeof(int));
	}
		/* Create first range node */
	else {
		/* Make key the lower value of the range, and the value the upper value of the range */
		firstRange = createKeyedList(&firstLower, &secLower, sizeof(int), sizeof(int));
	}

	return firstRange;
}

//Checks the number provided against the rule number listed
//@param number -- the number to check
//@param ruleNumber -- the rule number to check against
//@param firstRange -- first node in ranges list
//
//@return 1 if number is in rule ranges, 0 otherwise
int passesRule(int number, int ruleNumber, struct node * firstRange) {

    //tracker for ranges
    int currRange = 0;
    //go through ranges till rule number is hit
    while(currRange != (ruleNumber * 2) && firstRange) {
        firstRange = firstRange->next;
        currRange++;
    }

    //check number against ranges
    if(number >= *(int *)firstRange->key && number <= *(int *)firstRange->value) return TRUE;
    //go to second range
    firstRange = firstRange->next;
    if(number >= *(int *)firstRange->key && number <= *(int *)firstRange->value) return TRUE;

    //number not in rule range
    return FALSE;
}

//Returns the number at the designated column in provided ticket
//@param str -- pointer to ticket string
//@param column -- column in string to find number of
//
//@return value of number in tickets column, if column is out of range; -1 is returned
int getTicketsColumnValue(char * str, int column) {
    char * token = strtok(str, ",");
    int currCol = 0;
    while(token) {
        if(currCol == column) {
            return atoi(token);
        }
        //increment column counter and go to next token
        currCol++;
        token = strtok(NULL, ",");
    }

    //column out of range of string
    return -1;
}

void part1() {

	struct input * curr = inputList;
	struct node * firstRange = NULL;

	/* get ranges from input file */
	while(strcompare(curr->value, "\n")) {
		firstRange = addRange(curr->value, firstRange);												//add first range
		int backIndex = indexOfChar(curr->value, 'o', indexOfNumber(curr->value, 0));				//get index of o in or
		char * secondRange = positionsSubstring(curr->value, backIndex, strlength(curr->value));	//get substring of second range
		firstRange = addRange(secondRange, firstRange);												//add second range to list
		curr = curr->next;																			//go to next input node
	}

	//print list for debugging
//	struct node * currRange = firstRange;
//	while(currRange) {
//		printf("Range: %d - %d\n", *(int *)currRange->key, *(int *)currRange->value);
//		currRange = currRange->next;
//	}


	/* Get to nearby tickets to check */
	while(*curr->value != 'n') { curr = curr->next; }			//skip to line 'nearby tickets'
	curr = curr->next;											//to to next to start checking the first ticket

	/* loop through tickets and check for bad values */
	int sumOfBadNums = 0;
	while(curr) {
        //printf("checking ticket: %s\n", curr->value);
        //create copy of vale to token on
        char * copy = copyString(curr->value);
		char * token = strtok(copy, ",");
		while(token) {
			int number = atoi(token);
			if(!isValidNumber(number, firstRange)) { sumOfBadNums += number; }
			token = strtok(NULL, ",");
		}
        free(copy);
		curr = curr->next;
	}
    green();
	printf("Sum of bad values: %d\n", sumOfBadNums);
    reset();
	deleteList(firstRange);																			//free list memory
}

void part2() {

    struct input * curr = inputList;
    struct node * firstRange = NULL;

    //printInput();

    int numRules = 0;           //number of rules being checked

    /* get ranges from input file */
    while(strcompare(curr->value, "\n")) {



        firstRange = addRange(curr->value, firstRange);												//add first range
        int backIndex = indexOfChar(curr->value, 'o', indexOfNumber(curr->value, 0));				//get index of o in or
        char * secondRange = positionsSubstring(curr->value, backIndex, strlength(curr->value));	//get substring of second range
        firstRange = addRange(secondRange, firstRange);												//add second range to list
        numRules++;                                                                                 //increment number of rules being tracked
        curr = curr->next;																			//go to next input node
    }

    /* Get to nearby tickets to check */
    char * myTicket = NULL;
    while(*curr->value != 'n') {
        if(*curr->value == 'y') {
            myTicket = copyString((char *)curr->next->value);
        }
        curr = curr->next;
    }
    curr = curr->next;											//to to next to start checking the first ticket


    struct node * validTickets = NULL;          // create list of valid tickets to check rules on

    /* loop through tickets and check for bad values */
    while(curr) {
        //create copy to token on
        char * copy = copyString(curr->value);
        char * token = strtok(copy, ",");
        int valid = 1;
        while(token) {
            int number = atoi(token);
            if(!isValidNumber(number, firstRange)) { valid = 0; break; }
            token = strtok(NULL, ",");
        }
        free(copy);
        // if valid ticket add to list
        if (valid) {
            if (validTickets == NULL) {
                validTickets = createList(curr->value, strlength(curr->value));
            }
            else {
                addNewNode(validTickets, curr->value, strlength(curr->value));
            }
        }
        curr = curr->next;
    }

    //validTickets is now filled with all the valid tickets
//    printf("Number of valid tickets: %d\n", lengthOfList(validTickets));

    //list of known rules, once filled out completely we are done here
    struct node * knownRules = NULL;
    //number of defined rules (essentially number of non-zero entries in definedRules)
    int rulesFound = 0;
    //int of rules that work for the current ticket column (uses bits as flags)
    int ticketColumnRules = 0;
    //column that is currently being worked on
    int columnToCheck = 0;
    //rule to check current column against
    int ruleToCheck = 0;
    //rule string for debugging
    char ruleList[33];

    //keep iterating until all rules found
    while(rulesFound != numRules) {
//        printf("\rChecking rule: %d", ruleToCheck);
//        printf("Checking rule: %d\n", ruleToCheck);
        //check that rule hasn't already been defined
        struct node * foundRules = knownRules;
        int ruleAlreadyFound = 0;
        while(foundRules) {
            if(*(int *)foundRules->key == ruleToCheck) {
                ruleAlreadyFound = 1;
                break;
            }
            foundRules = foundRules->next;
        }

        //skip to next rule check if already defined
        if(ruleAlreadyFound) {
            ruleToCheck++;
            ruleToCheck %= numRules;
            continue;
        }



        while(columnToCheck < numRules) {
//            printf("\tchecking column %d\n", columnToCheck);
            //get pointer to first valid ticket
            struct node * firstValid = validTickets;
            //rule passed flag
            int rulePassed = 1;
            //loop through all tickets to check current column
            while(firstValid) {
                //get copy of value
                char * copy = copyString((char *)firstValid->value);

                //get number in current column
                int ticketNumber = getTicketsColumnValue(copy, columnToCheck);
                if(ticketNumber < 0) {
                    red();
//                    printf("Error getting ticket number -- line: %s, copy: %s, col: %d\n", (char *)firstValid->value, copy, columnToCheck);
                    reset();
                    return;
                }
//                printf("\t\tChecking number %d...\t", ticketNumber);
                //check number against rule
                if(!passesRule(ticketNumber, ruleToCheck, firstRange)) {
//                    red();
//                    printf("Rule Failed\n");
//                    reset();
                    rulePassed = 0;
                    break;
                }
                else {
//                    green();
//                    printf("Rule Passed\n");
//                    reset();
                }
                //go to next ticket
                firstValid = firstValid->next;
                free(copy);
                if(!rulePassed) break;
            }

            if(rulePassed) {
                //set flag in column rules to keep track of what rules the column passes
                ticketColumnRules = setBit(ticketColumnRules, columnToCheck);
                setBinaryString(ruleList, ticketColumnRules);
                //printf("\tRule found for column %d\tRule List: %s\n", columnToCheck, ruleList);
            }

            //set column counter to next column
            columnToCheck++;
        }

        //clear know rules from rule list
        struct node * rules = knownRules;
        while(rules) {
            //printf("\tClearing rule %d from %s\n", *(int *)rules->key, ruleList);
            ticketColumnRules = clearBit(ticketColumnRules, *(int *)rules->value);
            setBinaryString(ruleList, ticketColumnRules);
            //printf("\t\tClearing complete: %s\n", ruleList);
            rules = rules->next;
        }

        //check number of rules in rule list
        int numPassed = countSetBits(ticketColumnRules);
        //printf("\tNumber of rules passed after clearing: %d\n", countSetBits(ticketColumnRules));

        //check if only one rule passed remains
        if(numPassed == 1) {
            //get column of rule
            int col = getFirstBitPos(ticketColumnRules);
            green();
//            printf("\nSetting Rule %d to Column %d\n", ruleToCheck, col);
            reset();
            //add rule to known rule list
            if(knownRules) {
                addNewKeyedNode(knownRules, &ruleToCheck, &col, sizeof(int), sizeof(int));
            }
            else {
                knownRules = createKeyedList(&ruleToCheck, &col, sizeof(int), sizeof(int));
            }

            //increment known rule counter
            rulesFound++;
        }

        //reset counters
        ticketColumnRules = 0;
        columnToCheck = 0;
        ruleToCheck++;
        ruleToCheck %= numRules;
    }

    //print rule list
//    green();
//    printf("\n---Rule List---\n");
//    reset();
    struct node * rules = knownRules;

    double answer = 1;
    while(rules) {
//        printf("Rule: %d \tColumn: %d\n", *(int *)rules->key, *(int *)rules->value);
        if(*(int *)rules->key < 6) {
            // creat copy of my ticket
            char * copy = copyString(myTicket);
            //get number in current column
            int ticketNumber = getTicketsColumnValue(copy, *(int *)rules->value);
            answer *= ticketNumber;
            free(copy);
        }
        rules = rules->next;
    }

    green();
    printf("Product of ticket columns: %lf\n", answer);
    reset();

    //cleanup
    deleteList(knownRules);
    deleteList(validTickets);
    deleteList(firstRange);
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
