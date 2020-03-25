#include "PCB.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
/*
Jason Luu and Zsuzsanna Dianovics
Assignment 1
Implementation file: PCB.cpp
*/

/*PCB constructor - creates a PCB object
	@params  id: int the id of the process
			 priority: int the priority of the process
*/
PCB::PCB(string name, int priority, int burst, int turn_around_time, int waiting_time){
  this->name = name;
  this->priority = priority;
  this->burst = burst;
  this->turn_around_time = turn_around_time;
  this->waiting_time = waiting_time;
  state = ProcState::NEW;
}
int PCBTable::getSize(){
  return count;
}
void PCBTable::add(PCB* process){
  PCBTable[count] = process;
  count++;
}
void PCBTable::update(PCB* process){
  PCBTable[count] = process;
  count--;
}
void PCBTable::display(){
  for(int i = 0; i <count;i++){
      cout<<PCBTable[i]->name<<" turn-around time = ";
      cout<<PCBTable[i]->turn_around_time<<", waiting time = ";
      cout<<PCBTable[i]->waiting_time<<endl;
  }
}


