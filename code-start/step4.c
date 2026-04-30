// implement a queue using two stacks.
//
// logic (acc to me)
// s1 -> input stack
// s2 -> output stack

// enqueue and is_empty -> perform push and is_empty operation in S1 only, respectively.
// dequeue and q_peek -> require firstly push all values from S1 to S2 (if s2 is empty) 
// then perform pop and q_peek operation on S2, respectively;

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void main (void){

	struct Queue *q = malloc(sizeof(struct Queue));
	struct Stack *S1 = malloc(sizeof(struct Stack));
	struct Stack *S2 = malloc(sizeof(struct Stack));
	q->S1 = S1;
	q->S2 = S2;

	S1->top = NULL;
	S2->top = NULL;

	printf("is empty = %i\n", q_is_empty(q));

	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);

	printf("q_peek value = %i\n", q_peek(q));

	dequeue(q);

	printf("new q_peek value after pop = %i\n", q_peek(q));


}
