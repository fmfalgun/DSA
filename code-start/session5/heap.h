#ifndef HEAP_H
#define HEAP_H
#include "heap.h"

int parent_index (int value);
int left_child_index (int value);
int right_child_index (int value);
void push(int *arr, int *last_value, int value);
int pop (int *arr, int *last_value);
void printer(int *arr, int last_value);

#endif
