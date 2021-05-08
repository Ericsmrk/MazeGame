#pragma once
#include "Queue.h"

struct MyData {
	int index;
	double value;
};

class PriorityQueue{
public:
	PriorityQueue() : capacity(0), numberOfElements(0), PQ(nullptr) {}
	PriorityQueue(int c);
	~PriorityQueue() { delete[] PQ; }
	int GetNumberOfElements() { return numberOfElements; }
	void PrintNumberOfElements();

	bool IsEmpty() { return numberOfElements == 0; }
	bool IsFull() { return numberOfElements == capacity; };
	int GetParent(int child);
	int GetLeftChild(int parent) { return (2 * parent + 1); }
	int GetRightChild(int parent) { return (2 * parent + 2); };
	void Push(int index, double value);
	void IncreaseCapacityThenPush(int index, double value);
	MyData Pop();
	void DecreaseKey(int index, double value);
	void BuildMinHeap();
	void DisplayPQ();
	void PopAndPrint(PriorityQueue* PQ);
	int getCapacity() { return capacity; }

private:
	void MinHeapify(int i, int size);
	int capacity;
	int numberOfElements;
	MyData* PQ;
};

