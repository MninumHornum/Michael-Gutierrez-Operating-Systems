#include <iostream>
#include <string>
#include "virtualmem.h"

using namespace std;
//for the process states
enum stateProcess{NEW, READY, RUNNING, TERMINATED, WAITING};

class process {
private:
    int processid; // Process ID
    int burstTime; // CPU total execution time by the process
    int priority; // level of priority by the process
    int arrivalTime; // time for the processing entering system
    int waitingTime; // total time process waited in queue
    int remainingTime; // CPU time left before completion
    int turnTime; // time from arrival to completion
    int memory; // amount of memory for the process
    bool ioOperate; // Flag if process as I/O operations.
    stateProcess state; // current state of the process. 

public:
    // constructor
    process(int id, int burst, int prioit, int mem, bool io, int arrive)
        : processid(id), burstTime(burst), priority(prioit), arrivalTime(arrive),
            waitingTime(1), remainingTime(burst), turnTime(1), memory(mem), ioOperate(io) {}
    
    //used to update the process
    void stateSet(stateProcess stateNew) {
        state = stateNew;
    }

    /*this will execute the process, most of this is meant
    to check anything and keep a counter on the remaining time and what state we are in. when the process finishes
    execution, itll return the the state to TERMINATED. */ 
    void execution() {
        if(state == READY || state == RUNNING) {
            state = RUNNING;
            if(remainingTime > 0){
                remainingTime--;
            }
            if(remainingTime == 0) {
                state = TERMINATED;
            }
        }
    }
    //these are getters for stateproccess, remaining time, and the id
    stateProcess getState() const {return state; }
    int getRemain() const { return processid; }
    int getID() const {return processid; }

    /*this converts the enum state to string for the sake of displaying the current time in the process*/
    string stateString(stateProcess s) const {
        switch (s) {
            case NEW: return "new";
            case READY: return "ready";
            case RUNNING: return "running";
            case TERMINATED: return "terminated";
            case WAITING: return "waiting";
            default: return "state unknown";
        }
    }

    //heres how I display everything
    void display() const {
        cout << "ID Process: " << processid << " \nState: " <<
            stateString(state) << " \nRemaining Time: " << remainingTime;
    }

};

void runProcess() {
    // the values for the class process(int id=1, int burst=5, int prioit=1, int mem=1024, bool io=false, int arrive=0)
    process p1(1, 5, 1, 1024, false, 0); 
    p1.stateSet(READY); // start process as READY
    p1.display(); // void display

    for(int i = 0; i < 5; i++){ //loop process execution
        p1.execution();
        p1.display();
    }

    VirtMemory procVM;
    Frame framtab[NUM_FRAMES] = {};

    procVM.pagetable[0] = {true, 0, false};
    procVM.pagetable[1] = {true, 1, false};

    framtab[0] = {0, true};
    framtab[1] = {1, true};

    int virtAddress[] = {0,3019, 6120, 9231, 12342, 14453};
    for(int i = 0; i < 6; i ++){
        int physicalAdd = translation(virtAddress[i], framtab, procVM);
        if (physicalAdd != -1){
            cout << "\nVIRTUAL ADDRESS " << virtAddress[i] << " => PHYSCIAL ADDRESS " << physicalAdd << "\n";
        }
    }

}
