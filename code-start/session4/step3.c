/*
Implement pop — remove and return the max. Swap root with last element, shrink size, sift the root down.

Q - meaning of this line
```
Implement pop — remove and return the max. Swap root with last element, shrink size, sift the root down.
```
Ans - The max in a max-heap is always at the root (index 1). You want to remove it.

But you can't just delete the root and leave a hole — the tree would break. So the strategy:

1. Save the root value (that's what you'll return)
2. Take the **last element** in the array, put it at the root, shrink size by 1
3. Now the root is probably wrong — some small value sitting at the top, violating the heap invariant
4. So push it down — compare it with its two children, swap with the **larger** child if that child is bigger than it, repeat until it's in the right place

That "bubble down toward the leaves" process is called **sift-down**.

Why swap with the *larger* child? Think about it — if you swap with the smaller one, the larger child ends up as a sibling of a node smaller than it, which still violates the invariant.

Implement it. Go.

Q - is it really sift-down or shift-down!
Ans - Sift-down. Like sifting flour — small stuff falls through, big stuff stays up. Nothing is shifting (moving everything over by one position).

Common name confusion. The operation is also called "heapify-down" or "bubble-down" in some texts. All the same thing.

Go implement it.
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

	/* Approach 1 - mine, worked fine but affected by corner case where only left child or no child exists.
	int ptr = 1;
	int lci = left_child_index(ptr);  // left child index
	int rci = right_child_index(ptr); // right child index

	while ((lci <= *last_value) && (rci <= *last_value) && (arr[ptr] < arr[lci] || arr[ptr] < arr[rci])){
		int temp;	
		if (arr[lci] > arr[rci] ){
			temp = arr[lci];
			arr[lci] = arr[ptr];
			arr[ptr] = temp;
			ptr = lci;
		}
		else{
			temp = arr[rci];
			arr[rci] = arr[ptr];
			arr[ptr] = temp;
			ptr = rci;
		}
		lci = left_child_index(ptr);  // left child index
		rci = right_child_index(ptr); // right child index
	}
	*/

	//Approach 2 - largest child find to avoid edge case of where left child exist but right doesn't exist
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

	printf("value poped = %i\n",pop(arr, &last_value));
	printf("value poped = %i\n",pop(arr, &last_value));
	printf("value poped = %i\n",pop(arr, &last_value));

	for (int i = 1; i <= last_value; i++)
		printf("index %i value = %i it's parent = %i and leftchild = %i and rightchiled = %i\n", i, arr[i], parent_index(i), left_child_index(i), right_child_index(i));
	

}
