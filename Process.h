// Proccess.h

#ifndef PROCCESS_H
#define PROCCESS_H

#include <iostream>

class Process {
  private:
    int pid_;
    int arrivalTime_;
    int burstTime_;
    int priority_;

    unsigned int remainingTime_;  // how long the process has left

    float finishTime_;
    float waitTime_;
    float turnAroundTime_;
    float responseTime_;
    float contextSwitchCount_;

    Process* next_;
  public:
    // constructors
    Process();
    Process(int id, int at, int bt, int priority);
    Process(const Process &p);
    // destructor
    ~Process();

    // Getters and Setters
    int pid();
    void setPid(int id);
    
    int arrivalTime();
    void setArrivalTime(int at);
    
    int burstTime();
    void setBurstTime(int bt);

    int priority();
    void setPriority(int priority);

    int remainingTime();
    void setRemainingTime(int rt);

    float finishTime();
    void setFinishTime(float finishTime);

    float waitTime();
    void setWaitTime(float waitTime);

    float turnAroundTime();
    void setTurnAroundTime(float turnAroundTime);

    float responseTime();
    void setResponseTime(float responseTime);

    int contextSwitchCount();
    void setContextSwitchCount(int contextSwitchCount);

    Process* next();
    void setNext(Process* next);

    void print();
    // friends
    friend std::ostream &operator<<(std::ostream &os, const Process &rhs);
};

// PROCCESS_H
#endif
