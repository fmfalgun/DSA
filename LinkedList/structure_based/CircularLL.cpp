#include <iostream>

using namespace std;

template <typename T>
struct node{
	T data;
	node<T>* next;
};

template <typename T>
void insertion (node<T>*& head, int position, T data){
	int len = 1, count = 0;
	node<T>* new_node = new node<T>();
	new_node->data = data;
	new_node->next = new_node;
	
	node<T>* tail = head;
	node<T>* target_node = head;

	//case 0: head is null pointer
	if (head == nullptr) return head = new_node;

	else while(tail->next == head){
		tail = tail->next;
		len ++;
	}

	//case 1: insertion at beginning
	if (position == 0){
		new_node->next = head;
		tail->next = new_node;
		head = new_node;
		return;
	}

	//traverse to the node just before position
	if (position > len) position = position % len;
	while(target_node->next != nullptr && count != position-1){
		target_node = target_node->next;
		count++;
	}

	//case 2: insertion at nth location
	new_node->next = target_node->next;
	target_node->next = new_node;
}	

template <typename T>
void deletion(node<T>*& head, int position){
	int count = 0, len = 0;
	node<T>* target_node = head;
	node<T>* tail = head;
	// calculating len of ll
	while(tail->next != head){
		tail = tail->next;
		len++;
	}

	//case 1: head is nullptr
	if (head == nullptr) return;

	//case 2: head node needs to be deleted
	if (position%len == 0){
		tail->next = head->next;
		head = head->next;
		delete target_node;
		return;
	}
 
	//traverse to node before node to be deleted
	while(target_node != head && count != position-1){
		target_node = target_node->next;
		count ++;
	}

	//case 3: target node deletion
	node<T>* temp = target_node->next; 
	target_node->next = target_node->next->next;
	delete temp;
}



int main (void){


	return 0;
}
