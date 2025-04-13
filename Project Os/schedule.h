/*Michael Gutierrez 
March 17, 2025
Scheduling Process Project 3
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


using namespace std;

struct Process{
    int processid; // Process ID
    int burstTime; // CPU total execution time by the process
    int completeTime; //time for total completetion of process
    int arrivalTime; // time for the processing entering system
    int waitingTime; // total time process waited in queue
    int remainingTime; // CPU time left before completion
    int turnTime; // time from arrival to completion

    Process (int id, int burst, int arrive)
        : processid(id), burstTime(burst), completeTime(0), arrivalTime(arrive),
            waitingTime(0), remainingTime(burst), turnTime(0) {}
};

//Compare sorting process based on the arrival time
bool compArrival(const Process &a, const Process &b){
    return a.arrivalTime < b.arrivalTime;
}

//FCFS Scheduling Algorithm
void fcfs(vector<Process> &process) {
    sort(process.begin(), process.end(), compArrival);
    int currentTime = 0;

    for (auto &proc : process){
        if(currentTime < proc.arrivalTime)
            currentTime = proc.arrivalTime;
        proc.completeTime = currentTime + proc.burstTime;
        proc.turnTime = proc.completeTime - proc.arrivalTime;
        proc.waitingTime = proc.turnTime - proc.burstTime;
        currentTime = proc.completeTime;
    }
}


//SJF Scheduling Algorithm (Non-Preemptive)
void sjf(vector<Process> &process){
    sort(process.begin(), process.end(), compArrival);
        int currentTime = 0;
        priority_queue<pair<int, Process*>,vector<pair<int, Process*>>,
            greater<pair<int, Process*>>> ready_queue;
        vector<Process> completed;

        while(!process.empty() || !ready_queue.empty()){
            while(!process.empty() && process.front().arrivalTime <= currentTime){
                ready_queue.push({process.front().burstTime, &process.front()});
                process.erase(process.begin());
            }

            if (!ready_queue.empty()){
                pair<int, Process*> current = ready_queue.top(); //this was used added from AI assistance
                ready_queue.pop();
                
                Process* proc = current.second;
                proc->completeTime = currentTime + proc->burstTime;
                proc->turnTime = proc->completeTime - proc->arrivalTime;
                proc->waitingTime = proc->turnTime - proc->burstTime;
                currentTime = proc->completeTime;
                completed.push_back(*proc);
            }
            else{
                currentTime = process.front().arrivalTime;
            }
        }
    process = completed;

}

//display function taken from AI. used to display all times.
void display(const vector<Process> &process){
    cout << "PID  Arrival  Burst  Completion  Turnaround  Waiting\n";
    for (const auto &p : process) {
        cout << p.processid << "    " << p.arrivalTime << "      " << p.burstTime << "          "
             << p.completeTime << "          " << p.turnTime << "         " << p.waitingTime << "\n";
    }
    if(!process.empty()){
    double avg_tat = 0.0, avg_wt = 0.0;
    for (const auto &p : process) {
        avg_tat += p.turnTime;
        avg_wt += p.waitingTime;
    }
    avg_tat /= static_cast<double>(process.size());
    avg_wt /= static_cast<double>(process.size());

    cout << "\nAverage Turnaround Time: " << avg_tat << "\n";
    cout << "Average Waiting Time: " << avg_wt << "\n";
    }
}

//main function utilizes a 4 x 3 matrix and runs the numbers through both 
//the FCFS and the SJF algorithm. Then the process displays all times after each
//algorithm executes.
void runSchedule(){
    vector<Process> processList = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {4, 6, 2}
    };

    cout << "FCFS:\n";
    fcfs(processList);
    display(processList);

    cout << "\nSJF Non-Preemptive:\n";
    sjf(processList);
    display(processList);

}