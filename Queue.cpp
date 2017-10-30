// Queue.cpp

#include <iostream>

#include "Queue.h"

// constructor
Queue::Queue() {
  head_ = nullptr;
  tail_ = nullptr;
  processCount_ = 0;
}

// destructor
Queue::~Queue() {}

// getters and setters
Process* Queue::head() {
  return head_;
}

void Queue::setHead(Process* head) {
  head_ = head;
}

Process* Queue::tail() {
  return tail_;
}

void Queue::setTail(Process* tail) {
  tail_ = tail;
}

unsigned int Queue::processCount() {
  return processCount_;
}

void Queue::setProcessCount(unsigned int processCount) {
  processCount_ = processCount;
}

// Queue management
Process* Queue::dequeue() {
  if (processCount_ == 0) {
    return nullptr;
  }
  Process* p = head_;
  Process* temp = head_->next();
  head_ = temp;
  --processCount_;
  p->setNext(nullptr);
  return p;
}

void Queue::enqueue(Process* p) {
  if (processCount_ == 0) {
    head_ = p;
    tail_ = p;
    ++processCount_;
    return;
  }
  if (head_->next() == nullptr) {
    head_->setNext(p);
  }
  tail_->setNext(p);
  tail_ = p;
  ++processCount_;
}
