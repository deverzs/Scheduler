/*
Jason Luu and Zsuzsanna Dianovics
Assignment 3
Header file: ReadyQueue.h
Header file for queue object
This object creates a first come first queue that removes objects
based on the first come first serve order.
*/
/**
 * queue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a regular queue here such that the process that come first can be selected first.
 */
using namespace std;
#include<string>
#include "PCB.h"

//----- Globally setting up the aliases ----------------

typedef PCB el_t;          // el_t is an alias for the data type
// el_t is unknown to the client  

const int MAX_SIZE = 50;  // this is the max number of elements
// MAX is unknown to the client
//-------------------------------------------------------

class queue  
{
  private:
  // Data members are:
  el_t* el[MAX_SIZE]; // an array called el.
                     // Elements will be found between front and rear but
                     // front may be behind rear since the queue wraps around
  int  count;          // how many elements do we have right now?
  int  front;          // where the front element of the queue is.
  int  rear;           // where the rear element of the queue is.

  public:    // prototypes to be used by the client
  // Note that no parameter variables are given

  //add exception handling classes here with comments
  class Overflow{};//Overflow expception to handle overflow error
  class Underflow{}; //Underflow exception to handle underflow error

   queue();   // constructor to create an object 
   ~queue();  //destructor to destroy an object

   // PURPOSE: returns true if queue is empty, otherwise false
   bool isEmpty();

   // PURPOSE: returns true if queue is full, otherwise false
   bool isFull();

   // PURPOSE: if full, throws an exception Overflow
   // if not full, enters an element at the rear 
   // PRAMETER: provide the element to be added
   void add(el_t*);

   // PURPOSE: if empty, throws an exception Underflow
   // if not empty, removes the front element and give it back.
   el_t* remove();

   // PURPOSE: if empty, throws an exception Underflow
   // if not empty, give back the front element (but does not remove it)
   // PARAMETER: provide a holder for the element (pass by ref)
   void frontElem(el_t&);

   // PURPOSE: returns the current size to make it 
   // accessible to the client caller
   int getSize();

   // PURPOSE: display everything in the queue from front to rear
   //  enclosed in []
   // if empty, displays [ empty ]
   void displayAll();

   // PURPOSE: if empty, throws an exception Underflow
   //if queue has just 1 element, does nothing
   //if queue has more than 1 element, moves the front one to the rear
   void goToBack();


};           

