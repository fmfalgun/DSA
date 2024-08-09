#include <iostream>

using namespace std;

// we are going to code on following manner 
// - structure base
// - class base
// - union base
// - pointer base
// - arrays base

// 1) Structure base code

// Generic Node
template <typename T>
struct Node{

	T data;
	Node* next;

};


template <typename T>
void insertion(Node<T>*& head, int position, T data){
	int count = 0;
	Node<T>* target_node = head;

	//special case: insertion at begining
	if (position == 0){
	Node<T>* new_node = new Node<T>();
		new_node->data = data;
		new_node->next = head;
		head = new_node;
		return;
	}

	//traverse to the node just before the postition
	while(target_node != nullptr && count < position-1){
		target_node = target_node->next;
		count++;			
		
	}

	//check if position is valid
	if (target_node == nullptr) return;

	//inset the node 
	Node<T>* new_node = new Node<T>();
	new_node->data = data;
	new_node->next = target_node->next;
	target_node->next = new_node;
}

template <typename T>
void deletion(Node<T>*& head, int position){
	int count = 0;
	Node<T>* target_node = head;

	//special case: head is nullptr
	if (head == nullptr) return;

	//special case: head node needs to be deleted
	if (position ==0){
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}

	//traverse to the target_node
	while(target_node != nullptr && count < position-1){
		target_node = target_node->next;
		count++;
	}

	if (target_node == nullptr) return;

	//deleting the node
	Node<T>* temp = target_node->next;
	target_node->next = (target_node->next != nullptr)?target_node->next->next:nullptr;
	delete temp;
}

template<typename T>
Node<T>* search(Node<T>* head, T value){
	Node<T>* result = head;
	while(result!=nullptr && result->data != value)
		result = result->next;
	return result;
}

template<typename T>
void traversal(Node<T>* head){
	Node<T>* temp = head;
	while (temp!= nullptr){
		cout << temp->data << " ";
		temp = temp->next;
	}
}

template <typename T>
void update (Node<T>* head, int position, T data){
	Node<T>* temp = head;
	while(temp!= nullptr && position >0){
		temp = temp->next;
       		position --;
	}
 	if (temp != nullptr) { // Ensure the position is within the list
        	temp->data = data;
    	} else {
        	std::cout << "Position out of bounds" << std::endl;
    	}
}

template <typename T>
void reverse (Node<T>*& head){
	Node<T>* next = nullptr;
	Node<T>* now = head;
	Node<T>* prev = nullptr;


	while (now != nullptr){
		
		next = now->next;
		now->next = prev;
		prev = now;
		now = next;
	}
	head = prev;
}

// Main function to test insertion and deletion
int main() {
    // Example usage
    Node<int>* head = nullptr;

    // Insert nodes
    insertion(head, 0, 10);  // Insert at beginning
    insertion(head, 1, 20);  // Insert at position 1
    insertion(head, 2, 30);  // Insert at position 2
    insertion(head, 1, 15);  // Insert at position 1

    // Print the linked list
    std::cout << "Linked List after insertions: ";
    traversal(head);
    std::cout << std::endl;

    // Testing search function
    int value_to_search = 15;
    Node<int>* result = search(head, value_to_search);
    if (result != nullptr) {
        std::cout << "Found value " << value_to_search << " at address: " << result << std::endl;
    } else {
        std::cout << "Value " << value_to_search << " not found in the list." << std::endl;
    }

    // Delete nodes
    deletion(head, 1);  // Delete node at position 1

    // Print the linked list after deletion
    std::cout << "Linked List after deletion: ";
    traversal(head);
    std::cout << std::endl;

    // Testing search function again
    value_to_search = 15;
    result = search(head, value_to_search);
    if (result != nullptr) {
        std::cout << "Found value " << value_to_search << " at address: " << result << std::endl;
    } else {
        std::cout << "Value " << value_to_search << " not found in the list." << std::endl;
    }

    // Update nodes
    update(head, 1, 25);  // Update node at position 1
    std::cout << "Linked List after update: ";
    traversal(head);
    std::cout << std::endl;

    // Reverse the linked list
    reverse(head);
    std::cout << "Linked List after reversal: ";
    traversal(head);
    std::cout << std::endl;

    // Clean up memory
    Node<int>* current = head;
    while (current != nullptr) {
        Node<int>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;

    return 0;
}

