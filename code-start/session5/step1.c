/*
Build-heap conceptually — given unsorted array [4, 1, 9, 3, 7, 2, 6], which indices need sift-down and which don't? Why start at n/2?

Q1: Which indices need sift-down?
A1: 1 and 2 (values 4 and 1).

Q2: Why start at n/2?
A2: n/2 = 3 is the last non-leaf. Indices 4,5,6,7 are leaves — no children, 
trivially valid. So only 1,2,3 need visiting; 3 happens to already satisfy the invariant.

Q3: Why sift-down and not sift-up?
A3: Each node's subtree below it is already a valid heap (we process bottom-up). 
So we only need to push the current node down to its correct level.
 */

#include <stdio.h>
#include "heap.h"

void heapify(int arr[], int size){
	int n = (size-1)/2;
	int lvi; // largest value index

	/* approach one with multiple loops
	bool completed = false;
	while (!completed){
		for (int i = n; i > 0; i--){
			int lci = left_child_index(i);
			int rci = right_child_index(i);
		
			if (lci > size) continue;
			else if (rci > size) lvi = lci;
			else if (arr[lci] > arr[rci]) lvi = lci;
			else lvi = rci;
	
			if (arr[i] < arr[lvi]){
				int temp = arr[i];
				arr[i] = arr[lvi];
				arr[lvi] = temp;
			}	
		}
		
		//printer(arr,size);
		// for checking if all values are sifted-down
		completed = true;
		for (int i = n; i > 0; i--){
			int lci = left_child_index(i);
			int rci = right_child_index(i);
		
			if (lci > size) continue;
			else if (rci > size) lvi = lci;
			else if (arr[lci] > arr[rci]) lvi = lci;
			else lvi = rci;
		
			if (arr[i] < arr[lvi]){
				completed = false;
				break;
			}
		}
	
	}
	*/

	// approach 2
	

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
			printf("iteration %i, and pointer (ptr) %i\n",i,ptr);
			printer(arr,size);
		}
	}
}

void main (void){
	int arr[] = {0,4, 1, 9, 3, 7, 2, 6};
	int size = sizeof(arr)/sizeof(int);
	printer(arr, size);
	heapify(arr, size);
	printer(arr, size);
}
