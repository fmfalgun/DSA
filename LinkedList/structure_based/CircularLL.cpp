#include <iostream>

using namespace std;

//NOTE: position of node is calculated in terms of whole numbers

template <typename T>
struct node{
	T data;
	node<T>* next;

	node(T data){
		this->data = data;
		this->next = this;
	}
};

template <typename T>
void insertion(node<T>*& head, int position, T data) {
    node<T>* new_node = new node<T>(data);
    
    if (head == nullptr) { // Case 0: Empty list
        head = new_node;
        return;
    }

    node<T>* tail = head;
    int len = 1;
    
    // Calculate the length of the list
    while (tail->next != head) {
        tail = tail->next;
        len++;
    }

    // Adjust position within valid bounds
    position = position % len;

    if (position == 0) { // Case 1: Insert at the beginning
        new_node->next = head;
        tail->next = new_node;
        head = new_node;
        return;
    }

    // Traverse to the node just before the position
    node<T>* target_node = head;
    for (int count = 1; count < position; count++) {
        target_node = target_node->next;
    }

    // Insert the new node at the correct position
    new_node->next = target_node->next;
    target_node->next = new_node;
}

template <typename T>
void deletion(node<T>*& head, int position) {
    if (head == nullptr) return; // Case 1: Empty list

    node<T>* tail = head;
    int len = 1;

    // Calculate the length of the list
    while (tail->next != head) {
        tail = tail->next;
        len++;
    }

    if (len == 1) { // Case 2: Single node in the list
        delete head;
        head = nullptr;
        return;
    }

    // Adjust position within valid bounds
    position = position % len;

    if (position == 0) { // Case 3: Delete head node
        tail->next = head->next;
        node<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Traverse to the node just before the position
    node<T>* target_node = head;
    for (int count = 1; count < position; count++) {
        target_node = target_node->next;
    }

    // Delete the target node
    node<T>* temp = target_node->next;
    target_node->next = temp->next;
    delete temp;
}

template <typename T>
node<T>* search (node<T>* head, int value){
	bool found = false;
	node<T> * temp = head;
	do{ 
		if (temp->data == value) found = true;
		else temp = temp->next;
	}while(!found && temp != head);
	if (found) return temp; else return nullptr;
}

template <typename T>
void traversal(node<T>* head){
	node<T>* temp = head;
	do{
		cout << temp->data << "->";
		temp = temp->next;
	}while(temp != head);
	cout << "HEAD\n";
}

template <typename T>
void update(node<T>*& head, int position, int new_data){

	if (head == nullptr) return;

	int len = 0;
	node<T>* temp = head;
	do{
		temp = temp->next;
		len ++;
	}while(temp != head);

	position = position%len;

	if(position == 0)
		head->data = new_data;
	else {
		while(position--){
			temp = temp->next;
			cout << "temp value = " << temp->data << endl;
		};
		cout << "temp prev value = " << temp->data << endl;
		temp->data = new_data;
	}
}

template <typename T>
void reverse(node<T>*& head){
	if (head == nullptr) return;

	int len = 1;
	node<T>* current = head;
	while(current->next != head){
		current = current->next;		
		len++;
	}

	node<T>* prev = current; 	//tail
	current = head;
	node<T>* next = current->next;
	while(len--){
		current->next = prev;
		prev = current;
		current = next;
		next = next->next;
	}
	head = next;
}

int main() {
    // Create an empty circular linked list
    node<int>* head = nullptr;

    // Insert elements into the circular linked list
    insertion(head, 0, 10); // Insert 10 at position 0
    insertion(head, 1, 20); // Insert 20 at position 1
    // Search for elements in the circular linked list
    int searchValue = 15; // Value to search for
    node<int>* result = search(head, searchValue);

    if (result) {
        cout << "Found value " << searchValue << " in the list." << endl;
    } else {
        cout << "Value " << searchValue << " not found in the list." << endl;
    }

    insertion(head, 1, 15); // Insert 15 at position 1
    insertion(head, 3, 25); // Insert 25 at position 3 (end)
    insertion(head, 10, 30); // Insert 30 at position 10 (beyond end, should wrap around)

    // Function to print the circular linked list
    cout << "head = " << head->data << endl;

    // Print the list after insertions
    cout << "List after insertions: ";
    traversal(head);

    // Reverse the circular linked list
    reverse(head);

    // Print the list after reversal
    cout << "List after reversal: ";
    traversal(head);


    // Delete elements from the circular linked list
    deletion(head, 1); // Delete element at position 1 (15)
    deletion(head, 0); // Delete element at position 0 (10, the head)
    deletion(head, 2); // Delete element at position 2 (25)

    // Print the list after deletions
    cout << "List after deletions: ";
    traversal(head);

    // Reverse the circular linked list
    reverse(head);

    // Print the list after reversal
    cout << "List after reversal: ";
    traversal(head);


    // Search for elements in the circular linked list
    result = search(head, searchValue);

    if (result) {
        cout << "Found value " << result->data << " in the list." << endl;
    } else {
        cout << "Value " << searchValue << " not found in the list." << endl;
    }


    cout << "head = " << head->data << endl;
    // Traverse and print the list
    cout << "List traversal: ";
    traversal(head);
    cout << endl;

    // Update elements in the circular linked list
    int updatePosition = 9120; // Position to update
    int newValue = 50; // New value to set
    update(head, updatePosition, newValue);

    // Print the list after update
    cout << "List after update at position " << updatePosition << ": ";
    traversal(head);

    // Reverse the circular linked list
    reverse(head);

    // Print the list after reversal
    cout << "List after reversal: ";
    traversal(head);


    return 0;
}

