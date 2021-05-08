//Lab 9 CSCI 115 Spring 2021
//Eric Smrkovsky
#include <iostream>
#include "Queue.h"
using namespace std;

Queue::Queue(){
	capacity = 0;
	front = size = 0;
	rear = capacity -1;
	q = nullptr;
	insertCount = 0;
	dequeueCount = 0;
}

Queue::Queue(int capacity1){
	capacity = capacity1;
	front = size = 0;
	rear = capacity -1;
	q = new MyType[capacity];
	insertCount = 0;
	dequeueCount = 0;
}

Queue::~Queue(){
	delete[] q;
}

//Returns true if the Queue has reached it's capacity
bool Queue::IsFull(){
	return (size == capacity);
}

//Returns true if the Queue is empty
bool Queue::IsEmpty(){
	return ( size == 0);
}

//Enqueue to the front
void Queue::Enqueue(MyType x){
	if (not IsFull()) {
		insertCount++;
		rear = (rear + 1) % capacity;
		q[rear] = x;
		size++;
	}
}

int Queue::numInserted() {
	return insertCount;
}

int Queue::numDequeued() {
	return dequeueCount;
}

//Dequeue fron the back
MyType Queue::DequeueBack() {
	if (IsEmpty())
		return INT_MIN;
	MyType item = q[rear];
	front = (front + 1) % capacity;
	size--;
	return item;
}

//Dequeue fron the front
MyType Queue::Dequeue(){
	if (IsEmpty())
		return INT_MIN;
	MyType item = q[front];
	front = (front + 1) % capacity;
	size--;	
	return item;
}

//get the front of queue
MyType Queue::Front(){
	if (IsEmpty())
		return INT_MIN;
	return q[front];
}

//get the rear of queue
MyType Queue::Rear(){
	if (IsEmpty())
		return INT_MIN;
	return q[rear];
}


//Display all elements in order that should be dequeued
void Queue::DisplayQueue() {
	if (IsEmpty())
		cout << "\nEmpty Queue!!\n";
	cout << "Size of queue: " << size << endl;
	for (int i = 0; i < size; i++)
		cout << "Element: " << q[(front + i) % capacity] << " at position " << i << endl;
	cout << endl;
}

//Display all elements in q sorted
void Queue::DisplayAll(){
	if (IsEmpty())
		cout << "\nEmpty Queue!!\n";
	cout << "Capacity of queue: " << capacity << endl;
	for (int i = 0; i < capacity; i++)
		cout << "Element: " << q[i] << " at position " << i << endl;
	cout << endl;
}
