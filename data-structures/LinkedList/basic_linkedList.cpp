#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node{
	public:
		T data;
		Node<T>* next = null;
}

template <typename T>
class LinkedList{
	private:
		Node* head = new NODE();
	public:
		void push(T val);
		void append(T val);
		void insertAfter(T target_val, T val);
		void delete(T val);
		void print();
}

template <typename T>
void push(T val){
	Node<t>* temp = new Node();
	temp->data = val;
	temp->next = this->head;
	this->head = temp;
}

template <typename T>
void append(T val){
	Node<t>* temp = new Node();
	temp->data = val;
	
	Node<t>* iterator = this->head;
	while(iterator->next!=null) iterator = iterator->next;

	iterator->next = temp;
}

template <typename T>
void insertAfter(T target_val, T val){
	Node<t>* temp = new Node();
	temp->data = val;
	
	Node<t>* iterator = this->head;
	while(iterator->data == target_val || iterator->next != null) iterator = iterator->next;

	if (iterator->data == target_val){
		temp->next = iterator->next;
		iterator->next = temp;
	}
}

template <typename T>
void delete(T val){	
	Node<t>* iterator = this->head;	
	Node<t>* prev = new Node();
	while(iterator->data!=val || iterator->next == null){
		prev = iterator;
		iterator = iterator->next;
	}

	iterator->next = temp;
}

int main (void){

	int num_of_operations;
	cin >> num_of_operations;

	while(n--){

		int X, Y;
		string command;
		cin >> command;

		if (command == 'insertAfter') cin >> Y;
		if (command != 'print')cin >> X;

		if (command == 'push'){}
		else if (command == 'append'){}
		else if (command == 'insertAfter'){}
		else if (command == 'delete'){}	
		else if (command == 'print'){}
		else cout >> "Not a Valid Command\n";
	}

	return 0;
}
