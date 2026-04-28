#include <iostream>

using namespace std;

template <typename T>
struct node{
	T data;
	node* next;
	node* prev;
	
	node(T data){
		this->data = data;
		this->next = this;
		this->prev = this;
	}
};

template <typename T>
void insertion (node<T>*& head, int position, T data){
	if (head == nullptr) {
		node<T>* new_node = new node<T>(data);
		head = new_node;
		return;	
	};

	node<T>* temp = head;
	int len = 1;
	while(temp != head){
		temp = temp->next;
		len++;
	}

	position = position%len;

	while(position--)
		temp = temp->next;

	node<T>* new_node = new node<T>(data);
	new_node->next = temp;
	new_node->prev = temp->prev;
	temp->prev = new_node;
	new_node->prev->next = new_node;		
	
	if (position == 0) head = new_node;
}

template <typename T>
void deletion (node<T>*& head, int position){
	if (head == nullptr) return;

	int len = 0;
	node<T>* temp = head;
	do{
		len++;
		temp = temp->next;
	}
	while(temp != head);

	position = position%len;

	while(position--)
		temp = temp->next;

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	if (position == 0) head = temp->next;
	delete temp;
}

template <typename T>
node<T>* search(node<T>*& head, T value){
	if (head == nullptr) return nullptr;

	node<T>* temp = head;
	bool found = false;
	do{
		if (temp->data == value) {
			found = true;
			break;
		}
		temp = temp->next;
	}while(temp != head);

	if (found) return temp;
	else return nullptr;
}

template <typename T>
void traversal(node<T>* head){

	if (head == nullptr) return;
	node<T>* temp = head;
	do {
		cout << temp->data << " -> ";
		temp = temp->next;
	}while (temp != head);
	cout << "HEAD\n";
}

template <typename T>
void update(node<T>*& head, int position, T value){
	
	if (head == nullptr) return;

	int len = 0;
	node<T>* temp = head;
	do{
		len++;
		temp = temp->next;
	}while(temp!= head);

	position = position%len;

	while(position--)
		temp = temp->next;

	temp->data = value;
}

template <typename T>
void reverse(node<T>*& head){
	if (head == nullptr) return;

	int len = 0;
	node<T>* temp = nullptr;
	node<T>* current = head;
	node<T>* tail = head->prev;

	do{
		len++;
		current = current->next;
	}while(current != head);

	for (int i=0; i<len; i++){
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	head = tail;
}

int main(void){

    node<int>* head = nullptr;

    // Insert elements into the circular doubly linked list
    insertion(head, 0, 10); // Insert 10 at position 0
    insertion(head, 1, 20); // Insert 20 at position 1
    insertion(head, 2, 30); // Insert 30 at position 2
    insertion(head, 1, 15); // Insert 15 at position 1

    // Traverse and print the list elements using the traversal function
    cout << "List after insertions: ";
    traversal(head); // Use traversal to print the list

    // Delete an element from the circular doubly linked list
    deletion(head, 90); // Delete element at position 1

    // Traverse and print the list elements again after deletion
    cout << "List after deletion: ";
    traversal(head); // Use traversal to print the list

    // Search for an element in the circular doubly linked list
    int searchValue = 15;
    node<int>* searchResult = search(head, searchValue);

    // Check if the element was found
    if (searchResult) {
        cout << "Found value " << searchValue << " in the list.\n";
    } else {
        cout << "Value " << searchValue << " not found in the list.\n";
    }
    // Update an element at a specific position in the circular doubly linked list
    int updatePosition = 7;
    int newValue = 50;
    update(head, updatePosition, newValue);

    // Traverse and print the list elements after the update
    cout << "List after update at position " << updatePosition << ": ";
    traversal(head); // Use traversal to print the list

    // Reverse the circular doubly linked list
    reverse(head);

    // Traverse and print the list elements after reversal
    cout << "List after reversal: ";
    traversal(head); // Use traversal to print the list

    return 0;
}

