/*Title: Algorithm Efficiency and Sorting
*Author: Irem Seven
*ID: 21704269
*Section: 1
*/
#include <iostream>
#include <ctime>
#include "sorting.h"
#include <cmath>

using namespace std;

int main()
{

	int* arr1 = new int[16]{ 9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7 };
	int size = 16;
	int comparison = 0;
	int move = 0;
	
	insertionSort(arr1, size, comparison, move);
	displayArray(arr1, size);
	cout << "No of key comparison: " << comparison << endl;
	cout << "No of moves: " << move << endl;
	cout << "\n" << endl;

	int* arr2 = new int[16]{ 9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7 };
	comparison = 0;
	move = 0;
	quickSort(arr2, size, comparison, move);
	displayArray(arr2, size);
	cout << "No of key comparison: " << comparison << endl;
	cout << "No of moves: " << move << endl;
	cout << "\n" << endl;

	int* arr3 = new int[16]{ 9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7 };
	comparison = 0;
	move = 0;
	mergeSort(arr3, size, comparison, move);
	displayArray(arr3, size);
	cout << "No of key comparison: " << comparison << endl;
	cout << "No of moves: " << move << endl;
	cout << "\n" << endl;

	performanceAnalysis();

	return 0;

}


