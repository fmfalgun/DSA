#include "stack.h"
#include <stdlib.h>

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

