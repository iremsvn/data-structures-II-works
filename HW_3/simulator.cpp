
#include <iostream>
#include "maxHeap1.h"
//#include "maxHeap2.h" //only one header can be included since both maxHeaps have same class name
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
	
	hospital.parseText(fileName, maxAvg); //that function calls simulation funtion
}

