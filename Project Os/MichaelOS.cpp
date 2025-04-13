//Michael Gutierrez CSCE 4326
//2/12/2025
//IMPORTANT!github link for project
//https://github.com/MninumHornum/Michael-Gutierrez-Operating-Systems



#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "process.h"
#include "schedule.h"
//#include windows.h
using namespace std;


void runProcess();
void runSchedule();


//loading bar function 
void showLoadingBar(int totalSteps, int delayMs) {
    cout << "Loading: [";
    for (int i = 0; i < totalSteps; ++i) {
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        cout << "#";
        cout.flush(); // Flush output to update the terminal
    }
    cout << "] Done!" << endl;
    cout << "Welcome to Michael OS!";
}
 //the Authentication user function helps the user create a admin and password, and before logging in completely, the user must
 //reenter the information correct
void  AuthenticationUser(){ 
     string pass;
    string user;
    string idPass;
    string useCheck;
    string check;
    string idUser;

    cout << "Create a admin: "; // create a password
    cin >> user, 
    cout << "\n";
    useCheck = user;

    cout << "Create a password: "; // create a password
    cin >> pass, 
    cout << "\n";
    check = pass;
    do{
        cout << "Enter admin to log in: "; // user enters password
        cin >> idUser;
        cout << "\n";
        if(useCheck != idUser){
            cout << "INCORRECT! enter correct admin to continue\n";
        }
    }while(idUser != useCheck);
    
    do{
        cout << "Enter password to log in: "; // user enters password
        cin >> idPass;
        cout << "\n";
        if(check != idPass){
            cout << "INCORRECT! enter correct password\n";
        }
    } while(idPass != check);   
}

 // main function
int main() {
    int totalSteps = 30; // Number of steps in the progress bar
    int delayMs = 100;   // Delay in milliseconds between updates

    AuthenticationUser();
    showLoadingBar(totalSteps, delayMs);

    cout << "\n\n---- Running Process ----\n";
    runProcess();
    
    cout << "\n\n---- Running Schedule ----\n";
    runSchedule();
    
    return 0;
}
