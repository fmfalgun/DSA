#ifndef QUEUE_H
#define QUEUE_H
#include "stack.h"

struct Queue{
	struct Stack *S1;
	struct Stack *S2;
};

void enqueue(struct Queue *queue, int value);
void dequeue(struct Queue *queue);
bool q_is_empty(struct Queue *queue);
int q_peek(struct Queue *queue);

#endif
