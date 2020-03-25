#include <iostream>
#include "ReadyQueue_priority.h"

/*
Jason Luu and Zsuzsanna Dianovics
Assignment 1
Implementation file: ReadyQueue.cpp
Implementation file for ReadyQueue object
This object creats a priority queue that removes objects
based on the priority of the PCB object
*/

using namespace std;

//constructor
ReadyQueue::ReadyQueue(){
  count = 0; 		//no PCB elements yet!
}

/*
size: returns the size of the queue
	@params  none
	@return  int that is the size
*/
int ReadyQueue::size(){
  return count;
}

/*
add: add PCB element to a right place in the ReadyQueue 
	@params  PCB pointer
	@return  none
*/
void ReadyQueue::add(PCB* pcbPtr){

  Q[count] = pcbPtr;
  count++;
  pcbPtr->state = ProcState::READY; //change its state to READY when it is in the ReadyQueue
  pcbPtr->added +=1;
  trickleup(); //move the PCB elements to the right place
}

/*
howOftenEmpty: Check how many times the ReadyQueue is empty
	@params  none
	@return  int that is how often the queue is empty
*/
int ReadyQueue::howOftenEmpty(){
  return emptyQ;
} 


/* removeHighest: remove element that has the highest priority number 
	and re-arrange the oder of the ReadyQueue
	@param none
	@return  PCB pointer
	@calls reheapify()
*/
PCB* ReadyQueue::removeHighest(){
  PCB* removedElem;
  // if the queue is empty
  if(count<=0){
    emptyQ++;
    return nullptr;
  }
  else{
    Q[0]->state = ProcState::RUNNING; //change its state to RUNNING when it is removed from ReadyQueue
    removedElem = Q[0];
    reheapify();
    Q[0]->removed += 1;
    return removedElem;
  }
 
}

/* display: to display the printQueue in the order of FCFS
	@param none
	@return none
*/
void ReadyQueue::display(){
  //cout << "Display Processes in Ready Queue:" <<endl;
  for(int i = 0; i <= count - 1; i++){
    cout<<"Proc ID = " <<Q[i]->id <<", priority = " <<Q[i]->priority<<endl;
  }
}

/* swap: exchange PCB objects
	@param loc1 int first object to swap
			loca2 int the second object
	@return none
*/
void ReadyQueue::swap(int loc1, int loc2){
  PCB* temp; //local variable for holding the temporary PCB elem for swapping
  temp = Q[loc1];
  Q[loc1] = Q[loc2];
  Q[loc2] = temp;
}

/* trickleup: to make the last job trickle up to the right location
	@param none
	@return none
	@calls swap
*/
//PUPORSE: 
void ReadyQueue::trickleup(){
  int lastElem = count-1; 			//the last elem location
  bool didSwap = true; 				//local variable to determine whether we did swap or not.
  while (lastElem > 0 && didSwap == true){
<<<<<<< HEAD:ReadyQueue_sjf.cpp
    if(Q[lastElem]->burst < Q[getParent(lastElem)]->burst){
      swap(getParent(lastElem),lastElem);
      if(Q[lastElem]->burst == Q[lastElem - 1]->burst){
=======
    if(Q[lastElem]->priority > Q[getParent(lastElem)]->priority){
      swap(getParent(lastElem),lastElem);
      if(Q[lastElem]->priority == Q[lastElem - 1]->priority){
>>>>>>> priority_test:ReadyQueue_priority.cpp
        swap(getParent(lastElem)+1,lastElem);
      }
      // if(Q[getParent(lastElem)]->priority == Q[getParent(lastElem)+1]->priority){
      //   swap(getParent(lastElem)+1, getParent(lastElem));
      // }
      lastElem = getParent(lastElem);
    }
    

    
    else didSwap = false;
  }
}

/* getParent: find the location of the parent
	@param childLoc the index of the child
	@return int that is the parent of the child
	@calls even
*/
int ReadyQueue::getParent(int childloc){

  if(even(childloc) == true) //right child
    {
      return (childloc - 2 ) / 2;
      
    }
  else //left child
    {return (childloc - 1)/2;}
}

/* even: Even or odd?
	@param i int the number to check
	@return if true or false even
*/
bool ReadyQueue::even(int i)
{
  if ((i%2) == 0)
    return true;
  else 
    return false;
}

/* reheapify: to rearrange the ReadyQueue after remove the highest priority
	@param none
	@return none
	@calls getLargerchild()
*/
void ReadyQueue::reheapify()
{
  int X;
  int Y; //local variable for holding the location of larger child
  bool didSwap = true; //bool variable in order to determine we did swap or not
  Q[0] = Q[count - 1]; //move the last elem to the front
  count--;
  X = 0;
  while (X < count - 1 && didSwap == true)
    {
<<<<<<< HEAD:ReadyQueue_sjf.cpp
      Y = getSmallerchild(X);
      if (Y != -1 && (Q[X]->burst >= Q[Y]->burst))
=======
      Y = getLargerchild(X);
      if (Y != -1 && (Q[X]->priority <= Q[Y]->priority))
>>>>>>> priority_test:ReadyQueue_priority.cpp
        {
          swap(Y,X);
          X = Y;
        }
      else 
	{didSwap = false;}
    }
}

/* getLargerchild: to find the location of the larger child
	@param i int that is the child
	@return the largest child
*/
int ReadyQueue::getSmallerchild(int i)
{
  int LC = 2*i + 1; //left child is in the location of 2*i + 1 in Q
  int RC = 2*i + 2; //right child is in the location of 2*i + 2 in Q
  if (LC > count -1 && RC > count -1)
    {return -1;}
  if (Q[LC]->burst < Q[RC]->burst)
    {
      return LC;
    }
<<<<<<< HEAD:ReadyQueue_sjf.cpp
  else if(Q[LC]->burst == Q[RC]->burst)
=======
  else if(Q[LC]->priority == Q[RC]->priority)
>>>>>>> priority_test:ReadyQueue_priority.cpp
  {
    //determines which child (left or right) to return when they are the same priority based on the order of FCFS. 
    if(stoi(Q[LC]->name.substr(1)) < stoi(Q[RC]->name.substr(1))){
      return LC;
    }
    else return RC;
  }
  else {return RC;}
}