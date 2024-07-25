#include <iostream>
#include <vector>
using namespace std;

// types of nodes can be made
// - Array (static)
// - Vectors (dynamic)
// - LinkedList
// - Structure based
// - Union based
// - Class based

// Vector based nodes
template<typename T>
vector<T> Node;
vector<int> leftChild;
vector<int> rightChild;

//insertion
template <typename T>
int CreateNode(T data){
	int index = Node<T>.size();
	Node<T>.push_back(data);
	leftChild.push_back(-1);
	rightChild.push_back(-1);
	return index;
}

//set childs
void SetRightChild(int parentIndex, int rightChildIndex){
	rightChild[parentIndex] = rightChildIndex;
}

void SetLeftChild(int parentIndex, int leftChildIndex){
	leftChild[parentIndex] = leftChildIndex;
}

//Searching an element
template <typename T>
int Search(T data){
	for(int i=0; i<Node<T>.size(); i++)
		if(Node<T>[i] == data)
			return i;
	return -1;
}

//Insert node
template <typename T>
void Insert(int index){
	for(int i=0; i<Node<T>.size(); i++)
		if(leftChild[i] == -1){
			leftChild[i] == index;
			break;
		}
		else if(rightChild[i] == -1){
			rightChild[i] == index;
			break;
		}
}

// Delete node
template <typename T>
void Delete(int index){
	int targetParentIndex == -1;
	T target = Node<T>[index];
	T targetLeftChild = Node<T>[leftChild[index]];
	T targetRightChild = Node<T>[rightChild[index]];

	for(int i=0; i<Node<T>.size(); i++){
		if (leftChild[i] == index) 
			targetParentIndex = i;
		else if (rightChild == index)
			targetParentIndex = i;
		if (targetParentIndex != -1) break;
	}

	//Case1 - no child nodes
	if (targetLeftChild == -1 && targetRightChild == -1){
		Node<T>.erase(Node<T>.begin() + index);
		leftChild.erase(leftChild.begin() + index);
		rightChild.erase(rightChild.begin() + index);
	}

	//Case2 - single child nodes
	else if (targetLeftChild != -1 && targetRightChild != -1){

	}
	else{
		if (targetLeftChild != -1){
			()[targetParentIndex]
		}
	}
}

int main() {
    
	

    return 0;
}
