#include <iostream>
#include <vector>
using namespace std;

// Types of Queues available are as follow
// - Array based
// - Linked List based
// - Class based
// - Structure based

// 1. Array based
template <typename T>
vector<T> q;

template <typename T>
void Enq(T data){
	q<T>.push_back(data);
}

template <typename T>
void Deq(void){
	//T temp = q<T>.begin();
	q<T>.erase(q<T>.begin());
	//return temp;
}

template <typename T>
T Peek(void){
	T temp = q<T>.front();
	return temp;
}

template <typename T>
bool isEmpty(){
	return q<T>.empty();
}

int main(void){

    cout << "Enq 1, 2, 3" << endl;
    Enq(1);
    Enq(2);
    Enq(3);

    cout << "Peek: " << Peek<int>() << endl;

    cout << "Deq" << endl;
    Deq<int>();

    cout << "Peek: " << Peek<int>() << endl;

    cout << "Enq 4" << endl;
    Enq(4);

    cout << "Peek: " << Peek<int>() << endl;

    while (!isEmpty<int>()) {
        cout << "Deq: " << Peek<int>() << endl;
        Deq<int>();
    }
	return 0;	
}
