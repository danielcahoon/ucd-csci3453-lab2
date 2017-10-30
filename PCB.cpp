#include <iostream>

#include "Process.h"
#include "PCB.h"

using namespace std;

// constructor
PCB::PCB() : processCount_(0), timeCounter_(0), processListHead_(nullptr), processListTail_(0){ }

// destrutor
PCB::~PCB() { }

// setters and getters 
int PCB::processCount() {
  return processCount_;
}

void PCB::PCB::setProcessCount(int processCount) {
  processCount_ = processCount;
}

float PCB::timeCounter() {
  return timeCounter_;
}

void PCB::setTimeCounter(float timeCounter) {
  timeCounter_ = timeCounter;
}

Process* PCB::processListHead() {
  return processListHead_;
}

void PCB::setProcessListHead(Process* processListHead) {
  processListHead_ = processListHead;
}

Process* PCB::processListCurr() {
  return processListCurr_;
}

void PCB::setProcessListCurr(Process* processListCurr) {
  processListCurr_ = processListCurr;
}

Process* PCB::processListTail() {
  return processListTail_;
}

void PCB::setProcessListTail(Process* processListTail) {
  processListTail_ = processListTail;
}

// PCB managment
void PCB::enqueue(Process* p) {
  if (processCount_ == 0) {
    processListHead_ = p;
    processListCurr_ = p;
    processListTail_ = p;
    ++processCount_;
    return;
  }
  if (processListHead_->next() == nullptr) {
    processListHead_->setNext(p);
    processListCurr_->setNext(p);
  }
  processListTail_->setNext(p);
  processListTail_ = p;
  processListTail_->setNext(processListHead_);
  /*
  Process* curr = processListHead_;
  Process* next = processListHead_->next();
  if (p->remainingTime() < curr->remainingTime()) {
    p->setNext(processListHead_);
    processListTail_->setNext(p);
  } else if (p->remainingTime() > curr->remainingTime() && p->remainingTime() < next->remainingTime()) {
    curr->setNext(p);
    p->setNext(next);
  } else {
    next->setNext(p);
    p->setNext(processListHead_);
    processListTail_ = p;
  }
  */
  ++processCount_;
}
  
Process* PCB::dequeue() {
  if (processCount_ == 0) {
    return nullptr;
  }
  Process* p = processListHead_;
  
  cout << processListHead_ << endl;
  cout << processListHead_->next() << endl;

  cout << processListTail_ << endl;
  cout << processListTail_->next() << endl;

  processListHead_ = processListHead_->next();
  processListCurr_ = processListHead_;
  processListTail_->setNext(processListHead_);
  --processCount_;
  if (processCount_ < 2) {
    processListTail_->setNext(nullptr);
    processListTail_ = processListHead_;
  }
  p->setNext(nullptr);
  return p;
}

void PCB::print() {
  cout << endl << "********** PCB Print ********" << endl;
  cout << "List Head - " << processListHead_ << endl;
  cout << "List Curr - " << processListCurr_ << endl;
  cout << "List Tail - " << processListTail_ << endl;
  Process* temp = processListCurr_;
  processListCurr_ = processListHead_;
  for (int i = 0; i < processCount_; ++i, processListCurr_ = processListCurr_->next()) {
    processListCurr_->print();
  }
  cout << "*****************************" << endl << endl;
  processListCurr_ = temp;
}

void PCB::FCFS() {
  ++timeCounter_;
  processListHead_->setRemainingTime((processListHead_->remainingTime()) - 1);
}

void PCB::SRTF() {
  ++timeCounter_;
  processListHead_->setRemainingTime((processListHead_->remainingTime()) - 1);
  
}

void PCB::fixSRTFQueue() {
  Process* temp = processListHead_->next();
  if (temp == nullptr) {
    return;
  }
  while (temp != processListHead_) {
    if(processListCurr_->remainingTime() > temp->remainingTime()) {
      processListCurr_ = temp;
      temp = temp->next();
    } else {
      temp = temp->next();
    }
  }
  if (processListCurr_ != processListHead_) {
   this->timeCounter_ += 0.5;
   processListHead_->setContextSwitchCount(processListHead_->contextSwitchCount() + 1);
   while (processListCurr_ != processListHead_) {
     processListHead_ = processListHead_->next();
   }
   while (processListTail_->next() != processListHead_) {
     processListTail_ = processListTail_->next();
   }
  }
   processListHead_->setResponseTime(this->timeCounter_ - processListHead_->arrivalTime());
}

void PCB::RR(int timeQuantum, int timeSinceContextSwitch) {
  ++timeCounter_;
  ++timeSinceContextSwitch;
  processListHead_->setRemainingTime((processListHead_->remainingTime()) - 1);
  if (timeQuantum == timeSinceContextSwitch) {
    timeCounter_ += 0.5;
    if (processListHead_->contextSwitchCount() == 0) {
      processListHead_->setResponseTime(timeCounter_);
    }
    processListHead_->setContextSwitchCount(processListHead_->contextSwitchCount() + 1);
    processListHead_ = processListHead_->next();
    processListTail_ = processListTail_->next();
  }
}

void PCB::PP() {
  ++timeCounter_;
  processListHead_->setRemainingTime((processListHead_->remainingTime()) - 1);
}

void PCB::PPEnqueue(Process* p) {
  cout << "PPENQUEUE START" << endl;
  p->print();
  if (processCount_ == 0) {
    processListHead_ = p;
    processListCurr_ = p;
    processListTail_ = p;
    ++processCount_;
    return;
  }
  Process* curr = processListHead_;
  Process* next = processListHead_->next();
  if(next == nullptr) {
    if (p->priority() < curr->priority()) {
      timeCounter_ += 0.5;
      processListHead_->setContextSwitchCount(processListHead_->contextSwitchCount() + 1);
      processListHead_ = processListHead_->next();
      processListCurr_ = processListHead_;
      p->setNext(processListHead_);
      processListTail_->setNext(p);
    } else {
      processListHead_->setNext(p);
      processListCurr_->setNext(p);
      processListTail_->setNext(p);
      processListTail_ = p;
      processListTail_->setNext(processListHead_);
    }
    ++processCount_;
    return;
  }

  cout << "p = " << p->priority() << endl;
  cout << "curr = " << curr->priority() << endl;
  while (curr != processListTail_) {
    cout << "curr = " << curr << endl;
    cout << "tail = " << processListTail_ << endl;
    cout << "curr < p " << curr->priority() << " < " << p->priority() << endl;
    if (p->priority() < curr->priority()) {
      if (curr == processListHead_) {
        timeCounter_ += 0.5;
      }
      processListHead_->setContextSwitchCount(processListHead_->contextSwitchCount() + 1);
      p->setNext(processListHead_);
      processListHead_ = p;
      processListTail_->setNext(p);
      break;
    } else {
      curr = curr->next();
      next = next->next();
      cout << "p >= curr" << endl;
      cout << "curr = " << curr << endl;
      cout << "tail = " << processListTail_ << endl;
      if (curr == processListTail_) {
        processListTail_->setNext(p);
        processListTail_ = p;
        processListTail_->setNext(processListHead_);
      }
    }
  }
  ++processCount_;
}
