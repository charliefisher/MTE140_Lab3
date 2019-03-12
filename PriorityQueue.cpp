#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "PriorityQueue.hpp"
typedef PriorityQueue::DataType DataType;  // for simplicity

using namespace std;

PriorityQueue::PriorityQueue(unsigned int capacity) {
	capacity == 0 ? 16:capacity;
	size_ = 0;
	capacity_ = capacity;
	heap_ = new DataType[capacity_+1];
}

PriorityQueue::~PriorityQueue() {
	delete[] heap_;
	heap_ = NULL;
}

// Enqueues "val" into the priority queue. Returns false if failed, true
// otherwise. Assume no duplicate entries will be entered.
bool PriorityQueue::enqueue(DataType val) {
	if (full())
		return false;
	size_++;
	heap_[size_] = val;
	int cur = size_;
	while(heap_[cur/2] < heap_[cur] && cur != 1) {
		int temp = heap_[cur/2];
		heap_[cur/2] = heap_[cur];
		heap_[cur] = temp;
		cur /= 2;
	}
	return true;
}
// Dequeues the top element with the maximum value (priority) and rearranges
// the resulting heap. Returns false if failed, true otherwise.
bool PriorityQueue::dequeue() {
	if (empty())
		return false;
	heap_[1] = heap_[size_];
	size_--;
	int cur = 1;
	while (std::max(heap_[2*cur], heap_[2*cur+1]) > heap_[cur] && cur >= size_) {
		int maxChild = heap_[2*cur] > heap_[2*cur+1]? 2*cur : 2*cur+1;
		int temp = heap_[maxChild];
		heap_[maxChild] = heap_[cur];
		heap_[cur] = temp;
		cur = maxChild;
	}
	return true;
}

// Returns the max element of the priority queue, but does not remove it.
DataType PriorityQueue::max() const {
	return heap_[1];
}
// Returns true if the priority queue is empty; false otherwise.
bool PriorityQueue::empty() const {
	return size_ == 0;
}
// Returns true if the priority queue is full; false otherwise.
bool PriorityQueue::full() const {
	return size_ == capacity_;
}
// Returns the number of elements in the priority queue.
unsigned int PriorityQueue::size() const {
	return size_;
}
// Print the contents of the priority queue.
void PriorityQueue::print() const {
	cout << "[";
	for (int i = 1; i <= size_; i++) {
		cout << heap_[i];
		if (i != size_ + 1)
			cout << ", ";
	}
	cout << "]";

//	int depth = (int)ceil(pow(capacity_+1,0.5));
//	for (int i = 1; i <= size_; i++) {
//
//
//		int numLevel = (int)round(pow(2.0,i * 1.0));
//		for(int j = 0; j < numLevel; j++) {
//			cout << heap_[i];
//			if (j != numLevel)
//				cout << "\t";
//		}
//		cout << endl;
//	}
}
