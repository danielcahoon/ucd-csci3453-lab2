CXX      := g++
CXXFLAGS := -std=c++11

ucd-csci3453-lab2: PCB.o Queue.o Process.o main.o 
	    $(CXX) $(CXXFLAGS)  -o ucd-csci3453-lab2 PCB.o Queue.o Process.o main.o

main.o: main.cpp Process.h Queue.h PCB.h
	    $(CXX) $(CXXFLAGS) -c -o main.o main.cpp

Proccess.o: Process.h Process.cpp
			$(CXX) $(CXXFLAGS) -c -o Process.o Process.cpp

Queue.o: Queue.h Queue.cpp Process.h 
			$(CXX) $(CXXFLAGS) -c -o Queue.o Queue.cpp

PCB.o: PCB.h PCB.cpp Process.h 
			$(CXX) $(CXXFLAGS) -c -o PCB.o PCB.cpp

.PHONY: clean test

clean:
	    rm -f output10 output4 PCB.o Queue.o Process.o main.o ucd-csci3453-lab2

test: ucd-csci3453-lab2
	    ./ucd-csci3453-lab2 input10 output10 0

test4: ucd-csci3453-lab2
			./ucd-csci3453-lab2 input4 output4 0

test41: ucd-csci3453-lab2
			./ucd-csci3453-lab2 input4 output4 1

test42: ucd-csci3453-lab2
			./ucd-csci3453-lab2 input4 output4 2 4

test43: ucd-csci3453-lab2
			./ucd-csci3453-lab2 input4 output4 3
