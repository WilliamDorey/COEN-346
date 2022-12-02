// Standard Libraries
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <random>
#include <fstream>

// Declaring default namespace for code clarity
using namespace std;

// TODO: Separate functions into respective .cpp files for conciseness and modularity?
//  Scheduler + Process
//  Memory Manager
//  Memory space should probably be a class since it gets at least 4 functions


// Declaring functions
// TODO: Decide which functions can open a stream vs just have it passed to if by reference
[[noreturn]] void virtual_clock(int&);
void process(int&, fstream&, fstream&, int);
void scheduler(int&, fstream&);

// Main Driver function
int main() {
    // Creating common streams and variables
    fstream log;
    log.open("../output.txt" ,ios_base::out);

    int clk = 0;
    // Initializing clock, scheduler, and memory manager
    thread thr_clock(virtual_clock, ref(clk));
    thread thr_sched(scheduler, ref(clk), ref(log));
    thr_clock.detach();
    thr_sched.join();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

// Virtual clock function to have a common timing point for all threads
void virtual_clock(int& clk){
    // TODO: replace with a semaphore since its the main topic for this assignment
    // wait for the clock to be kick-started in order to allow some setup time before execution
    while(clk == 0);

    // TODO: once semaphore is implemented, move this to main function so clk is only initialized once
    clk = 1000;

    // Increment the clock's value in 10 millisecond intervals forever
    do{
        this_thread::sleep_for(chrono::nanoseconds(10000));
        clk ++;
    } while(true);
    // TODO: do we want this process to terminate at the end? If so we can do like previous assignment, and force clk
    //  negative in the main function to escape loop here since its ref
}

//Scheduler function
// First In First Out (FIFO) scheduler for process that are listed in "processes.txt"
void scheduler(int& clk, fstream& logs){
    string temp = "";
    // TODO: Open input file streams for the "commands.txt" and "processes.txt" files
    fstream processes;
    fstream commands;

    processes.open("../processes.txt", ios_base::in);
    commands.open("../commands.txt", ios_base::in);

    // TODO: Read "processes.txt" for the core count (C), number of processes (N), and the processes respective values
    int N = 0;
    processes >> N;
    temp = to_string(N);
    logs << temp << endl;
    temp = "";
    processes >> temp;
    logs << temp;
    commands >> temp;
    logs << temp;

    // TODO: Start process threads as they arrive based on reference clock
    //  (store order as file line # in an array maybe? or a parallel array of arrival and burst times?)
    //  Should also have a common file stream for "commands.txt" passed to each (created above)

    // TODO: Semaphore to only allow as many processes as cores to run

    // TODO: Clean up any pointers used here
}

// Process function
// Only should be called by scheduler when it has decided to start the process
void process(int& clk, fstream& commands, fstream& log, int burst){
    // TODO: Log start and finish of process

    // TODO: Run the following loop until time to end
    //  Read command -> execute command -> log command upon complete -> get random int between 10 and 1000 ->
    //  wait for that time in milliseconds (or wait until end of burst) -> repeat

    // TODO: Signal semaphore at exit so next process can start
}

