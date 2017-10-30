// Queue.h

#include "Process.h"

#ifndef QUEUE_H
#define QUEUE_H

class Queue {
  private:
    Process* head_;
    Process* tail_;
    int processCount_;
  public:
    // constructor
    Queue();
    // destructor
    ~Queue();

    // getters and setters
    Process* head();
    void setHead(Process* head);

    Process* tail();
    void setTail(Process* tail);

    unsigned int processCount();
    void setProcessCount(unsigned int processCount);

    // queue management
    Process* dequeue();
    void enqueue(Process* p);
};

// QUEUE_H
#endif
