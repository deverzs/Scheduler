#include "PCB.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
/*
Jason Luu and Zsuzsanna Dianovics
Assignment 3
Implementation file: PCB.cpp
*/

/*PCB constructor - creates a PCB object
	@params  id: int the id of the process
			 priority: int the priority of the process
       burst: int the burst time of the process
       burst_left: int the remaining burst time of the process (RR and Priority+RR)
       turn_around_time: int the turn-around time of the process
       waiting_time: int waiting time of the process
       isEqual: boolean variable to determine whether the process has the unique priority or not.
*/
PCB::PCB(string name, int priority, int burst, int burst_left, int turn_around_time, int waiting_time){
  this->name = name;
  this->priority = priority;
  this->burst = burst;
  this->burst_left = burst_left;
  this->turn_around_time = turn_around_time;
  this->waiting_time = waiting_time;
  isEqual = false;
  state = ProcState::NEW;
}
// get the size of the PCB table and return its size
int PCBTable::getSize(){
  return count;
}
// to add the new process into the PCB table
void PCBTable::add(PCB* process){
  PCBTable[count] = process;
  count++;
}
//to display the statistics of each task in the PCB table
void PCBTable::display(){
  for(int i = 0; i <count;i++){
      cout<<PCBTable[i]->name<<" turn-around time = ";
      cout<<PCBTable[i]->turn_around_time<<", waiting time = ";
      cout<<PCBTable[i]->waiting_time<<endl;
  }
}
