#include "PriorityQueue.h"
#include <iostream>
#include <algorithm>
using namespace std;

//constructor to that sets capacity
PriorityQueue::PriorityQueue(int c){
	capacity = c;
	numberOfElements = 0;
	PQ = new MyData[capacity];
}

//print the number of elements in the PriorityQueue
void PriorityQueue::PrintNumberOfElements(){
	cout << "Number of elements in PQ: " << numberOfElements << endl;
}

//return the parent of the input
int PriorityQueue::GetParent(int child){
	if(child % 2 == 0)
		return (child / 2) - 1;
	else
		return (child / 2);
}

//place value into the priority queue 
void PriorityQueue::Push(int index, double value){
	if (numberOfElements < capacity) {
		MyData element;
		element.index = index;
		element.value = value;

		int i = numberOfElements;
		while (i != 0 && element.value < PQ[i / 2].value){
			PQ[i] = PQ[i / 2];
			i = i / 2;
		}
		PQ[i] = element;
		numberOfElements++;
		/*cout << "Added (" << index << "," << value << ")  ,  size: ";
		cout << numberOfElements << endl;*/
	}
	else 
		cout << "Out of capacity\n";
}

//increase the capacity of the PQ then push
void PriorityQueue::IncreaseCapacityThenPush(int index, double value){
	capacity++;
	if (numberOfElements < capacity) {
		MyData element;
		element.index = index;
		element.value = value;

		int i = numberOfElements;
		while (i != 0 && element.value < PQ[i / 2].value) {
			PQ[i] = PQ[i / 2];
			i = i / 2;
		}
		PQ[i] = element;
		numberOfElements++;
		cout << "Added (" << index << "," << value << ")  ,  size: ";
		cout << numberOfElements << endl;
	}
	else
		cout << "Out of capacity\n";
}

//Dequeue.Pop the first element from the priority queue
MyData PriorityQueue::Pop(){
	if (numberOfElements > 0) {
		MyData temp = PQ[0];
		PQ[0] = PQ[numberOfElements - 1];
		MinHeapify(0, numberOfElements);
		numberOfElements--;
		return temp;
	}
	else {
		MyData temp;
		temp.index = -1;
		temp.value = 0;
		return temp;
	}
}

//
void PriorityQueue::DecreaseKey(int index, double value){
	int i = 0;
	bool found = false;
	while (!found && i < numberOfElements) {
		if (PQ[i].index == index) {
			PQ[i].value = value;
			found = true;
		}
		i++;
	}
	if (found) {
		int child = i - 1;
		int parent = GetParent(child);
		while (PQ[child].value < PQ[parent].value && child >= 0 && parent >= 0) {
			swap(PQ[child], PQ[parent]);
			child = parent;
			parent = GetParent(child);
		}
	}
}

//mantain the minHeap properties
void PriorityQueue::BuildMinHeap(){
	for (int i = numberOfElements / 2 - 1; i >= 0; i--) {
		MinHeapify(i, numberOfElements);
	}
}

//Display the priority queue
void PriorityQueue::DisplayPQ(){
	cout << "Priority Queue\n";
	cout << "     Capacity: " << capacity << "/n     Number of elements: ";
	cout << numberOfElements << endl;
	for (int i = 0; i < numberOfElements; i++) {
		cout << "#" << i << " : (" << PQ[i].index << ",";
		cout << PQ[i].value << ")\n";
	}
	cout << "\n\n";
}

//run Heapify on the min heap (maintains heap property for tree)
void PriorityQueue::MinHeapify(int i, int size){
	int leftChild = 2 * i + 1;
	int rightChild = 2 * i + 2;
	int smallest = i;

	if (leftChild < size && PQ[leftChild].value < PQ[i].value)
		smallest = leftChild;

	if (leftChild < size && PQ[rightChild].value < PQ[smallest].value)
		smallest = rightChild;
	if (smallest != i) {
		swap(PQ[i], PQ[smallest]);
		MinHeapify(smallest, size);
	}
}
