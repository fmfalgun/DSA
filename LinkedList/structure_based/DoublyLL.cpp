#include <iostream>

using namespace std;

template <typename T>
struct node{
	T data;
	node* prev;
	node* next;
};

template <typename T>
void insertion (node<T>*& head, int position, T data){
	int count = 0; 
	node<T>* target_node = head;
	node<T>* new_node = new node<T>();
	new_node->data = data;
	
	//case 1: insert at beginning
	if (position == 0){
		new_node->next = target_node;
		target_node->prev = new_node;
		head = new_node;
		return;	
	}

	//traverse to the node just before position
	while(target_node != nullptr && count < position-1){
		target_node = target_node->next;
		count++;
	}

	// check if position is valid
	if (target_node == nullptr) return;

	//insert the node
	new_node->next = target_node->next;
	target_node->next = new_node;
	new_node->prev = target_node;
	new_node->next->prev = new_node;
}

template <typename T>
void deletion (node<T>*& head, int position){

	int count = 0;
	node<T>* target_node = head;
	node<T>* new_node = new node<T>();

	//case 1: head is nullptr
	if (target_node == nullptr) return;

	//case 2: head node needs to be deleted
	if (position == 0){
		head = target_node->next;
		delete target_node;
		return;
	}

	//traverse to the target_node
	while(target_node != nullptr && count < position-1){
		target_node = target_node->next;
		count++;
	}

	if (target_node == nullptr) return;
 
	//deleting the node
	node<T>* temp = target_node->next;
	target_node->next = (target_node->next != nullptr)?target_node->next->next:nullptr;
	if(target_node->next->next != nullptr) target_node->next->next->prev = target_node;
	delete temp;
}

template <typename T>
node<T>* search(node<T>* head, T value){
	node <T>* result = head;
	while(result != nullptr && result->data != value)
		result= result->next;
	return result;
}

template <typename T>
void traversal(node<T> head_or_tail){
	node<T>* iterator = head_or_tail;
	if (head_or_tail->next == nullptr)
		while(iterator->prev != nullptr){
			cout << iterator->data << " ";
			iterator = iterator->prev;
		}
	else	while(iterator->next != nullptr){
			cout << iterator->data << " ";
			iterator = iterator->next;
	}
}

template <typename T>
void update(node<T>* head, int position, T new_data){
	node<T>* target_node = head;
	while(target_node != nullptr && position--)
		target_node = target_node->next;
	target_node->data = new_data;
}

template <typename T>
void reverse(node<T>*& head){
	node<T>* target_node = head;
	node<T>* temp = new node<T>();
	while(target_node != nullptr){
		temp = target_node;
		target_node->prev = target_node->next;
		target_node->next = temp->prev;
		head = target_node;
		target_node = temp->next;
	}
}

template <typename T>
int length(node<T>* head){
	int len = 0;
	while (head != nullptr){
		head = head->next;
		len++;
	}
	return len;
}
int main(void){

}
