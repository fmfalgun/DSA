#ifndef STACK_H
#define STACK_H

struct Node {
int value;
struct Node *next;
};

struct Stack{
struct Node *top;
};

void push(struct Stack *stack, int value);
int peek(struct Stack *stack);
void pop(struct Stack *stack);
bool is_empty(struct Stack *stack);

#endif
