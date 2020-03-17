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
PCB::PCB(int id, int priority){
  this->id = id;
  this->priority = priority;
  state = ProcState::NEW;
}



