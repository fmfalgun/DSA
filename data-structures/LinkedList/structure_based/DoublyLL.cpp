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
	new_node->prev = nullptr;
	new_node->next = nullptr;
	
	//case 1: insert at beginning
	if (position == 0){
		new_node->next = target_node;
		if(target_node != nullptr) target_node->prev = new_node;
		new_node->prev = nullptr;
		head = new_node;
		//cout << new_node->data << " ";
		//if (new_node->prev != nullptr) cout << new_node->prev->data << " "; else cout << "prev node is nullptr\n";
		//if (new_node->next != nullptr) cout << new_node->next->data << endl; else cout << "next node is nullptr \n";
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
	new_node->prev = target_node;
	target_node->next = new_node;
	if (new_node->next != nullptr) new_node->next->prev = new_node;

	//cout << new_node->data << " ";
	//if (new_node->prev != nullptr) cout << new_node->prev->data << " "; else cout << "prev node is nullptr\n";
	//if (new_node->next != nullptr) cout << new_node->next->data << endl; else cout << "next node is nullptr \n";
}

template <typename T>
void deletion (node<T>*& head, int position){

	int count = 0;
	node<T>* target_node = head;

	//case 1: head is nullptr
	if (target_node == nullptr) return;

	//case 2: head node needs to be deleted
	if (position == 0){
		head = target_node->next;
		if (head!=nullptr) head->prev = nullptr;
		delete target_node;
		return;
	}

	//traverse to the target_node
	while(target_node != nullptr && count < position-1){
		target_node = target_node->next;
		count++;
	}

	if (target_node == nullptr || target_node->next == nullptr) return;
 
	//deleting the node
	node<T>* temp = target_node->next;
	target_node->next = (target_node->next != nullptr)?target_node->next->next:nullptr;
	if(target_node->next != nullptr) target_node->next->prev = target_node;
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
void traversal(node<T>* head_or_tail){
	node<T>* iterator = head_or_tail;
	
	if(head_or_tail == nullptr) return;

	if (iterator->next != nullptr){
		while(iterator != nullptr){
			cout << iterator->data << " ";
			iterator = iterator->next;
	}}else if (iterator->prev != nullptr){
		while (iterator != nullptr){
			cout << iterator->data << " ";
			iterator = iterator->prev;
		}	
	}else cout << "cannot determine if node is head or tail" << endl;
}

template <typename T>
void update(node<T>* head, int position, T new_data){
	node<T>* target_node = head;
	while(target_node != nullptr && position--)
		target_node = target_node->next;
	target_node->data = new_data;
}
template <typename T>
void reverse(node<T>*& head) {
    node<T>* current = head;
    node<T>* temp = nullptr;

    // Traverse and swap next and prev pointers
    while (current != nullptr) {
        // Swap the next and prev pointers
        temp = current->prev;

        // Swap the current node's prev and next pointers
        current->prev = current->next;
        current->next = temp;

        // Move to the next node in the original list (which is the prev in the reversed list)
        current = current->prev;

    }

    // Update head to the new first node
    if (temp != nullptr && temp->prev != nullptr) {
        head = temp->prev;
    } else if (current != nullptr) {
        head = current;
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

int main() {
    // Example usage
    node<int>* head = nullptr;

    // Insert nodes
    insertion(head, 0, 10);  // Insert at beginning
    insertion(head, 1, 20);  // Insert at position 1
    insertion(head, 2, 30);  // Insert at position 2
    insertion(head, 1, 15);  // Insert at position 1

    // Print the linked list
    std::cout << "Doubly Linked List after insertions: ";
    traversal(head);
    std::cout << std::endl;

    // Testing search function
    int value_to_search = 15;
    node<int>* result = search(head, value_to_search);
    if (result != nullptr) {
        std::cout << "Found value " << value_to_search << " at address: " << result << std::endl;
    } else {
        std::cout << "Value " << value_to_search << " not found in the list." << std::endl;
    }

    // Delete nodes
    deletion(head, 1);  // Delete node at position 1

    // Print the linked list after deletion
    std::cout << "Doubly Linked List after deletion: ";
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
    std::cout << "Doubly Linked List after update: ";
    traversal(head);
    std::cout << std::endl;

    // Reverse the linked list
    cout << endl;
    reverse(head);
    std::cout << "Doubly Linked List after reversal: ";
    traversal(head);
    cout << "\n";
    // Print the length of the linked list
    std::cout << "Length of the linked list: " << length(head) << std::endl;

    // Clean up memory
    node<int>* current = head;
    while (current != nullptr) {
        node<int>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;

    return 0;
}

