#pragma once
#include "PCB.h"
/*
Jason Luu and Zsuzsanna Dianovics
Assignment 1
Header file: ReadyQueue.h
Header file for ReadyQueue object
This object creats a priority queue that removes objects
based on the priority of the PCB object
*/

/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here uch that the process with the highest priority
 * can be selected next.
 */
class ReadyQueue {
public:

	// add a PCB representing a process into the ready queue.
	void add(PCB* pcbPtr);

	// remove and return the PCB with the highest priority from the queue
	PCB* removeHighest();

	// Returns the number of elements in the queue.
	int size();

	// Prints the queue contents to standard output based on the order of FCFS.
	void display();
	
	//constructor
	ReadyQueue();
	
	//debugging function to check how often the queue is empty
	int howOftenEmpty();
	
	
private:

	//Utility functions for priority queue
	void swap(int,int);		//swap the objects
	void reheapify(); 		//re-arrange after remove from the ReadyQueue
	int getSmallerchild(int);//return the location of the smaller child
	void trickleup(); 		// trickle up after adding at the rear
	int getParent(int); 	//return the parent location given the child location
	bool even(int); 		//even or odd?

	PCB* Q[30]; 			//an array holding PCB elements.
	int count; 				//how many elements are in the ReadyQueue
	int emptyQ;				//number of times queue is empty
	
};