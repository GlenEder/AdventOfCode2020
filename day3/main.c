#include <stdio.h>
#include "../utils/util.h"


int main(int argc, char *argv[]) {

	//check program params
	if(argc != 2) {
		printf("Ussage: <program> <input file>\n");
		return -1;
	}

	//handle reading input 
	readInput(argv[1]);


}
