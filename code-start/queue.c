#include "queue.h"
#include <stdlib.h>

void shift(struct Queue *q){
	while(q->S1->top){
		struct Node *temp; //here we haven't used malloc, coz temp going to refer other location, and we don't want to make any operation on new memory locations!
		temp = q->S1->top->next;
		push(q->S2, q->S1->top->value);
		free(q->S1->top);
		q->S1->top = temp;
	}
}

void enqueue(struct Queue *queue, int value){
	push(queue->S1, value);
}

void dequeue(struct Queue *queue){
	if (is_empty(queue->S2)) shift(queue);
	pop(queue->S2);
}

bool q_is_empty(struct Queue *queue){
	return ((is_empty(queue->S1))&&(is_empty(queue->S2)))?true:false;
}

int q_peek(struct Queue *queue){
	if (is_empty(queue->S2)) shift(queue);
	return peek(queue->S2);
}
