/*Title: Algorithm Efficiency and Sorting
*Author: Irem Seven
*ID: 21704269
*Section: 1
*/

#include <iostream>
#include <cstddef>
#include <ctime>
#include <cmath>
#include "sorting.h"
using namespace std;

void insertionSort(int* arr, int size, int& compCount, int& moveCount) 
{
	for (int unsorted = 1; unsorted < size; ++unsorted) {

		int nextItem = arr[unsorted];
		int loc = unsorted;

		compCount++;
		for (; (loc > 0) && (arr[loc - 1] > nextItem); --loc)
		{
			arr[loc] = arr[loc - 1];
			compCount++;
			moveCount++;
		}

		arr[loc] = nextItem;
		moveCount+= 2;
	}
}

/////////////////////////////////////////////////////////

void quickSort(int* arr, int size, int& compCount, int& moveCount)
{
	quicksort(arr, 0, size - 1, compCount, moveCount);
}

void quicksort(int theArray[], int first, int last, int& compCount, int& moveCount) {
	// Precondition: theArray[first..last] is an array.
	// Postcondition: theArray[first..last] is sorted.

	int pivotIndex;

	if (first < last) {

		// create the partition: S1, pivot, S2
		partition(theArray, first, last, pivotIndex, compCount, moveCount);

		// sort regions S1 and S2
		quicksort(theArray, first, pivotIndex - 1, compCount, moveCount);
		quicksort(theArray, pivotIndex + 1, last, compCount, moveCount);
	}
}


void partition(int theArray[], int first, int last, int& pivotIndex, int& compCount, int& moveCount) {

	// Precondition: theArray[first..last] is an array; first <= last.
	// Postcondition: Partitions theArray[first..last] such that:
	//   S1 = theArray[first..pivotIndex-1] < pivot
	//   theArray[pivotIndex] == pivot
	//   S2 = theArray[pivotIndex+1..last] >= pivot

	 // place pivot in theArray[first]

	int pivot = theArray[first]; // copy pivot
	moveCount++;

	// initially, everything but pivot is in unknown
	int lastS1 = first;           // index of last item in S1
	int firstUnknown = first + 1; // index of first item in unknown

	 // move one item at a time until unknown region is empty
	for (; firstUnknown <= last; ++firstUnknown) {
		// Invariant: theArray[first+1..lastS1] < pivot
		//            theArray[lastS1+1..firstUnknown-1] >= pivot

		// move item from unknown to proper region

		compCount++; //increment no of key comparisons
		if (theArray[firstUnknown] < pivot) {  	// belongs to S1
			++lastS1;

			int temp = theArray[firstUnknown];
			theArray[firstUnknown] = theArray[lastS1];
			theArray[lastS1] = temp;

			moveCount = moveCount + 3; //3 data moves
		}	// else belongs to S2
	}
	// place pivot in proper position and mark its location

	int temp1 = theArray[first];
	theArray[first] = theArray[lastS1];
	theArray[lastS1] = temp1;
	moveCount = moveCount + 3; //3 data moves

	pivotIndex = lastS1;
}

//////////////////////////////////////////////////////

void mergeSort(int* arr, int size, int& compCount, int& moveCount)
{
	mergesort(arr, 0, size - 1, compCount, moveCount);
}

void mergesort(int theArray[], int first, int last, int& compCount, int& moveCount) {

	if (first < last) {

		int mid = (first + last) / 2; 	// index of midpoint

		mergesort(theArray, first, mid, compCount, moveCount);

		mergesort(theArray, mid + 1, last, compCount, moveCount);

		// merge the two halves
		merge(theArray, first, mid, last, compCount, moveCount);
	}
}


void merge(int theArray[], int first, int mid, int last, int& compCount, int& moveCount)
{ 

	int first1 = first; 	// beginning of first subarray
	int last1 = mid; 		// end of first subarray
	int first2 = mid + 1;	// beginning of second subarray
	int last2 = last;		// end of second subarray
	int index = first1; // next available location in tempArray

	int* tempArray = new int[last + 1]{ 0 }; // temporary array,
											//allocated dynamically to change size in run time

	for (; (first1 <= last1) && (first2 <= last2); ++index) {

		compCount++; //increment 1 for key comparison
		if (theArray[first1] < theArray[first2]) {
			tempArray[index] = theArray[first1];
			++first1;
		}
		else {
			tempArray[index] = theArray[first2];
			++first2;
		}
		moveCount++; //increment 1 for 1 data move
	}

	// finish off the first subarray, if necessary
	for (; first1 <= last1; ++first1, index++)
	{
		tempArray[index] = theArray[first1];
		moveCount++;
	}

	// finish off the second subarray, if necessary
	for (; first2 <= last2; ++first2, ++index)
	{
		tempArray[index] = theArray[first2];
		moveCount++;
	}
		
	// copy the result back into the original array
	for (index = first; index <= last; ++index)
	{
		theArray[index] = tempArray[index];
		moveCount++;
	}

	delete [] tempArray;

}  // end merge

