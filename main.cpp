// Danny Cahoon
// Lab 2
// CSCI 3453


#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include "Process.h"
#include "Queue.h"
#include "PCB.h"

using namespace std;

int main (int argc, char *argv[]) {
  if (argc > 5) {
    fprintf(stderr, "usage:  \n");
    exit(1);
  }

  std::string fileInName = argv[1];
  std::string fileOutName = argv[2];
  std::ifstream dataIn;
  std::ofstream dataOut;

  dataIn.open(fileInName);
  std::string s;
  Queue queue;
  queue = Queue();
  Queue completedQueue = Queue();
  
  while(!dataIn.eof()) {
    // Read in from file
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    
    dataIn >> id;
    if (queue.tail() != nullptr && id == queue.tail()->pid()) {
      break;
    }

    dataIn >> arrivalTime;
    dataIn >> burstTime;
    dataIn >> priority;
    
    Process* p = new Process(id, arrivalTime, burstTime, priority);
    printf("Value of p = %p----------------------------------------\n", p);
    p->print();
    cout << "Process " << id << " created" << endl;
    queue.enqueue(p);
    cout << "Process added to queue" << endl;
    queue.head()->print();
    queue.tail()->print();
    cout << "Process printed----------------------------------------------------" << endl << endl;
    printf("number of processes = %d\n\n", queue.processCount());
  }
  dataIn.close();
  printf("number of processes = %d\n\n", queue.processCount());

  
  PCB pcb = PCB();

  switch(atoi(argv[3])) {
  case 0: {
    float avgBurst = 0.0;
    float avgWait = 0.0;
    float avgTurnAround = 0.0;
    float avgResponseTime = 0.0;
    int   numOfContextSwitch = 0;
    int   numOfProcesses = 0;
    dataOut.open(argv[2], std::ios::app);
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "************************************************* Scheduling algorithm: FCFS ************************************************" << endl;
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "|  pid  |  arrival  |  CPU-burst  |  Priority  |  Finish  |  Wait Time  |  Turnaround  |  Response Time  |  No. of Context  |\n"; 
    dataOut.close();
    Process* p = queue.head();
    while (p != nullptr || pcb.processCount() != 0) {
      cout << "get queue.head()" << endl;
      p = queue.head();
      cout << "pre queue management" << endl;
      cout << "pcb time - " << pcb.timeCounter() << endl;
      if (p != nullptr) {
        if (pcb.timeCounter() == p->arrivalTime()) {
          p = queue.dequeue();
          p->print();
          pcb.enqueue(p);
        }
      }
      cout << "post queue management" << endl;
      cout << p << endl;
      cout << pcb.processCount() << endl << endl;

      pcb.print();
      
      pcb.FCFS();
      
      if (pcb.processListHead()->remainingTime() == 0) {
        cout << "process counter == process burst time" << endl;
        Process* temp = pcb.dequeue();
        temp->print();
        temp->setFinishTime(pcb.timeCounter());
        temp->setWaitTime(pcb.timeCounter() - temp->arrivalTime() - temp->burstTime());
        temp->setTurnAroundTime(temp->waitTime() + temp->burstTime());
        temp->setResponseTime(temp->waitTime());
        dataOut.open(argv[2], std::ios::app);
        dataOut << *temp << "  |\n";
        dataOut.close(); 
        p = completedQueue.dequeue();
        ++numOfProcesses;
        avgBurst += temp->burstTime();
        avgWait += temp->waitTime();
        avgTurnAround += temp->turnAroundTime();
        avgResponseTime += temp->responseTime();
        numOfContextSwitch += temp->contextSwitchCount();
        delete temp;
      }
    }
    dataOut.open(argv[2], std::ios::app);
    dataOut << "Average CPU burst time = " << (avgBurst / numOfProcesses) << "ms" << endl;
    dataOut << "Average waiting time = " << (avgWait / numOfProcesses) << "ms" << endl;
    dataOut << "Average turn around time = " << (avgTurnAround / numOfProcesses) << "ms" << endl;
    dataOut << "Average response time = " << (avgResponseTime / numOfProcesses) << "ms" << endl;
    dataOut << "No. of context switches performmed = " << numOfContextSwitch << endl;
    dataOut.close();

    break;
  }
  case 1: {
    float avgBurst = 0.0;
    float avgWait = 0.0;
    float avgTurnAround = 0.0;
    float avgResponseTime = 0.0;
    int   numOfContextSwitch = 0;
    int   numOfProcesses = 0;
    dataOut.open(argv[2], std::ios::app);
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "************************************************* Scheduling algorithm: SRTF ************************************************" << endl;
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "|  pid  |  arrival  |  CPU-burst  |  Priority  |  Finish  |  Wait Time  |  Turnaround  |  Response Time  |  No. of Context  |\n"; 
    dataOut.close();
    Process* p = queue.head();

    while (p != nullptr || pcb.processCount() != 0) {
      cout << "~~~~~~~~~~~~~~~~~~~PCB TIME " << pcb.timeCounter() << "~~~~~~~~~~~~~~~~~~~~" << endl; 
      cout << "get queue.head()" << endl;
      p = queue.head();
      cout << "pre queue management" << endl;
      cout << "pcb time - " << pcb.timeCounter() << endl;
      if (p != nullptr) {
        if (pcb.timeCounter() >= p->arrivalTime()) {
          p = queue.dequeue();
          p->print();
          pcb.enqueue(p);
          pcb.print();
          if (pcb.processCount() > 1) {
            pcb.fixSRTFQueue();
          }
        }
      }
      cout << "post queue management" << endl;
      cout << p << endl;
      cout << pcb.processCount() << endl << endl;
      
      pcb.print();

      pcb.SRTF();

      if (pcb.processListHead()->remainingTime() == 0) {
        cout << "process count == process burst time" << endl;
        Process* temp = pcb.dequeue();
        temp->print();
        temp->setFinishTime(pcb.timeCounter());
        temp->setWaitTime(pcb.timeCounter() - temp->burstTime());
        temp->setTurnAroundTime(pcb.timeCounter() - temp->arrivalTime());
        temp->setResponseTime(temp->waitTime() - temp->arrivalTime());
        dataOut.open(argv[2], std::ios::app);
        dataOut << *temp << "  |\n"; 
        dataOut.close();
        ++numOfProcesses;
        avgBurst += temp->burstTime();
        avgWait += temp->waitTime();
        avgTurnAround += temp->turnAroundTime();
        avgResponseTime += temp->responseTime();
        numOfContextSwitch += temp->contextSwitchCount();
        delete temp;
      }
      pcb.print();
    }

    dataOut.open(argv[2], std::ios::app);
    dataOut << "Average CPU burst time = " << (avgBurst / numOfProcesses) << "ms" << endl;
    dataOut << "Average waiting time = " << (avgWait / numOfProcesses) << "ms" << endl;
    dataOut << "Average turn around time = " << (avgTurnAround / numOfProcesses) << "ms" << endl;
    dataOut << "Average response time = " << (avgResponseTime / numOfProcesses) << "ms" << endl;
    dataOut << "No. of context switches performmed = " << numOfContextSwitch << endl;
    dataOut.close();
    break;
  }
  case 2: {
    if (argc != 5) {
      fprintf(stderr, "A time quantum must be included to use the round robin scheduling algorithm");
      exit(1);
    }
    float avgBurst = 0.0;
    float avgWait = 0.0;
    float avgTurnAround = 0.0;
    float avgResponseTime = 0.0;
    int   numOfContextSwitch = 0;
    int   numOfProcesses = 0;
    dataOut.open(argv[2], std::ios::app);
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "****************************************** Scheduling algorithm: Round Robin ************************************************" << endl;
    dataOut << "******************************************* ( No. of tasks = " << queue.processCount() << "  Quantum = " << atoi(argv[4]) << ") ************************************************" << endl;
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "|  pid  |  arrival  |  CPU-burst  |  Priority  |  Finish  |  Wait Time  |  Turnaround  |  Response Time  |  No. of Context  |\n"; 
    dataOut.close();

    Process* p = queue.head();

    int timeSinceContextSwitch = 0;
    while (p != nullptr || pcb.processCount() != 0) {
      cout << "~~~~~~~~~~~~~~~~~~~PCB TIME " << pcb.timeCounter() << "~~~~~~~~~~~~~~~~~~~~" << endl; 
      cout << "get queue.head()" << endl;
      p = queue.head();
      cout << "pre queue management" << endl;
      cout << "pcb time - " << pcb.timeCounter() << endl;
      if (p != nullptr) {
        if (pcb.timeCounter() >= p->arrivalTime()) {
          p = queue.dequeue();
          p->print();
          pcb.enqueue(p);
          pcb.print();
        }
      }
      cout << "post queue management" << endl;
      cout << p << endl;
      cout << pcb.processCount() << endl << endl;
      
      pcb.print();

      pcb.RR(atoi(argv[4]), timeSinceContextSwitch);

      ++timeSinceContextSwitch;
      if (pcb.processListHead()->remainingTime() == 0) {
        cout << "process count == process burst time" << endl;
        Process* temp = pcb.dequeue();
        temp->print();
        temp->setFinishTime(pcb.timeCounter());
        temp->setWaitTime(pcb.timeCounter() - temp->arrivalTime() - temp->burstTime());
        temp->setTurnAroundTime(pcb.timeCounter() - temp->arrivalTime());
        temp->setResponseTime(temp->waitTime() - temp->arrivalTime());
        dataOut.open(argv[2], std::ios::app);
        dataOut << *temp << "  |\n"; 
        dataOut.close();
        ++numOfProcesses;
        avgBurst += temp->burstTime();
        avgWait += temp->waitTime();
        avgTurnAround += temp->turnAroundTime();
        avgResponseTime += temp->responseTime();
        numOfContextSwitch += temp->contextSwitchCount();
        timeSinceContextSwitch = 0;
      }
      pcb.print();
      cout << "tscs = " << timeSinceContextSwitch << endl;
      if (atoi(argv[4]) == timeSinceContextSwitch) {
        timeSinceContextSwitch = 0;
      }
    }
    dataOut.open(argv[2], std::ios::app);
    dataOut << "Average CPU burst time = " << (avgBurst / numOfProcesses) << "ms" << endl;
    dataOut << "Average waiting time = " << (avgWait / numOfProcesses) << "ms" << endl;
    dataOut << "Average turn around time = " << (avgTurnAround / numOfProcesses) << "ms" << endl;
    dataOut << "Average response time = " << (avgResponseTime / numOfProcesses) << "ms" << endl;
    dataOut << "No. of context switches performmed = " << numOfContextSwitch << endl;
    dataOut.close();
    break;
  }
  case 3: {
    float avgBurst = 0.0;
    float avgWait = 0.0;
    float avgTurnAround = 0.0;
    float avgResponseTime = 0.0;
    int   numOfContextSwitch = 0;
    int   numOfProcesses = 0;    
    dataOut.open(argv[2], std::ios::app);
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "**************************************** Scheduling algorithm: Preemptive Priority ******************************************" << endl;
    dataOut << "*****************************************************************************************************************************" << endl;
    dataOut << "|  pid  |  arrival  |  CPU-burst  |  Priority  |  Finish  |  Wait Time  |  Turnaround  |  Response Time  |  No. of Context  |\n"; 
    dataOut.close();
    Process* p = queue.head();

    while (p != nullptr || pcb.processCount() != 0) {
      cout << "~~~~~~~~~~~~~~~~~~~PCB TIME " << pcb.timeCounter() << "~~~~~~~~~~~~~~~~~~~~" << endl; 
      cout << "get queue.head()" << endl;
      p = queue.head();
      cout << "pre queue management" << endl;
      cout << "pcb time - " << pcb.timeCounter() << endl;
      if (p != nullptr) {
        if (pcb.timeCounter() >= p->arrivalTime()) {
          p = queue.dequeue();
          p->print();
          pcb.PPEnqueue(p);
          cout << "PPENQUEUE COMPLETE" << endl;
          pcb.print();
        }
      }
      cout << "post queue management" << endl;
      cout << p << endl;
      cout << pcb.processCount() << endl << endl;
      
      pcb.print();

      pcb.PP();

      if (pcb.processListHead()->remainingTime() == 0) {
        cout << "process count == process burst time" << endl;
        Process* temp = pcb.dequeue();
        temp->print();
        temp->setFinishTime(pcb.timeCounter());
        temp->setWaitTime(pcb.timeCounter() - temp->arrivalTime() - temp->burstTime());
        temp->setTurnAroundTime(pcb.timeCounter() - temp->burstTime() - temp->arrivalTime());
        dataOut.open(argv[2], std::ios::app);
        dataOut << *temp << "  |\n"; 
        dataOut.close();
        ++numOfProcesses;
        avgBurst += temp->burstTime();
        avgWait += temp->waitTime();
        avgTurnAround += temp->turnAroundTime();
        avgResponseTime += temp->responseTime();
        numOfContextSwitch += temp->contextSwitchCount();
        delete temp;
      }
      pcb.print();
    }
    dataOut.open(argv[2], std::ios::app);
    dataOut << "Average CPU burst time = " << (avgBurst / numOfProcesses) << "ms" << endl;
    dataOut << "Average waiting time = " << (avgWait / numOfProcesses) << "ms" << endl;
    dataOut << "Average turn around time = " << (avgTurnAround / numOfProcesses) << "ms" << endl;
    dataOut << "Average response time = " << (avgResponseTime / numOfProcesses) << "ms" << endl;
    dataOut << "No. of context switches performmed = " << numOfContextSwitch << endl;
    dataOut.close();
    break;
  }
  default:
    fprintf(stderr, "%d must be between 0 and 3\n", atoi(argv[3]));
    exit(1);
  }
  return 0;
}
