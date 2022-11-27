#include <iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

/*
 * Class that I used to test my func
 * Includes the variables associated with a process, that are used as arguments for the process func
 */
class Process{
private:
    int arrival = 1;
    int burstTime = 1;
    int status = 2;
    int id = 0;
public:
    int getArrival() const{
        return arrival;
    }
    int getbusrtTime() const{
        return burstTime;
    }
    int getStatus() const{
        return status;
    }
    int getID() const{
        return id;
    }
    void setStatus(int s){
        status = s;
    }
    void setArrival(int arr){
        arrival = arr;
    }
    void setBurst(int bt){
        burstTime = bt;
    }
    void setID(int px){
        id = px;
    }
};

void startProcess(int&, int, Process &);

/*
 * What works:
 * - Process can be executed for quantum amount or their remaining burst time
 * - Only 1 process at a time enters the critical section
 * - All process will be executed for their respective burst time (total time is correct)
 * What doesn't so far:
 * - No priority; no queue implemented.
 * - Clk doesn't increment by itself; if P3 arrives at t=5 but the current clkTime=4 (P1 burstTime + P2 burstTime), P3 will not execute.
 */

int main() {
    //Variables from scheduler
    int quantum = 2;
    int clk = 1;

    Process P1;
    P1.setID(0);

    Process P2;
    P2.setStatus(2);
    P2.setArrival(2);
    P2.setBurst(3);
    P2.setID(1);

    Process P3;
    P3.setStatus(2);
    P3.setArrival(3);
    P3.setBurst(5);
    P3.setID(2);

    thread t1(startProcess,ref(clk), ref(quantum), ref(P1));
    thread t2(startProcess,ref(clk), ref(quantum), ref(P2));
    thread t3(startProcess,ref(clk), ref(quantum), ref(P3));
    t1.join();
    t2.join();
    t3.join();

    cout << "Total time: " << clk << endl;

    return 0;
}

/*
 * Status Variable:
 * If status = 2, process has not arrived so busy wait
 * If status = 1, process is ready to enter critical section (i.e it has arrived)
 * If status = 0, it is done (no remaining burst time)
 *
 * Critical Section:
 * Decrement burstTime by quantum
 * Add quantum to clkTime
 * Change status so other processes can enter critical section
 */

void startProcess(int& clkTime, int q, Process & Px){
    int arrival = Px.getArrival();
    int burstTime = Px.getbusrtTime();
    int status = Px.getStatus();

    while (1){
        //Check if process has already finished
        if (status == 0){
            return;
        }
        while ((arrival <= clkTime) && (burstTime > 0)) {
            while (status == 2) {
                //busy wait until process arrives
                //'<=' in case some processes arrive at the same time
                if (arrival <= clkTime)
                    status = 1;
            }
            status = 2;                                 //locks so no other P enters critical section

            /* ****************************** Critical Section *************************************** */
            cout << "Time " << clkTime << ", Process " << Px.getID() << ", Started" << endl;

            //when the remaining burstTime is less than q, P should not take all of q to finish
            if (q >= burstTime){
                clkTime = clkTime + burstTime;
                burstTime = 0;
                status = 0;                             //P is done, others can enter critical section
                cout << "Time " << clkTime << ", Process " << Px.getID() << ", Finished" << endl;
            }
            else{
                burstTime = burstTime - q;
                clkTime = clkTime + q;
                status = 1;                             //P is partially done, should go back to the queue
                cout << "Time " << clkTime << ", Process " << Px.getID() << ", Paused" << endl;
            }

            break;
        }
        Px.setStatus(status);   //this property can be used to check progress of process
    }
}