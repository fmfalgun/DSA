/*
 Implement heap_sort(arr, n) — in-place: repeatedly swap root with the last element, 
 shrink the heap boundary by 1, sift-down. Print final sorted array.

 repeat (size-1) times:
    swap arr[1] with arr[last]
    shrink last by 1
    sift-down from root
 */

#include <stdio.h>
#include "heap.h"

void heapify(int arr[], int size){
	int n = (size-1)/2;
	int lvi; // largest value index
	for (int i = n; i > 0; i--){
		int lci = left_child_index(i);
		int rci = right_child_index(i);
		int ptr = i; 

		while(lci <= size){	
			if (rci > size) lvi = lci;
			else if (arr[lci] > arr[rci]) lvi = lci;
			else lvi = rci;
		
			if (arr[ptr] > arr[lvi]) break;
			int temp = arr[ptr];
			arr[ptr] = arr[lvi];
			arr[lvi] = temp;	
			ptr = lvi;

			lci = left_child_index(ptr);
			rci = right_child_index(ptr);
			//printf("iteration %i, and pointer (ptr) %i\n",i,ptr);
			//printer(arr,size);
		}
	}
}

void sift_down(int *arr, int size, int root_index){
	int ptr = root_index;
	int lci = left_child_index(ptr);
	int rci = right_child_index(ptr);

	while (lci <= size){
		int lvi;
		if (rci > size) lvi = lci;
		else if (arr[rci] < arr[lci]) lvi = lci;
		else lvi = rci;

		if (arr[ptr] < arr[lvi]){
			int temp = arr[lvi];
			arr[lvi] = arr[ptr];
			arr[ptr] = temp;
		}
		else break;

		ptr = lvi;
		lci = left_child_index(ptr);
		rci = right_child_index(ptr);
		//printf("pointer (ptr) %i and lci value = %i\n",ptr, lci);
		//printer(arr,size);
	}
	//printf("pointer (ptr) %i\n",ptr);
	//printer(arr,size);
}

void heap_sort(int *arr, int size){
	int n = size;
	while (n != 1){
		// swaping top index
		int temp = arr[n];
		arr[n] = arr[1];
		arr[1] = temp;
		

		// heapify with one less size coz at max index is highest value;
		n--;
		sift_down(arr, n, 1);
	}
}

void main (void){
	int arr[] = {0,4, 1, 9, 3, 7, 2, 6};
	int size = sizeof(arr)/sizeof(int);
	size--;
	printer(arr, size);
	heapify(arr, size);
	printer(arr, size);
	heap_sort(arr,size);
	printer(arr, size);	
}
