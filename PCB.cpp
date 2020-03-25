#include "PCB.h"
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



