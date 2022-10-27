#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

#include "UserQueue.h"
#include "User.h"

using namespace std;

void scheduler(int*,int,fstream&);
void process(int*,int,int,int*);

int main() {
    int *clock = new int;
    *clock = 1;
    int q;

    //TODO: Filestream called 'file'
    //Read the first line to receive the quantum and store the integer value in 'q'
    thread thr_schedule(scheduler, ref(clock), q, ref(file));

    //Once assignment works, it would be best to detach instead of waiting for it to join,
    //Then we can use clock = -1 as a completion signal to this driver function
    //thr_schedule.detach();

    while(*clock == 0); // Busy wait for the setup to complete in the thread

    //This block is for when we have a somewhat functioning program ready to test
    /*
    while(*clock >= 1){
        this_thread::sleep_for(chrono::seconds(1));
        *clock ++;
    }
    */

    //Quick 1 second sleep to verify a waiting period
    this_thread::sleep_for(chrono::seconds(1));

    //Just something to make sure we are running
    std::cout << "Hello, World!" << std::endl;

    //Making sure that the scheduler thread has completed before terminating while developing
    thr_schedule.join();
    return 0;
}

void scheduler(int* clk, int q, fstream* file){
    //convert input file to proper schedule
    this_thread::sleep_for(chrono::seconds(1));

    //Starts the clock once loaded
    *clk = 1;
}

void process(int* clk, int burst, int arrival, int* status){
    //Statuses:
    //-1 -> Complete (or nullptr)
    //0  -> Running
    //1  -> Waiting
    //2  -> Not yet Arrived
}