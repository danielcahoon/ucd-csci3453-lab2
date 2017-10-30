Lab 2
Danny Cahoon
CSCI3453 001

To run the program first run make while in the directory with the Makefile to create the executable file.
This program is written to be a command line tool. The parameters are as follows:
  ./ucd-csci3453-lab2 inputFileName outputFileName cpuSchedulerChoice

For RR a time quantum must be specified as follows for a time quantum of 4:
  ./ ucd-csci3453-lab2 inputFile outputFile 2 4

A sample run can be done as follows to run through each of the alogrithms:

  -make test4
  -make test41
  -make test42
  -make test43

Each of the above will run the algorithms in order from FCFS to PP. make test42 does Round Robin with a time quantum of 4.
It takes input from the file input4 and puts the results in output4.
