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
#include "ReadyQueue_priority_rr.h"
#include "ReadyQueue_rr.h"


using namespace std;
int main(int argc, char *argv[])
{
    std::cout << "CS 433 Programming assignment 3" << std::endl;
	std::cout << "Author: Jason Luu and Zsuzsanna Dinaovics" << std::endl;
	std::cout << "Date: 04/09/2020" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description: Priority based with Round Robin (EXTRA CREDIT)" << std::endl;
	std::cout << "	Uses the priority queue to store the tasks based on the priority (The highest number is the highest priority)." << std::endl;
	std::cout << "	If there are two or more tasks that have the same priority, we will do the Round-Robin scheduling alogorithm for those tasks." << std::endl;
    std::cout << "	Otherwise, the task will run as priority scheduler." << std::endl;
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
    queue tempQueue; //***
    //printQueue holds ran processes for printing info
    ReadyQueue printQueue; 
    PCB* new_process = new PCB("",0,0,0,0,0); //holds the new process from the input file
    //running_task holds the processes that has the highest priority
    PCB* running_task = new PCB("",0,0,0,0,0);
    //next_task holds the preocess that will be removed in the next iteration
    PCB* next_task;
    int counter = 0; //local variable for keeping track of how many processes do we have in the input file
    int arrive_time = 0; //assumption of all the process arrive at time 0
    int previous_finish_time = 0; //holds the previous finished time process.
    double sfinish_time = 0;
    double swaiting_time = 0;
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
    // CODE TO RUN THE PRIORITY BASED ROUND ROBIN SCHEDULLING ALGORITHM
    while(tableQueue.size() != 0){
        running_task = tableQueue.removeHighest();
        next_task = tableQueue.checkFront();
        cout<<"Running task = ["<<running_task->name<<"]   ";
        cout<<"["<<running_task->priority<<"]   ";
        cout<<"["<<running_task->burst_left<<"]   for ";
        
        if(running_task->isEqual){ //check whether the task has any same priority with the other tasks.
            if(running_task->burst_left > QUANTUM && running_task->priority == next_task->priority){ //check if the current task has the same priority as the next task and it has the burst time greater than QUANTUMM time.
                running_task->burst_left = running_task->burst_left - QUANTUM;
                tempQueue.add(running_task);
                previous_finish_time = previous_finish_time + QUANTUM;
                cout<<QUANTUM<<" units"<<endl;
                continue;
            }
            else if (running_task->burst_left > QUANTUM && running_task->priority != next_task->priority){ //the case when the current task does not have the same priority as the next task
                running_task->burst_left = running_task->burst_left - QUANTUM;
                tempQueue.add(running_task);
                previous_finish_time = previous_finish_time + QUANTUM;
                cout<<QUANTUM<<" units"<<endl;
                while(!tempQueue.isEmpty()){ //time to run the tasks that are in the Round-Robin Queue that have all the same priority
                    running_task = tempQueue.remove();
                    cout<<"Running task = ["<<running_task->name<<"]   ";
                    cout<<"["<<running_task->priority<<"]   ";
                    cout<<"["<<running_task->burst_left<<"]   for ";
                    if(running_task->burst_left > QUANTUM){
                        running_task->burst_left = running_task->burst_left - QUANTUM;
                        tempQueue.add(running_task);
                        previous_finish_time = previous_finish_time + QUANTUM;
                        cout<<QUANTUM<<" units"<<endl;
                        continue;
                    }
                    else{
                        running_task->turn_around_time = running_task->turn_around_time + arrive_time + running_task->burst_left + previous_finish_time;
                        previous_finish_time = running_task->turn_around_time;
                        running_task->waiting_time = running_task->turn_around_time - running_task->burst;
                        cout<<running_task->burst_left<<" units"<<endl;
                        cout<<"Task "<<running_task->name<<" is finished."<<endl;
                        sfinish_time = sfinish_time + running_task->turn_around_time;
                        swaiting_time = swaiting_time + running_task->waiting_time;
                    }
                }
            }
            else //case when the task's burst time <= QUANTUMM
            {
                running_task->turn_around_time = running_task->turn_around_time + arrive_time + running_task->burst_left + previous_finish_time;
                previous_finish_time = running_task->turn_around_time;
                running_task->waiting_time = running_task->turn_around_time - running_task->burst;
                cout<<running_task->burst_left<<" units"<<endl;
                cout<<"Task "<<running_task->name<<" is finished."<<endl;
                sfinish_time = sfinish_time + running_task->turn_around_time;
                swaiting_time = swaiting_time + running_task->waiting_time;
            }
        }
        else //case when the task has a unique priority
        {
            running_task->turn_around_time = running_task->turn_around_time + arrive_time + running_task->burst_left + previous_finish_time;
            previous_finish_time = running_task->turn_around_time;
            running_task->waiting_time = running_task->turn_around_time - running_task->burst;
            cout<<running_task->burst_left<<" units"<<endl;
            cout<<"Task "<<running_task->name<<" is finished."<<endl;
            sfinish_time = sfinish_time + running_task->turn_around_time;
            swaiting_time = swaiting_time + running_task->waiting_time;
        }    
    }
    while(!tempQueue.isEmpty()){ //SPECIFIC CASE WHEN ALL THE TASKS HAVE THE SAME PRIORITY
                    running_task = tempQueue.remove();
                    cout<<"Running task = ["<<running_task->name<<"]   ";
                    cout<<"["<<running_task->priority<<"]   ";
                    cout<<"["<<running_task->burst_left<<"]   for ";
                    if(running_task->burst_left > QUANTUM){
                        running_task->burst_left = running_task->burst_left - QUANTUM;
                        //running_process->waiting_time = running_process->waiting_time + QUANTUM;
                        tempQueue.add(running_task);
                        previous_finish_time = previous_finish_time + QUANTUM;
                        cout<<QUANTUM<<" units"<<endl;
                        continue;
                    }
                    else{
                        running_task->turn_around_time = running_task->turn_around_time + arrive_time + running_task->burst_left + previous_finish_time;
                        previous_finish_time = running_task->turn_around_time;
                        running_task->waiting_time = running_task->turn_around_time - running_task->burst;
                        cout<<running_task->burst_left<<" units"<<endl;
                        cout<<"Task "<<running_task->name<<" is finished."<<endl;
                        sfinish_time = sfinish_time + running_task->turn_around_time;
                        swaiting_time = swaiting_time + running_task->waiting_time;
                    }
                }
    //PRINT OUT THE STATISTICS FOR EACH TASK AND THE AVERAGE OF WAITIING AND TURN-AROUND TIME
    table.display();
    cout<<"Average turn-around time = "<<sfinish_time/counter<<endl;
    cout<<"Average waiting time = "<<swaiting_time/counter<<endl;
    
    return 0;
}