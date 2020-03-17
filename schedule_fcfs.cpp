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
#include "queue.h"

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
    queue q1;
    PCB* running_process = new PCB("",0,0);
    int arrive_time = 0;
    int finish_time = 0;
    int waiting_time = 0;
    double sfinish_time = 0;
    double swaiting_time = 0;
    int count =0;//counter to keep track how many proccesses are in the PCB table
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
        table.PCBTable[count] = new PCB(name,priority,burst);
        q1.add(table.PCBTable[count]);
        count++;
        
    }
    //TESTING FOR CORRECT PCBTABLE
    for(int i = 0; i < count; i++){
        cout<<"["<<table.PCBTable[i]->name<<"]  ";
        cout<<"["<<table.PCBTable[i]->priority<<"]  ";
        cout<<"["<<table.PCBTable[i]->burst<<"]  ";
        cout<<endl;
    }
    q1.displayAll(); //TESTING FOR CORRECT QUEUE


    // TODO: Add your code to run the scheduler and print out statistics
    while(!q1.isEmpty()){
        q1.remove(*running_process);
        finish_time = finish_time + running_process->burst + arrive_time;
        waiting_time = finish_time - running_process->burst;
        cout<<"--------------------"<<endl;
        cout<<running_process->name<<" turn-around time = ";
        cout<<finish_time<<", waiting time = ";
        cout<<waiting_time<<endl;
        sfinish_time = sfinish_time + finish_time;
        swaiting_time = swaiting_time + waiting_time;
        
    }
    cout<<"Average turn-around time = " <<sfinish_time/count<<endl;
    cout<<"Average waiting time = "<<swaiting_time/count<<endl;
    


    return 0;
}
