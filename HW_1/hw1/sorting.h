/*Title: Algorithm Efficiency and Sorting
*Author: Irem Seven
*ID: 21704269
*Section: 1
*/
#ifndef __SORTING_H
#define __SORTING_H

#include <ctime>
#include <cmath>
#include <time.h>  
#include <stdlib.h>  

	void insertionSort(int* arr, int size, int& compCount, int& moveCount);
	void quickSort(int* arr, int size, int& compCount, int& moveCount);
	void mergeSort(int* arr, int size, int& compCount, int& moveCount);
	void quicksort(int theArray[], int first, int last, int& compCount, int& moveCount);
	void partition(int theArray[], int first, int last, int& pivotIndex, int& compCount, int& moveCount);
	void mergesort(int theArray[], int first, int last, int& compCount, int& moveCount);
	void merge(int theArray[], int first, int mid, int last, int& compCount, int& moveCount);
	void displayArray(int* arr, int len);
	void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, int N);
	void createAlreadySortedArrays(int*& arr1, int*& arr2, int*& arr3, int N);
	void performanceAnalysis();

#endif
