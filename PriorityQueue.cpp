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
	//	cout << "called dequeue" << endl;
	//	print();
	//	cout << endl << "size " << size() << endl;
	if (empty())
		return false;
	else if (size() == 1) {
		size_--;
		return true;
	}
	heap_[1] = heap_[size_]; // replace root with bottom right most leaf node
	size_--; // decrement size as that part of the array should now be inaccessible

	//keep switching root with largest child

	int cur = 1, lastCur = 0;
	do {
		lastCur = cur;
		if (size_ >= 2*cur + 1) { // has two child nodes
			if (std::max(heap_[2*cur], heap_[2*cur+1]) > heap_[cur]) {
				int maxChild = heap_[2 * cur] > heap_[2 * cur + 1] ? 2 * cur : 2 * cur + 1;
				int temp = heap_[maxChild];
				heap_[maxChild] = heap_[cur];
				heap_[cur] = temp;
				cur = maxChild;
			}
		}
		else if(size_ >= 2*cur) { // only has a left child
			if (heap_[2*cur] > heap_[cur]) {
				int temp = heap_[cur];
				heap_[cur] = heap_[cur*2];
				heap_[cur*2] = temp;
				cur = 2*cur;
			}
		}

	} while (lastCur != cur);



//cur = 1;
//	while (std::max(heap_[2*cur], heap_[2*cur+1]) > heap_[cur] && cur >= size_) {
//		int maxChild = heap_[2*cur] > heap_[2*cur+1]? 2*cur : 2*cur+1;
//		int temp = heap_[maxChild];
//		heap_[maxChild] = heap_[cur];
//		heap_[cur] = temp;
//		cur = maxChild;
//	}
//	print();
	return true;
//	else if (size_ <= 3) { // case where after removing root, we won't have multiple child nodes
//			size_--;
//			if ()
//
//			return true;
//		}
}

DataType PriorityQueue::max() const {
	return heap_[1];
}

bool PriorityQueue::empty() const {
	return size_ == 0;
}

bool PriorityQueue::full() const {
	return size_ == capacity_;
}

unsigned int PriorityQueue::size() const {
	return size_;
}

void PriorityQueue::print() const {
	cout << "[";
	for (int i = 1; i <= size_; i++) {
		cout << heap_[i];
		if (i != size_)
			cout << ", ";
	}
	cout << "]";
}
