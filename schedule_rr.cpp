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
#include "ReadyQueue_rr.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "CS 433 Programming assignment 3" << std::endl;
    std::cout << "Author: xxxxxx and xxxxxxx" << std::endl;
    std::cout << "Date: xx/xx/20xx" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : **** " << std::endl;
    std::cout << "=================================" << std::endl;
    
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
    // create PCB table and Ready Queue
    PCBTable table;
    // tableQueue holds the queue to run the processes
    queue tableQueue;
    PCB* new_process = new PCB("",0,0,0,0,0);
    PCB* running_process = new PCB("",0,0,0,0,0);;
    int arrive_time = 0;
    int previous_finish_time = 0; //holds the previous finished time process.
    int counter = 0; //how many procceses do we have in the input file
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
        new_process = new PCB(name,priority, burst, burst,0,0);
        table.add(new_process);
        tableQueue.add(new_process);
        counter++;
    }
    //TESTING FOR CORRECT PCBTABLE
    for(int i = 0; i < table.getSize(); i++){
        cout<<"["<<table.PCBTable[i]->name<<"]  ";
        cout<<"["<<table.PCBTable[i]->priority<<"]  ";
        cout<<"["<<table.PCBTable[i]->burst<<"]  ";
        cout<<endl;
    }
    //tableQueue.displayAll(); //TESTING FOR CORRECT QUEUE


    // TODO: Add your code to run the scheduler and print out statistics
    while(!tableQueue.isEmpty()){
        running_process = tableQueue.remove();
        cout<<"Running task = ["<<running_process->name<<"] [";
        cout<<running_process->priority<<"] [";
        cout<<running_process->burst_left<<"] for ";
        if(running_process->burst_left > QUANTUM){
            running_process->burst_left = running_process->burst_left - QUANTUM;
            //running_process->waiting_time = running_process->waiting_time + QUANTUM;
            tableQueue.add(running_process);
            previous_finish_time = previous_finish_time + QUANTUM;
            cout<<QUANTUM<<" units"<<endl;
            continue;
        }
        else
        {
            running_process->turn_around_time = running_process->turn_around_time + running_process->burst_left + arrive_time + previous_finish_time;
            previous_finish_time = running_process->turn_around_time;
            running_process->waiting_time = running_process->turn_around_time - running_process->burst;
            cout<<running_process->burst_left<<" units"<<endl;
            cout<<"Task "<<running_process->name<<" is finished."<<endl;
        }
        
        
        //cout<<"--------------------"<<endl;
        sfinish_time = sfinish_time + running_process->turn_around_time;
        swaiting_time = swaiting_time + running_process->waiting_time;
    }
    table.display();
    cout<<"Average turn-around time = " <<sfinish_time/counter<<endl;
    cout<<"Average waiting time = "<<swaiting_time/counter<<endl;
    


    return 0;
}