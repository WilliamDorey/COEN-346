// Standard Libraries
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <random>
#include <fstream>
#include <semaphore>
#include <mutex>
#include "processQueue.h"
#include "MemorySpace.h"

// Declaring default namespace for code clarity
using namespace std;

//Global variables for Semaphores
counting_semaphore cores{0};
binary_semaphore vm_turn{1};
bool flag = true;

// Declaring functions
// TODO: Decide which functions can open a stream vs just have it passed to if by reference
[[noreturn]] void virtual_clock(int&);
void process(int&, fstream&, fstream&, int, int);
void scheduler(int&, fstream&);
int getRandom();
void VM_manager(int, int, fstream&, fstream&);
void setFlag(int);

// Main Driver function
int main() {
    // Creating common streams and variables
    fstream log;
    log.open("../output.txt" ,ios_base::out);

    int clk = 0;
    // Initializing clock, scheduler, and memory manager
    thread thr_sched(scheduler, ref(clk), ref(log));
    thread thr_clock(virtual_clock, ref(clk));
    thr_clock.detach();
    thr_sched.join();

    return 0;
}

// Virtual clock function to have a common timing point for all threads
void virtual_clock(int& clk){
    // Increment the clock's value in 10 millisecond intervals forever
    do{
        this_thread::sleep_for(chrono::milliseconds(10));
        clk += 10;
    } while(true);
}

//Scheduler function
// First In First Out (FIFO) scheduler for process that are listed in "processes.txt"
void scheduler(int& clk, fstream& logs){
    fstream processes;
    fstream commands;

    processes.open("../processes.txt", ios_base::in);
    commands.open("../commands.txt", ios_base::in);

    int N = 0;
    processes >> N;
    for (int i = 0; i < N; ++i) {
       cores.release();
    }

    int i,j,k;
    processes >> i;
    processQueue* queue = new processQueue(i);
    k = 1;
    while (processes >> i){
        processes >> j;
        queue->addProc(i,j,k);
        k ++;
    }
    queue->setIndex(0);
    queue->sort();

    int* info = new int[3];
    while(true) {
        info = queue->getInfo();
        while( (clk / 1000 ) < info[0]);
        cores.acquire();
        thread thr_proc(process, ref(clk), ref(commands), ref(logs), info[1], info[2]);
        thr_proc.detach();
        if (queue->nextProc() == -1)
            break;
    }

    // Checking that all processes have completed by acquiring all available cores
    for( int l = 0; l < N; l++)
        cores.acquire();

    // end of scheduler
    cout << "Scheduler has finished at clock time " << clk << endl;
    delete[] info;
}

// Process function
// Only should be called by scheduler when it has decided to start the process
void process(int& clk, fstream& commands, fstream& log, int burst, int ID){
    int sClk = clk;
    int remain = burst*1000;
    int API_time = 0;
    int clk2 = clk;
    log << "Clock: " << clk << ", Process: " << ID << ": Started." << endl;

    while(!flag);              //busy wait until flag=1;

    do{
        setFlag(0);                 //lock VMM; only 1 process accesses it at a time
        API_time += getRandom();
        sClk += API_time;
        while(clk < sClk);                  //wait until API finishes
        remain = remain - API_time;
        if(remain < 0)
            break;
        thread thr_vmm(VM_manager, sClk, ID, ref(commands), ref(log));  //execute API calls in a thread
        thr_vmm.join();
        setFlag(1);                  //release for another API call to go through
    } while (remain > API_time);

    while (burst > (clk - clk2)/1000);
    log << "Clock: " << clk << ", Process: " << ID << ": Finished." << endl;
    cores.release();
}

//Function to execute API calls based on commands.txt input file
void VM_manager(int sClk, int ID, fstream& commands, fstream& log){
    string cmd;
    commands >> cmd;
    int vID, val;

    MemorySpace* mem;

    if(cmd == "Store"){
        commands >> vID;
        commands >> val;
        // mem->Store(to_string(vID),val);
        log << "Clock: " << sClk << ", Process: " << ID << ", Store: Variable " << vID << ", Value: " << val << endl;
    }
    else if (cmd == "Lookup"){
        commands >> vID;
        //mem->Lookup(to_string(vID));
        log << "Clock: " << sClk << ", Process: " << ID << ", Lookup: Variable " << vID << endl;
    }
    else if (cmd == "Release"){
        commands >> vID;
        //mem->Release(to_string(vID));
        log << "Clock: " << sClk << ", Process: " << ID << ", Release: Variable " << vID << endl;
    }
    else{
        commands.clear();
        commands.seekg(0, ios::beg);        //start reading file over when it's done
    }
}

void setFlag(int flagVal){
    flag = flagVal;
}

// Function to return a random integer between 10 and 1000
int getRandom(){
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> dist(1,100);
    return dist(generator) * 10;
}