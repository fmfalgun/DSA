#include <iostream>
#include <list>
#include <iterator>

using namespace std;

template <typename T>
list<T> stack;

template <typename T>
void push(T data){
	auto it = stack<T>.begin();
	std::advance(it, stack<T>.end());
	stack<T>.emplace(it,data);
}


template <typename T>
void pop(void){
	auto it = stack<T>.begin();
	advance(it,0);
	stack<T>.erase(it);
}

template <typename T>
T peek(void){
	size_t position = stack<T>.size();
	auto it = stack<T>.begin();
	advance(it, position-1);
	return *it;
}

template <typename T>
bool isEmpty(void){
	return stack<T>.empty();
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

