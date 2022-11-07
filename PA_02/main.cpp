//standard libraries
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

//User object files
#include "UserQueue.h"
#include "User.h"

//Namespace declaration
using namespace std;

//Driver functions
void scheduler(int&,int,fstream&);

//Main driver function for program
int main() {
    int clock;
    clock = 0;
    int q;

    fstream file;
    file.open("../input.txt", ios_base::in);

    file >> q;

    //Read the first line to receive the quantum and store the integer value in 'q'
    thread thr_schedule(scheduler, ref(clock), q, ref(file));

    //Once assignment works, it would be best to detach instead of waiting for it to join,
    //Then we can use clock = -1 as a completion signal to this driver function
    thr_schedule.detach();

    while(clock == 0); // Busy wait for the setup to complete in the thread
    //cout << "Clock has started" << endl;
    //This block is for when we have a somewhat functioning program ready to test
    while(clock >= 1){
        this_thread::sleep_for(chrono::milliseconds(100));
        clock ++;
    }

    return 0;
}

void scheduler(int& clk, int q, fstream& file){
    //convert input file to proper schedule
    auto* queue = new UserQueue();

    string temp;
    while(file >> temp){
        int i,j,k;
        file >> i;
        User* newUser = new User(temp,i);
        for(int n = 0; n < i; n++){
            file >> j;
            file >> k;
            newUser->addProcess(clk, j, k, n);
        }
        //Prime user for first cycle and add to queue
        newUser->setIndex(0);
        queue->addUser(newUser);
    }

    file.close();
    file.open("../output.txt", ios_base::out);
    temp = "";

    User* active;

    //Starts the clock once loaded
    clk = 1;

    while(queue->getUser() != nullptr){
        active = queue->getUser();

        while(active->nextProcess() == -1){
            queue->cycleQueue();
            active = queue->getUser();
        }

        active->resume();
        int sTime = clk;
        temp = "Time " + to_string(clk) + ", ";
        temp += "User " + active->getID() + ", ";
        temp += "process " + to_string( active->getIndex() ) + ", ";
        temp += "Resumed\n";
        cout << temp;

        while(clk != (sTime + q)){
            // If the current process completes during the User's assigned time
            if(active->getStatus() == -1){
                // Document
                temp = "Time " + to_string(clk) + ", ";
                temp += "User " + active->getID() + ", ";
                temp += "process " + to_string( active->getIndex() ) + ", ";
                temp += "Completed\n";
                cout << temp;

                //If the user
                if (active->validate() > 0){
                    if (active->nextProcess() != -1){
                        active->resume();
                        temp = "Time " + to_string(clk) + ", ";
                        temp += "User " + active->getID() + ", ";
                        temp += "process " + to_string( active->getIndex() ) + ", ";
                        temp += "Resumed\n";
                        cout << temp;
                    } else
                        break;
                } else
                    break;
            }
        }
        if(active->getStatus() != -1){
            //this_thread::sleep_for(chrono::milliseconds(20));
            active->pause();
            temp = "Time " + to_string(clk) + ", ";
            temp += "User " + active->getID() + ", ";
            temp += "process " + to_string( active->getIndex() ) + ", ";
            temp += "Paused\n";
            cout << temp;
        }

        if(active->validate() == 0)
            queue->removeHead();
        else
            queue->cycleQueue();

        if(queue->getLength() == 0)
            break;
    }


    //End of process, clk to <0 will stop the program
    clk = -2;

    file.close();
    delete queue;
}
