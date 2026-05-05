/*
Implement push — insert a value into the heap. The new element goes at the end; sift it up until the heap invariant holds.

Q - but we used static array can we insert new int in it eventough intialization is previously done already

Ans - Good catch. You can't — a static array has fixed size.

You have two options:

1. Declare the array large enough upfront (e.g. `int arr[100]`) and track how many elements are actually in use with a `size` variable. The rest of the slots just sit empty.
2. Use `malloc`/`realloc` for a dynamic array.

For a heap implementation, option 1 is standard and simpler. You're not really "inserting into the array" — you're writing into the next unused slot and incrementing your size counter.

Go with option 1.

 */


#include<stdio.h>

int parent_index (int value){
	if (value == 0 || value == 1) return -1;
	return ((int)value/2);
}

int left_child_index (int value){
	return (2*value);
}

int right_child_index (int value){
	return ((2*value)+1);
}

void push(int *arr, int *last_value, int value){
	arr[++(*last_value)] = value;
	int ptr = (*last_value);
	while(ptr > 1 && arr[parent_index(ptr)] < value){
		//printf("\n-> %i, arr[ptr] value = %i, arr[parent_index(ptr)] = %i",ptr, arr[ptr], arr[parent_index(ptr)]);
		arr[ptr] = arr[parent_index(ptr)];
		arr[parent_index(ptr)] = value;
		ptr = parent_index(ptr);
		//printf("\n-> %i, arr[ptr] value = %i, arr[parent_index(ptr)] = %i",ptr, arr[ptr], arr[parent_index(ptr)]);
	}
	//printf("\n-> %i, arr[ptr] value = %i, arr[parent_index(ptr)] = %i",ptr, arr[ptr], arr[parent_index(ptr)]);
}

void main (void){

	int arr[100] = {-1, 90, 70, 80, 40, 60, 10, 50};
	int last_value = 7;
	int size = sizeof(arr)/sizeof(int);
	
	for (int i = 1; i <= last_value; i++)
		printf("index %i value = %i it's parent = %i and leftchild = %i and rightchiled = %i\n", i, arr[i], parent_index(i), left_child_index(i), right_child_index(i));

	push(arr, &last_value, 95);
	push(arr, &last_value, 999);
	printf("\n");

	for (int i = 1; i <= last_value; i++)
		printf("index %i value = %i it's parent = %i and leftchild = %i and rightchiled = %i\n", i, arr[i], parent_index(i), left_child_index(i), right_child_index(i));
	

}
