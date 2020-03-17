#pragma once

/*
Jason Luu and Zsuzsanna Dianovics
Assignment 1
PCB.h

Header file: PCB object
This object has an enum class representing the process state
This object needs an ID and a Priority to be created
*/

//Enum class of process state
enum class ProcState {NEW, READY, RUNNING, WAITING, TERMINATED};

/* 
Process control block(PCB) is a data structure representing a process in the system.
A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
*/
class PCB {
public:
    // The unique process ID
	unsigned int id;
    // The priority of a process valued between 1-50. Larger number represents higher priority
	unsigned int priority;
	// The current state of the process.
	// A process in the ReadyQueue should be in READY state
	ProcState state;
	//Tracking how often object removed from queue
	int removed;
	//Tracking how often added to the queue
	int added;
	//constructor
	PCB(int,int);
	
};

/*
Header and implementation for PCBTable

PCBTable is an array of PCB object pointers 
*/
class PCBTable {
 public:
  PCB* PCBTable[30]; //an array for PCB table, holds 30 pointers 
  
};
