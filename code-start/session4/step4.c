/*
Push [3, 10, 1, 7, 4, 8] one by one, print the array after each push. Then pop three times, printing the popped value and array each time.
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

int pop (int *arr, int *last_value){
	int return_value = arr[1];
	arr[1] = arr[(*last_value)--];

	int ptr = 1, largest_child;

	int lci = left_child_index(ptr);
	int rci = right_child_index(ptr);

	while(lci <= *last_value){
		
		if (rci > *last_value) largest_child = lci;
		else if (arr[lci] > arr[rci]) largest_child = lci;
		else largest_child = rci;
		if (arr[ptr] >= arr[largest_child]) break;

		int temp = arr[largest_child];
		arr[largest_child] = arr[ptr];
		arr[ptr] = temp;
		ptr = largest_child;
		//printf("ptr value = %i\n", ptr);
		
		lci = left_child_index(ptr);
		rci = right_child_index(ptr);
	}
	

	return return_value;
}

void printer(int *arr, int last_value){
	for (int i = 1; i <= last_value; i++)
		printf("index %i value = %i\n", i, arr[i]);
	printf("\n");
}

void main (void){
	
	int arr1[100] =  {-1};
	int lv2 = 0;
	push(arr1,&lv2,3);
	printer(arr1,lv2);
	push(arr1,&lv2,10);
	printer(arr1,lv2);
	push(arr1,&lv2,1);
	printer(arr1,lv2);
	push(arr1,&lv2,7);
	printer(arr1,lv2);
	push(arr1,&lv2,4);
	printer(arr1,lv2);
	push(arr1,&lv2,8);
	printer(arr1,lv2);
	
	printf("value poped = %i\n",pop(arr1,&lv2));
	printer(arr1,lv2);
	printf("value poped = %i\n",pop(arr1,&lv2));
	printer(arr1,lv2);
	printf("value poped = %i\n",pop(arr1,&lv2));
	printer(arr1,lv2);
}