///////////////////////////////////////////////////

void displayArray(int* arr, int len) {
	for (int i = 0; i < len; i++)
		cout << arr[i] << "\t";
	cout << endl;
}

///////////////////////////////////////////////////

void performanceAnalysis()
{
	int* arr1, *arr2, *arr3;
	int compI[6], moveI[6];
	int compM[6], moveM[6];
	int compQ[6], moveQ[6];
	double timeElapsedI[6];
	double timeElapsedM[6];
	double timeElapsedQ[6];
	clock_t counter;
	int type = 0;
	while (type < 2)
	{ 
		int size = 5000;
		int j = 0;
		for (; size <= 30000; size += 5000)
		{
			compI[j] = 0;
			moveI[j] = 0;
			timeElapsedI[j] = 0;
			compM[j] = 0;
			moveM[j] = 0;
			timeElapsedM[j] = 0;
			compQ[j] = 0;
			moveQ[j] = 0;
			timeElapsedQ[j] = 0;
			if (type == 0)
			createRandomArrays(arr1, arr2, arr3, size);
			else
			createAlreadySortedArrays(arr1, arr2, arr3, size);

			counter = clock();
			insertionSort(arr1, size, compI[j], moveI[j]);
			counter = clock() - counter;
			timeElapsedI[j] = (double)counter * 1000 / CLOCKS_PER_SEC;

			counter = clock();
			mergeSort(arr2, size, compM[j], moveM[j]);
			counter = clock() - counter;
			timeElapsedM[j] = (double)counter * 1000 / CLOCKS_PER_SEC;

			if (type == 0)
			{
				counter = clock();
				quickSort(arr3, size, compQ[j], moveQ[j]);
				counter = clock() - counter;
				timeElapsedQ[j] = (double)counter * 1000 / CLOCKS_PER_SEC;
			}

			delete[] arr1;
			delete[] arr2;
			delete[] arr3;

			j++;
		}
	
		for (int sortNumber = 0; sortNumber < 3; sortNumber++)
		{
			cout << "------------------------------------------" << endl;
			size = 5000;
			if (sortNumber == 0)
			{
				cout << "Part c - Time Analysis of Insertion Sort" << endl;
				cout << "Array Size" << "\t\t" << "Time Elapsed" << "\t\t" << "compCount" << "\t\t" << "moveCount" << endl;
				for (int j = 0; j < 6; j++)
				{
					cout << size << "\t\t\t" << timeElapsedI[j] << " ms\t\t\t" << compI[j] << "\t\t" << moveI[j] << endl;
					size += 5000;
				}
			}
			else if (sortNumber == 1)
			{
				cout << "Part c - Time Analysis of Merge Sort" << endl;
				cout << "Array Size" << "\t\t" << "Time Elapsed" << "\t\t" << "compCount" << "\t\t" << "moveCount" << endl;
				for (int j = 0; j < 6; j++)
				{
					cout << size << "\t\t\t" << timeElapsedM[j] << " ms\t\t\t" << compM[j] << "\t\t\t" << moveM[j] << endl;
					size += 5000;
				}
			}
			else
			{
				cout << "Part c - Time Analysis of Quick Sort" << endl;
				if (type == 0)
				{
					cout << "Array Size" << "\t\t" << "Time Elapsed" << "\t\t" << "compCount" << "\t\t" << "moveCount" << endl;
					for (int j = 0; j < 6; j++)
					{
						cout << size << "\t\t\t" << timeElapsedQ[j] << " ms\t\t\t" << compQ[j] << "\t\t\t" << moveQ[j] << endl;
						size += 5000;
					}
				}

				else
				{
					cout << "Due to high array sizes Stack Overflow achieved." << endl;
					cout << "Values could not be measured for Quick sort when sorted, Worst case." << endl;
				}		
			}
		}
		if (type == 0)
		{
			cout << "**************************" << endl;
			cout << "Using already sorted arrays:" << endl;
			cout << "**************************" << endl;
		}

		type++;
	}
}


////////////////////////////////////////////////

void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, int N) {
	if (N <= 0) {
		arr1 = arr2 = arr3 = NULL;
		return;
	}
	arr1 = new int[N];
	arr2 = new int[N];
	arr3 = new int[N];

	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		arr1[i] = rand() % (2 * N);
		arr2[i] = arr3[i] = arr1[i];
	}
}

////////////////////////////////////////////////////

void createAlreadySortedArrays(int*& arr1, int*& arr2, int*& arr3, int N) {
	if (N <= 0) {
		arr1 = arr2 = arr3 = NULL;
		return;
	}
	arr1 = new int[N];
	arr2 = new int[N];
	arr3 = new int[N];

	for (int i = 0; i < N; i++)
		arr1[i] = arr2[i] = arr3[i] = i;
}