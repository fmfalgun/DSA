/*
 * Write a function in C that takes an integer array and its size, 
 * and sorts it using merge sort. Print the sorted array in main.
 *
 * Merge sort is **divide and conquer**. Three steps:
**1. Divide** — split the array in half, keep splitting until you have arrays of size 1
**2. Conquer** — an array of size 1 is already sorted (trivially)
**3. Merge** — take two sorted halves and combine them into one sorted array
---
The magic is in the merge step. Imagine you have:
```
[1, 4, 7]    [2, 3, 9]
```
You compare the fronts — 1 vs 2. Take the smaller (1). Then 4 vs 2. Take 2. Then 4 vs 3. Take 3. And so on:
```
[1, 2, 3, 4, 7, 9]
```
Two sorted arrays merge into one sorted array in O(n) time.
---
**The full picture:**
```
[5, 2, 8, 1, 9, 3]
       ↓ divide
  [5, 2, 8]   [1, 9, 3]
       ↓ divide again
 [5] [2,8]   [1] [9,3]
       ↓ divide again
[5] [2] [8]  [1] [9] [3]
       ↓ now merge back up
  [2,5] [8]   [1,3] [9]
       ↓
  [2,5,8]     [1,3,9]
       ↓
  [1,2,3,5,8,9]
```
---
**Why is it O(n log n)?**
- You split log n times (halving each time)
- Each merge level touches all n elements
- So: n × log n
---
That's the whole concept. Now try to code it — start with the merge function first, that's the heart of it. What does the signature look like? *
 */

#include <stdio.h>

void arr_print(int *arr, int size){
	for (int i=0; i<size; i++)
		printf("%i\t",arr[i]);
	printf("\n");	
}

void merge(int *arr, int left, int right, int mid){
/* approach 1 - incorrect, now if we want to correct
 * then right half become unsorted so we again need to 
 * call merge_sort there, which also increase time complexity
 * exponentially!
 
	int ptr = mid;
	while (left <= right){
		while (ptr <= right){
			int temp;
			if (arr[left] > arr[ptr]){
				temp = arr[left];
				arr[left] = arr[ptr];
				arr[ptr] = temp;
				ptr++;
			}
			else left++;
		}
	}
*/

	int size = right - left +1;
	int temp[size];

	int i = left;     // pointer to left half
	int j = mid + 1;  // pointer to right half
	int k = 0;        // pointer to temp

	while (i <= mid && j <= right){
		if (arr[i] <= arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}

	while (i<= mid) temp[k++] = arr[i++];
	while (j <= right) temp[k++] = arr[j++];

	for (i = 0; i < size; i++)
		arr[left+i] = temp[i];

}

void merge_sort(int *arr, int left, int right){
	if (left >= right) return;
	int mid = (left + (right - left)/2);
	merge_sort(arr, left, mid);
	merge_sort(arr, mid+1, right);
	merge(arr,left,right,mid);
}

void main (void){

	int arr[] = {2,2,562,346,22,457,44,4,666,7,54};
	int size = sizeof(arr)/sizeof(int);

	arr_print(arr,size);
	merge_sort(arr,0,size-1);
	arr_print(arr,size);
}
