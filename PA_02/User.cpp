#include <iostream>
#include <thread>
#include <utility>
#include "User.h"

using namespace std;

//Default Constructor
User::User(string newId, int i) {
    id = move(newId);
    total = i;
    index = 0;
    processes = new int[i];
}

//Destructor
User::~User(){
    delete processes;
}

//Member Functions
void User::addProcess( int& clk, int arrival, int burst, int pos){
    processes[pos] = 2;
    thread thr_new(process, ref(clk), arrival, burst, ref(processes[pos]));
    thr_new.detach();
}

void User::resume(){
    processes[index] = 0;
}

void User::pause(){
    processes[index] = 1;
}

int User::validate(){
    int remain = 0;
    for(int i = 0; i < total; i++)
        if(processes[i] >= 0)
            remain ++;

    return remain;
}
int User::nextProcess(){
    int start = index;
    int complete = 0;
    do{
        if(index < (total-1) )
            index++;
        else
            index = 0;

        if(processes[index] == 1)
            return index;
        else if (processes[index] == -1)
            complete ++;
    }while( index != start);
    if(complete == total)
        return -2;

    return -1;
}

void User::process(int& clk, int arrival, int burst, int& lock) {
    //Statuses:
    //-1 -> Complete (or nullptr)
    //0  -> Running
    //1  -> Waiting
    //2  -> Not yet Arrived
    string temp;
    //Busy wait until reaching the arrival time of the process
    while (clk < arrival);
    //cout << "Process started, time : " << burst << endl;
    lock = 1;
    int clkStored;
    while (burst > 0) {
        clkStored = clk;
        //cout << clk << endl;
        while (lock == 0 && burst > 0) {
            if (clkStored != clk) {
                burst = burst - (clk - clkStored);
                clkStored = clk;
                //string temp = "Time remaining : " + to_string(burst) + "\n";
                //cout << temp;
            }
        }
    }
    //Before terminating, set the flag to -1 to indicate the process has been completed.
    //cout << "Process completed" << endl;

    lock = -1;
}

//Get functions
string User::getID(){
    return id;
}
/*not used
int User::getTotal() const {
    return total;
}
// */
int User::getIndex() const {
    return index;
}
int User::getStatus(){
    return processes[index];
}

//Set functions
/* Not used
void User::setID(string newId) {
    id = move(newId);
}
 */
void User::setIndex(int newIndex) {
    index = newIndex;
}


