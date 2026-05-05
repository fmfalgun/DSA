/*

 **Session 03 — Step 1: BST Insert**

Implement a BST in C.

**You need:**
- `struct Node` — holds an `int` value, left and right child pointers
- `create_node(value)` — mallocs and returns a new node
- `insert(root, value)` — recursively inserts value, maintaining BST property (left < node, right >= node). Returns the root.

**In `main`:** insert a few values, then print the root and its children manually to verify structure.

Go ahead.

 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *left_node;
	struct Node *right_node;
};

struct Node* create_node(int value){
	struct Node* node = malloc(sizeof(struct Node*));
	node->value = value;
	node->left_node = NULL;
	node->right_node = NULL;
	return node;
}

struct Node* insert (struct Node *node, int value){
	/* approach 1 - thought of inserting values and not returning anything
	struct Node temp = root;
	struct Node new_node = create_code(value);
	while(temp->left_node != NULL || temp->right_node != NULL){
		if (temp->value > value) temp = temp->left_node;
		else temp = temp->right_node;
	}
	if (temp->value <= value) temp->left_node = new_node;
	if (temp->value > value) temp->right_node = new_node;
	*/

	/* approach 2 -
	  insert(NULL, 5)      → create and return new node
	  insert(node, 5):
    	  if 5 < node->value → node->left  = insert(node->left,  5)
    	  if 5 >= node->value → node->right = insert(node->right, 5)
    	  return node
	*/

	if (node == NULL) return create_node(value);
	if (value < node->value) node->left_node = insert(node->left_node, value);
	if (value >= node->value) node->right_node = insert(node->right_node, value);
	return node;
}

void inorder (struct Node* node){
	if (node == NULL) return;
	inorder(node->left_node);
	printf("%i\t",node->value);
	inorder(node->right_node);
}

struct Node* left_most_node (struct Node* node){
	if (node->left_node == NULL) return node;
	left_most_node(node->left_node);
}

struct Node* delete(struct Node* node, int value){
	if (node == NULL) return node;
	if (value < node->value) node->left_node = delete(node->left_node, value);
	else if (value > node->value) node->right_node = delete (node->right_node, value);
	else {
		struct Node *temp;
		temp = node;
		if (node->left_node == NULL && node->right_node == NULL){
			free (node);
			return NULL;
		}
		else if (node->left_node != NULL && node->right_node == NULL){
			node = node->left_node;
			free(temp);
		}
		else if (node->right_node != NULL && node->left_node == NULL){
			node = node->right_node;
			free(temp);
		}
		else{
			/*
			// Approach 1 - replace the target node with left most leaf of right subtree
			// beacause in this one we lost the track of node->left
			node = node->right_node;
			struct Node *prev;
			while(node->left_node != NULL){
				prev = node;
				node = node->left_node;
			}
			prev->left_node = NULL;
			free(temp);
			*/

			// Approach 2 - replace value from successor with target node and then remove successor node
			struct Node *successor = node->right_node;
			while(successor->left_node != NULL) successor = successor->left_node;
			node->value = successor->value;
			node->right_node = delete(node->right_node, successor->value);
		}
	}
	return node;

}

bool search (struct Node * node, int value){
	if (node == NULL) return false;
	/* Old logic
	if (node->value == value) return true;
	int found = false;
	if (node->value > value) found = search(node->left_node,value);
	if (node->value <= value) found = search(node->right_node,value);
	return found;
	*/

	// better logic
	if (node->value ==value) return true;
	else if (node->value > value) return search(node->left_node,value);
	else return search(node->right_node,value);	
}

void main (void){

	struct Node* root = create_node(34);
	insert(root, 34);
	insert(root, 10);
	insert(root, 15);
	insert(root, 5);
	insert(root, 13);
	insert(root, 2);
	insert(root, 7);
	insert(root, 17);

	inorder(root);

	printf("\nfound number 15 = %i\n",search(root, 15));
	printf("found number 15 = %i\n",search(root, 1345));

	delete(root, 17);
	delete(root, 10);
	inorder(root);
}
