//
//  main.cpp
//  SchedulingAlg
//
//  Created by Justin Grabowski on 12/9/18.
//  Copyright © 2018 Justin Grabowski. All rights reserved.
//

/*
 
 
 When running in “Single algorithm performance evaluation” mode the
 program should perform the following:
 -   Generate a set of data representing set of processes (min 10 and max 20)
      to be executed in the “ready” queue.  You have to create an appropriate
      data structure to store data associated with each process (Process name,
      Burst time, Priority, Arrival time etc) and to implement “ready” queue.
      Use the random number generator for test data generation.
 -   Prompt the user to select scheduling algorithm from the list and to enter
      specific parameters for selected algorithm if necessary.
 -   Calculate average waiting time using selected algorithm.
 -   Display test data, name of the selected algorithm and calculated
      average time
 -   Prompt the user to end the program or to select different algorithm for evaluation using the same set of data.
 
 
 
 
 When running in “Algorithm comparing” mode the program should be able to
  calculate the average waiting times for all implemented algorithm using
  several sets of generated data (number of sets should be given by the user),
  present the results on the screen, and store the results in a file for analysis,
  evaluation of the algorithm performance and trend analyses.
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include "Job.hpp"

int main(int argc, const char * argv[]) {
    
    while(true)
    {
        std::vector<Job> jobsVector;
        std::vector<Job> RRVector;
        std::cout << "Welcome to Justin's cpu scheduler from hell\n\n";
        unsigned short input;
        std::cout << "Plesase enter your selection (1= FCFS: 2= RR: 3= Compare) or 0 to quit:\t";
        
        while(!(std::cin>>input))
        {
            if(std::cin.eof()||std::cin.bad())
                break;
            
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid entry (1= FCFS: 2= RR: 3= Compare) or 0 to quit:\t";
        }
        
        if (std::cin.eof())
            std::cout << "No value eneterd\n";
        if (std::cin.bad())
            std::cout<< "Input steam is bad\n";
        
        if (input < 0 || input > 3)
            std::cout << "Invalid entry\n";
        
        std::cout << "\n\n";
        if(input == 0)
            break;
        
        unsigned totalWaitTime = 0;
        unsigned averageWaitTime = 0;
        unsigned totalRRWaitTime = 0;
        unsigned avgRRTime = 0;
        unsigned cputimeQuantum = 0;
     
        srand((unsigned)time(0));

        //Generating random "Jobs"
        for(size_t i = 0; i < 10; i++)
        {
            
            std::string jobName = "P" + std::to_string(i);
            
            //jobs.push(Job(jobName, std::rand()%10 , std::rand()%5, time(0) + std::rand()%10));
            
            jobsVector.push_back(Job(jobName, std::rand()%10 , std::rand()%5, std::rand()%10));

        }

        //Calculate the wait times
        for(size_t i = 0; i < jobsVector.size(); ++i)
        {
            jobsVector[i]._waitingTime = 0;
            for(size_t j = 0; j < i; j++)
                jobsVector[i]._waitingTime += jobsVector[j]._burstTime;
        }
        
    //-------------------------------------------------------------------------------
    //***************************** RUN FCFS TEST **********************************|
    //-------------------------------------------------------------------------------
        
        if(input == 1)
        {
            //Print the vectors contents
            for (auto i = jobsVector.begin(); i != jobsVector.end(); ++i)
            {
                std::cout << i->_processName
                << "\tBurst Time: " << i->_burstTime
                << "\tPriority: " << i->_priority
                << "\tArrival Time: " << i->_arrivalTime
                << "\tWaiting Time: " << i->_waitingTime << std::endl;
                //jobsVector.pop_back();
            }
            
            //Calculate the average waiting time
            size_t numProcesses = 0;
            
            while(++numProcesses < jobsVector.size())
            {
                totalWaitTime += jobsVector[numProcesses]._waitingTime;
            }
            
            averageWaitTime = totalWaitTime/numProcesses;
            
            std::cout << "\n\nAverage Wait Time: " << averageWaitTime << "\n\n";
            
        }
        
    //-------------------------------------------------------------------------------
    //****************************** RUN RR TEST ***********************************|
    //-------------------------------------------------------------------------------
        if(input == 2)
        {
            cputimeQuantum = 2;
            
            std::cout << "Quantum Time: " << cputimeQuantum <<"\n\n";
            
            //Generating random "Jobs"
            for(size_t i = 0; i < 10; i++)
            {
                std::string jobName = "P" + std::to_string(i);
                
                //jobs.push(Job(jobName, std::rand()%10 , std::rand()%5, time(0) + std::rand()%10));
                
                RRVector.push_back(Job(jobName, std::rand()%10 , std::rand()%10, std::rand()%10));
            }
            
            //create burst checker thingy
            unsigned burstTime[RRVector.size()];
            for(size_t i = 0; i < RRVector.size(); ++i)
            {
                burstTime[i] = RRVector[i]._burstTime;
            }
            
            /*
            //Calculate the wait time for RR
            {
                unsigned time = 0;
                while(true)
                {
                    bool complete = true;
                    for (size_t i = 0;i < RRVector.size(); i++)
                    {
                        if(burstTime[i] > 0)
                        {
                            complete = false;
             
                            if(burstTime[i] < cputimeQuantum)
                            {
                                time = time + burstTime[i];
                                RRVector[i]._waitingTime = time - burstTime[i];
                                burstTime[i] = 0;
                            }
                            else
                            {
                                time += cputimeQuantum;
                                burstTime[i] -= cputimeQuantum;
                            }
                        }
                    }
                    if(complete == true)
                        break;
                }
            }
            */
            
            //Calculate the wait times for RR

            int t= 0;
            while(true)
            {
                bool finnished = true;
                
                for(int i = 0; i < RRVector.size(); i++)
                {
                    if(burstTime[i] > 0) //This process has not finnished
                    {
                        finnished = false;
                        
                        if(burstTime[i] > cputimeQuantum)
                        {
                            t += cputimeQuantum;
                            burstTime[i] -= cputimeQuantum;
                        }
                        else
                        {
                            t = t+ burstTime[i];
                            RRVector[i]._waitingTime = t - burstTime[i];
                            burstTime[i] = 0;
                        }
                    }
                }
                if(finnished == true)
                    break;
            }

            //Print the vectors contents
            for (auto i = RRVector.begin(); i != RRVector.end(); ++i)
            {
                std::cout << i->_processName
                << "\tBurst Time: " << i->_burstTime
                << "\tPriority: " << i->_priority
                << "\tArrival Time: " << i->_arrivalTime
                << "\tWaiting Time: " << i->_waitingTime << std::endl;
            }
            
            //Calculate the average waiting time
            size_t numRRProcesses = 0;
            
            while(++numRRProcesses < RRVector.size())
            {
                totalRRWaitTime += RRVector[numRRProcesses]._waitingTime;
            }
            
            avgRRTime = totalRRWaitTime/numRRProcesses;
            
            std::cout << "\n\nAverage Wait Time: " << avgRRTime << "\n\n";
        }
    }
    return 0;
}
