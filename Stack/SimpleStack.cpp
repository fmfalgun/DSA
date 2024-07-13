#include <iostream>
#include <vector>

using namespace std;

// Types of Queus available are as follow
// - Array based
// - Linked List based
// - Class based
// - Structure based

// 1. Array based
template <typename T>
vector<T> stk;

// inserting element on the top
template <typename T>
void push(T data){
	stk<T>.push_back(data);
}

// removing top element
template <typename T>
void pop(void){
	stk<T>.pop_back();
}

// checking top element
template <typename T>
T peek(){
	return stk<T>.back();
}

//stack is empty?
template <typename T>
bool isEmpty(void){
	return stk<T>.empty();
}

int main(void){

 // Test the stack with integer type
    cout << "Testing stack with integers:" << endl;
    push(10);
    push(20);
    push(30);

    cout << "Top element is: " << peek<int>() << endl; // Should output 30

    pop<int>();
    cout << "Top element after pop is: " << peek<int>() << endl; // Should output 20

    cout << "Stack is empty: " << (isEmpty<int>() ? "Yes" : "No") << endl; // Should output No

    pop<int>();
    pop<int>();
    cout << "Stack is empty after popping all elements: " << (isEmpty<int>() ? "Yes" : "No") << endl; // Should output Yes

    // Test the stack with string type
    cout << "\nTesting stack with strings:" << endl;
    push(string("hello"));
    push(string("world"));

    cout << "Top element is: " << peek<string>() << endl; // Should output "world"

    pop<string>();
    cout << "Top element after pop is: " << peek<string>() << endl; // Should output "hello"

    cout << "Stack is empty: " << (isEmpty<string>() ? "Yes" : "No") << endl; // Should output No

    pop<string>();
    cout << "Stack is empty after popping all elements: " << (isEmpty<string>() ? "Yes" : "No") << endl; // Should output Yes

	return 0;
}
