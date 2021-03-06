/**
 * Driver program 
 * 
 * Add other data structures and .cpp and .h files as needed.
 * 
 * The input file is in the format:
 *
 *  [name], [priority], [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "PCB.h"
#include "ReadyQueue_sjf.h"


using namespace std;
int main(int argc, char *argv[])
{
    std::cout << "CS 433 Programming assignment 3" << std::endl;
	std::cout << "Author: Jason Luu and Zsuzsanna Dinaovics" << std::endl;
	std::cout << "Date: 04/09/2020" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description: Shortest Job First CPU Scheduler" << std::endl;
    std::cout << "	First, read the input file that provided from the command line." << std::endl;
	std::cout << "	Uses the shortest job queue to store the tasks based on the burst time (The highest number is the longest burst time)." << std::endl;
	std::cout << "	Then, the scheduler will schedule the shortest job to run first." << std::endl;
    std::cout << "	Then, it will calculate the turn-around and waiting time when the task is finished." << std::endl;
    std::cout << "	Finally, it will calculate the average turn-around and waiting time." << std::endl;
	std::cout << "=======================================================" << std::endl;
    
    int QUANTUM = 10;
    // Check that input file is provided at command line
    if(argc < 2 ) {
        cerr << "Usage: " << argv[0] << " <input_file> [<time_quantum>]" << endl;
        exit(1);
    }

    // Read the time quantum if provided.
    if(argc >= 3) {
        QUANTUM = atoi(argv[2]);
    }

    // Read task name, priority and burst length from the input file 
    string name;
    int priority;
    int burst;

    // open the input file
    std::ifstream infile(argv[1]);
    string line;
    // create the table for PCB and ReadyQueue
    PCBTable table;
    // tableQueue holds the queue to run the processes
    ReadyQueue tableQueue; 
    //printQueue holds ran processes for printing info
    ReadyQueue printQueue; 
    PCB* new_process = new PCB("",0,0,0,0,0); //holds the new process from the input file
    //running_task holds the processes that has the highest priority
    PCB* running_task = new PCB("",0,0,0,0,0);
    int counter = 0; //local variable for keeping track of how many processes do we have in the input file
    int arrive_time = 0; //assumption of all the process arrive at time 0
    int previous_finish_time = 0; //holds the previous finished time process.
    double sfinish_time = 0; //holds the sum of the finished time
    double swaiting_time = 0; //holds the sum of the waiting time
    while(getline(infile, line) ) {
        std::istringstream ss (line);
        // Get the task name
        getline(ss, name, ',');
        
        // Get the task priority 
        string token;
        getline(ss, token, ',');
        priority = std::stoi(token);

        // Get the task burst length 
        getline(ss, token, ',');
        burst = std::stoi(token);
        
        cout << name << " " << priority << " " << burst << endl;
        // TODO: add the task to the scheduler's ready queue
        // You will need a data structure, i.e. PCB, to represent a task
        new_process = new PCB(name,priority,burst,burst,0,0); 
        table.add(new_process);
        tableQueue.add(new_process);
        counter++;
    }
        

    //TESTING FOR CORRECT PCBTable
    for(int i = 0; i <table.getSize(); i++){
        cout<<"["<<table.PCBTable[i]->name<<"]  ";
        cout<<"["<<table.PCBTable[i]->priority<<"]  ";
        cout<<"["<<table.PCBTable[i]->burst<<"]  "<<endl;
    }
    
    // TODO: CODE TO RUN SJF CPU SCHEDULER
    while(tableQueue.size() != 0){
        running_task = tableQueue.removeHighest();
        cout<<"Running task = ["<<running_task->name<<"]   ";
        cout<<"["<<running_task->priority<<"]   ";
        cout<<"["<<running_task->burst<<"]   for "<<running_task->burst<<" units"<<endl;
        running_task->turn_around_time = running_task->turn_around_time + arrive_time + running_task->burst + previous_finish_time;
        previous_finish_time = running_task->turn_around_time;
        running_task->waiting_time = running_task->turn_around_time - running_task->burst;
        sfinish_time = sfinish_time + running_task->turn_around_time;
        swaiting_time = swaiting_time + running_task->waiting_time;
    }
    //PRINT OUT THE STATISTICS OF EACH TASK IN THE PCB TABLE
    table.display();
    //PRINT OUT THE AVERAGE TURN-AROUND AND WAITING TIME
    cout<<"Average turn-around time = "<<sfinish_time/counter<<endl;
    cout<<"Average waiting time = "<<swaiting_time/counter<<endl;
    return 0;
}
