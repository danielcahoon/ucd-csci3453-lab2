// PCB.h

#ifndef PCB_H
#define PCB_H

class PCB {
  private:
  int processCount_;
  float timeCounter_;

  Process* processListHead_;
  Process* processListCurr_;
  Process* processListTail_;

  public:
    // constructor
    PCB();
    // destructor
    ~PCB();

    // getters and setters
    int processCount();
    void setProcessCount(int processCount);

    float timeCounter();
    void setTimeCounter(float timeCounter);

    Process* processListHead();
    void setProcessListHead(Process* processListHead);

    Process* processListCurr();
    void setProcessListCurr(Process* processListCurr);

    Process* processListTail();
    void setProcessListTail(Process* processListTail);

    // PCB managment
    void enqueue(Process* p);
    Process* dequeue();
    void sort();
    void print();

    // CPU Scheduler methods
    void FCFS();
    void SRTF();
    void fixSRTFQueue();
    void RR(int timeQuantum);
    void PP();
};


// PCB_H
#endif
