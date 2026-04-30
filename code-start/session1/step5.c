// Implement binary search on a sorted integer array.
// Then: what happens if the array has duplicates 
// and you want the FIRST occurrence of the target?
// Rules:

// - No libraries
// - Write it as a function: int binary_search(int arr[], int size, int target)
// - Returns index if found, -1 if not
// 
// Test it yourself with a few cases
//
// Then think about the duplicate problem separately.

#include <stdio.h>

int binary_search(int *arr, int size, int target){	
/*	
 *	appraoach one
 *
	int index = size/2;
	size  = size/2;
	while (size > 0){
		printf("index = %i, n size = %i \n",index, size);
		size = size/2;
		if (target == arr[index]) return index;
		else if (target > arr[index]) index += size;
		else index -= size;
	}
*/
	//aproach two

	int left = 0, right = size-1, mid;
	while (left <= right){
		//printf("left = %i, right = %i, mid = %i, target = %i \n",left, right, mid, target);
		mid = left + ((right - left)/2);
		if (target == arr[mid]) return mid;
		else if (target > arr[mid]) left = mid + 1;
		else if (target < arr[mid]) right = mid - 1;
	}	
	return -1;
}

int first_occurance (int *arr, int size, int target){
	
	int left = 0, right = size-1, mid;
	while (left <= right){
		//printf("left = %i, right = %i, mid = %i, target = %i \n",left, right, mid, target);
		mid = left + ((right - left)/2);
		if (target == arr[mid]){
			
			int val = first_occurance(arr, mid, target);
			if (val != -1) mid = val;
			break;
		}
		else if (target > arr[mid]) left = mid + 1;
		else if (target < arr[mid]) right = mid - 1;
	}
	return (arr[mid] == target)? mid: -1;	
}

void main (void)
{

	//int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int arr[] = {1,2,2,2,3,5,5,8,9,9,10};	
	int size = sizeof(arr)/sizeof(int);
	
	printf("-1 index mean number not found\n");
	printf("searching for value 5 and found  it at = %i index\n", binary_search(arr, size, 5));
	printf("searching for value 8 and found  it at = %i index\n", binary_search(arr, size, 8));
	printf("searching for value 3 and found  it at = %i index\n", binary_search(arr, size, 3));
	printf("searching for value 9 and found  it at = %i index\n", binary_search(arr, size, 9));
	printf("searching for value 343 and found  it at = %i index\n", binary_search(arr, size, 343));
	printf("searching for value 986 and found  it at = %i index\n", binary_search(arr, size, 986));
	printf("searching for value 2 and found  it at = %i index\n", binary_search(arr, size, 2));
	printf("searching for value 2 and found  it at = %i index\n", first_occurance(arr, size, 2));
	printf("searching for value 65 and found  it at = %i index\n", binary_search(arr, size, 65));

}
