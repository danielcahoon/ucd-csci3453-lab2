// Process.cpp
#include <iostream>
#include <iomanip>
#include <stdio.h>

#include "Process.h"

Process::Process(): pid_(0), arrivalTime_(0), burstTime_(0), priority_(0) {}

Process::Process(int id, int at, int bt, int priority) {
  pid_ = id;
  arrivalTime_ = at;
  burstTime_ = bt;
  priority_ = priority;
  remainingTime_ = bt;
  finishTime_ = 0;
  waitTime_ = 0;
  turnAroundTime_ = 0;
  responseTime_ = 0;
  contextSwitchCount_ = 0;
  next_ = nullptr;
}

Process::~Process() {}

// Getters and Setters
int Process::pid() {
  return pid_;
}

void Process::setPid(int id) {
  pid_ = id;
}

int Process::arrivalTime() {
  return arrivalTime_;
}

void Process::setArrivalTime(int at) {
  arrivalTime_ = at;
}

int Process::burstTime() {
  return burstTime_;
}

void Process::setBurstTime(int bt) {
  burstTime_ = bt;
}

int Process::priority() {
  return priority_;
}

void Process::setPriority(int priority) {
  priority_ = priority;
}

int Process::remainingTime() {
  return remainingTime_;
}

void Process::setRemainingTime(int rt) {
  remainingTime_ = rt;
}

float Process::finishTime() {
  return finishTime_;
}

void Process::setFinishTime(float finishTime) {
  finishTime_ = finishTime;
}

float Process::waitTime() {
  return waitTime_;
}

void Process::setWaitTime(float waitTime) {
  waitTime_ = waitTime;
}

float Process::turnAroundTime() {
  return turnAroundTime_;
}

void Process::setTurnAroundTime(float turnAroundTime) {
  turnAroundTime_ = turnAroundTime;
}

float Process::responseTime() {
  return responseTime_;
}

void Process::setResponseTime(float responseTime) {
  responseTime_ = responseTime;
}

int Process::contextSwitchCount() {
  return contextSwitchCount_;
}

void Process::setContextSwitchCount(int contextSwitchCount) {
  contextSwitchCount_ = contextSwitchCount;
}

Process* Process::next() {
  return next_;
}

void Process::setNext(Process* next) {
  next_ = next;
}

void Process::print() {
  printf("pid - %d | at - %d | bt - %d | pr - %d | rt - %u | this - %p | next - %p\n", pid_, arrivalTime_, burstTime_, priority_, remainingTime_, this, next_);
}

// friends
std::ostream& operator<<(std::ostream &os, const Process &rhs) {
  os << "|  " 
     << std::setw(3) << rhs.pid_ << "  |  "
     << std::setw(7) << rhs.arrivalTime_ << "  |  "
     << std::setw(9) << rhs.burstTime_ << "  |  "
     << std::setw(8) << rhs.priority_ << "  |  "
     << std::setw(6) << rhs.finishTime_ << "  |  " 
     << std::setw(9) << rhs.waitTime_ << "  |  " 
     << std::setw(10) << rhs.turnAroundTime_ << "  |  "
     << std::setw(13) << rhs.responseTime_ << "  |  "
     << std::setw(14) << rhs.contextSwitchCount_;
  return os;
}
