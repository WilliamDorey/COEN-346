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
counting_semaphore vm_turn{0};

// TODO: Separate functions into respective .cpp files for conciseness and modularity?
//  Scheduler + Process
//  Memory Manager
//  Memory space should probably be a class since it gets at least 4 functions


// Declaring functions
// TODO: Decide which functions can open a stream vs just have it passed to if by reference
[[noreturn]] void virtual_clock(int&);
void process(int&, fstream&, fstream&, int, int, int);
void scheduler(int&, fstream&);
int getRandom();
void VMmanager(int&, int&, fstream&, fstream&, int);

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
        thread thr_proc(process, ref(clk), ref(commands), ref(logs), info[0], info[1], info[2]);
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
void process(int& clk, fstream& commands, fstream& log, int start, int burst, int ID){
    int sClk = clk;
    cout << "Starting process " << ID << " at clock time " << clk << endl;

    // TODO: Log start and finish of process

    // TODO: Run the following loop until time to end
    //  Read command -> execute command -> log command upon complete -> get random int between 10 and 1000 ->
    //  wait for that time in milliseconds (or wait until end of burst) -> repeat

    // TODO: Signal semaphore at exit so next process can start

    int API_time = 0;
    string cmd;

    while (burst*10 > API_time){
        API_time += getRandom();
        sClk += API_time;
        thread thr_vmm(VMmanager, ref(sClk), ref(ID), ref(commands), ref(log), start);
        thr_vmm.join();
    }

    while (burst > (clk - sClk)/1000);
    cout << "Ending process " << ID << " at clock time " << clk << endl;
    cores.release();
}

void VMmanager(int& sClk, int& ID, fstream& commands, fstream& log,int arrival){
    string cmd;
    commands >> cmd;
    int vID, val;

    MemorySpace* mem;

    //need flag; if not my turn, stuck in while loop
    //if arr => sClk, exit while loop
    //while (arrival*1000 < sClk);
    if(cmd == "Store"){
        commands >> vID;
        commands >> val;
       // mem->Store(to_string(vID),val);
        log << "Clock: " << sClk << " Process: " << ID << ", Store: Variable " << vID << ", Value: " << val << endl;
    }
    else if (cmd == "Lookup"){
        commands >> vID;
        //mem->Lookup(to_string(vID));
        log << "Clock: " << sClk << " Process: " << ID << ", Lookup: Variable " << vID << endl;
    }
    else if (cmd == "Release"){
        commands >> vID;
        //mem->Release(to_string(vID));
        log << "Clock: " << sClk << " Process: " << ID << ", Release: Variable " << vID << endl;
    }
    else
        cout << "Invalid Command in input file\n";

}

// Function to return a random integer between 10 and 1000
int getRandom(){
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> dist(1,1);
    return dist(generator) * 10;
}