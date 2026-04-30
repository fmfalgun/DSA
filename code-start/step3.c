// Implement a stack using a linked list in C.
// - push(value)
// - pop()
// - peek()
// - is_empty()

// No arrays. Each node is malloc'd.
// Test it: push 1,2,3 → peek → pop → peek → print remaining.


#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *next;
};

struct Stack{
	struct Node *top;
};

void push(struct Stack *stack, int value){
	struct Node *temp = malloc(sizeof(struct Node));
	temp->value = value;	

	temp->next = stack->top;
	stack->top = temp;
}

int peek(struct Stack *stack){
	return stack->top->value;	
}

void pop(struct Stack *stack){
	if (stack->top == NULL) return;  
	struct Node *ptr = stack->top->next;
	free (stack->top);
	stack->top = ptr;
}

bool is_empty(struct Stack *stack){
	return (stack->top == NULL)?true:false;
}

void main (void){

	struct Stack *stack = malloc(sizeof(struct Stack));
	
	stack->top = NULL;
	printf("is empty = %i\n", is_empty(stack));

	push(stack, 1);
	push(stack, 2);
	push(stack, 3);
	
	printf("peek value = %i\n", peek(stack));

	pop(stack);

	printf("new peek value after pop = %i\n", peek(stack));
	
}
