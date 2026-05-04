/*

Concept in one paragraph:
Pick an element as a pivot. Rearrange the array so everything smaller than pivot is on its left, everything larger is on its right. Now pivot is in its final correct position. Recursively do the same for left and right sides.

No divide step, no temp array. It sorts in place.
[5, 2, 8, 1, 9, 3]   pivot = 3
→ [2, 1, 3, 5, 9, 8]   3 is now in correct position
→ sort [2,1] and [5,9,8] independently

Your task:

Write quick_sort(arr, left, right) and a helper partition(arr, left, right) that picks the last element as pivot, places it in the correct position, and returns its index.

Same signature pattern as merge sort. Start with partition — what does it need to do step by step?

 */

#include <stdio.h>


int partition(int *arr, int left, int right){

	/* Attempt 1
	if (left >= right) return left;

	int size = right - left;
	int left_arr[size];
	int right_arr[size];
	int pivot = arr[right];

	int i = 0;     //pointer to temp's left part 
	int j = 0;     //pointer to temp's right part
	
	int itr = left;    //pionter to iterate in arr from left to right
	while(itr != right){
		if (arr[itr] > pivot) right_arr[j++] = arr[itr];
		else left_arr[i++] = arr[itr];
		itr++;
	}

	int max_left = i, max_right = j;
	i = 0;
	j = 0;

	bool left_filled = false;
	int pivot_index = -1;
	for (int k = left; k < right; k++){
		if (!left_filled){
			if (i < max_left) arr[k] = left_arr[i++];
			else {
				arr[k] = pivot;
				left_filled = true;
				pivot_index = k;
				continue;
			}
		}
		if (left_filled && j < max_right) arr[k] = right_arr[j++];
	}

	for (int m = pivot_index+1; m <= right && j < max_right; m++) arr[m] = right_arr[j++];

	*/

	// Attempt 2
	
	int pivot = arr[right];
	int i = left;

	for (int j = left; j <= right-1; j++){
		if (arr[j] <= pivot){
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}

	int temp = arr[i];
	arr[i] = arr[right];
	arr[right] = temp;

	return i;
}


void quick_sort(int *arr, int left, int right){
	if (left >= right) return;
	int ptr = partition(arr, left, right);
	quick_sort(arr, left, ptr-1);	
	quick_sort(arr, ptr+1, right);	
}

void main (void){

	int arr[] = {2,2,562,346,22,457,44,4,666,7,54};	
	int size = sizeof(arr)/sizeof(int);
	int iterator = 0;
	
	while (iterator < size)	printf("%i\t", arr[iterator++]);
	printf("\n");
	quick_sort(arr, 0, size-1);	
	iterator = 0;
	while (iterator < size)	printf("%i\t", arr[iterator++]);
	printf("\n");

}
