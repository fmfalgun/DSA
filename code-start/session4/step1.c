/*

Conceptual first — given a max-heap stored in a 1-indexed array, 
write down the index formulas for parent, left child, right child. 
Then draw what this array [_, 90, 70, 80, 40, 60, 10, 50] 
looks like as a tree (index 0 unused).

Q - meaning of this line?
```
given a max-heap stored in a 1-indexed array, write down the index formulas for parent, left child, right child
```

Ans - A heap is usually drawn as a tree, but implemented as a plain array.

"1-indexed" means index 0 is unused — actual elements start at index 1. 
This is a convention choice that makes the math clean.

So if a node is at index `i`:
- its **left child** is at some index relative to `i`
- its **right child** is at another index
- its **parent** is at another

Your job for task 1 is to figure out those three formulas by staring at the tree structure.

Here's a nudge: draw the array `[_, 90, 70, 80, 40, 60, 10, 50]` as a tree 
first (root = index 1, fill level by level left to right). 
Then look at a node — say `70` at index 2 — and ask: 
where are its children in the array? What are their indices? 
Can you spot a pattern?

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

void main (void){

	int arr[] = {-1, 90, 70, 80, 40, 60, 10, 50};
	int size = sizeof(arr)/sizeof(int);
	for (int i = 1; i < size; i++)
		printf("index %i value = %i it's parent = %i and leftchild = %i and rightchiled = %i\n", i, arr[i], parent_index(i), left_child_index(i), right_child_index(i));

}
