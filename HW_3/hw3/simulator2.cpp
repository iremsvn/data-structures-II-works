
#include <iostream>
#include "maxHeap2.h"
#include <stdio.h>
#include <stdlib.h>


using namespace std;

int main(int argc, char *argv[])
{
	char* input_fileName = argv[1];
	char* input_constraint = argv[2];
	string fileName;
	int maxAvg;

	if (input_fileName == NULL) {
		cin >> fileName >> maxAvg;
	}
	else {
		fileName = string(input_fileName);
		maxAvg = atoi(input_constraint);
	}
	Heap hospital;
	
	hospital.parseText(fileName, maxAvg);
}

