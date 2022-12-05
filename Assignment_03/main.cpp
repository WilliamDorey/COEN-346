// Standard Libraries
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <random>
#include <fstream>
#include <semaphore>
#include "processQueue.h"
#include "MemorySpace.h"

// Declaring default namespace for code clarity
using namespace std;

//Global variables for Semaphores
counting_semaphore cores{0};
binary_semaphore MMU_status{0};
binary_semaphore API_ready{0};
binary_semaphore API_complete{0};

// Declaring functions
[[noreturn]] void virtual_clock(int&);
void process(int&, fstream&, fstream&, int, int, string&);
void scheduler(int&, fstream&, string&);
int getRandom();
[[noreturn]] void MMU(int&, fstream&, int, string&);


// Main Driver function
int main() {
    // Creating common streams and variables
    fstream log;
    log.open("../output.txt" ,ios_base::out);
    fstream memconfig;
    memconfig.open("../memconfig.txt", ios_base::in);
    int mem;
    memconfig >> mem;

    string cmd;
    int clk = 0;

    // Initializing clock, scheduler, and memory manager
    thread thr_sched(scheduler, ref(clk), ref(log), ref(cmd));
    thread thr_MMU(MMU, ref(clk), ref(log), mem, ref(cmd));
    thread thr_clock(virtual_clock, ref(clk));

    thr_MMU.detach();
    thr_clock.detach();

    //The program will terminate once the scheduler completes it's execution
    thr_sched.join();

    return 0;
}

// Virtual clock function to have a common timing point for all threads
[[noreturn]] void virtual_clock(int& clk){
    // Increment the clock's value in 10 millisecond intervals forever
    do{
        this_thread::sleep_for(chrono::milliseconds(10));
        clk += 10;
    } while(true);
}

//Scheduler function
// First In First Out (FIFO) scheduler for process that are listed in "processes.txt"
void scheduler(int& clk, fstream& logs, string& cmd){
    // fstream creation for processes file and commands file
    fstream processes;
    fstream commands;
    processes.open("../processes.txt", ios_base::in);
    commands.open("../commands.txt", ios_base::in);

    // finding the number of cores and setting up the semaphore to respect this value
    int N = 0;
    processes >> N;
    for (int i = 0; i < N; ++i) {
       cores.release();
    }

    //Populating the process Queue
    int i,j,k;
    processes >> i;
    auto* queue = new processQueue(i);
    k = 1;
    while (processes >> i){
        processes >> j;
        queue->addProc(i,j,k);
        k ++;
    }
    queue->setIndex(0);
    queue->sort();

    // Calls the processes as they arrive and semaphore is available
    int* info;
    while(true) {
        info = queue->getInfo();
        while( (clk / 1000 ) < info[0]);
        cores.acquire();
        thread thr_proc(process, ref(clk), ref(commands), ref(logs), info[1], info[2], ref(cmd));
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
void process(int& clk, fstream& commands, fstream& log, int burst, int ID, string& cmd){
    // log start
    string temp_log = "Clock: " + to_string(clk) + ", Process: " + to_string(ID) + ": Started.\n";
    log << temp_log;
    cout << temp_log;

    //storing the start time of the process and calculating the first API request time
    int sClk = clk; // start clock time
    int nextExec = clk + getRandom();

    do{
        // wait until the execution time for the API
        while(nextExec > clk);
        //Wait for the MMU to become available
        MMU_status.acquire();
        //Determine the command to be run
        if(!getline(commands, cmd)) {
            commands.clear();
            commands.seekg(0);
            getline(commands, cmd);
        }
        //Send API command via reference string location and semaphores
        temp_log = ", Process: " + to_string(ID) + ": " + cmd;
        API_ready.release();
        API_complete.acquire();
        temp_log = "Clock: " + to_string(clk) + temp_log + " : Results = " + cmd + '\n';
        log << temp_log;
        cout << temp_log;
        cmd = "";
        //Finished with MMU and calculate next execution time
        MMU_status.release();
        nextExec = clk + getRandom();
    } while (burst > (nextExec - sClk) / 1000);

    //busy wait until the process expires
    while (burst > ( clk - sClk ) / 1000);

    //log end
    temp_log = "Clock: " + to_string(clk) + ", Process: " + to_string(ID) + ": Finished.\n";
    log << temp_log;
    cout << temp_log;
    cores.release();
}

//Function to execute API calls based on commands.txt input file
[[noreturn]] void MMU(int& clk, fstream& log, int memSize, string& cmd){
    // Variable setup
    string func, vid;
    int val;
    auto* mem = new MemorySpace(memSize, ref(log), ref(clk));

    //Initial release to allow operations once setup process is complete
    MMU_status.release();

    //Main operation of the MMU
    while(true){
        //Wait for an incoming API request and process command
        API_ready.acquire();
        istringstream ss(cmd);
        ss >> func;
        if (func == "Store"){
            ss >> vid;
            ss >> val;
            mem -> Store(vid,val);
            cmd = "Variable stored";
        } else if (func == "Release"){
            ss >> vid;
            mem -> Release(vid);
            cmd = "Release Completed";
        } else if (func == "Lookup") {
            ss >> vid;
            val = mem -> Lookup(vid);
            cmd = to_string(val);
        } else {
            cmd = "Invalid command, Aborting operation!\n";
        }
        API_complete.release();
    }
}

// Function to return a random integer between 10 and 1000
int getRandom(){
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> dist(1,100);
    return dist(generator) * 10;
}