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
#include <iomanip>
#include "Job.hpp"
#include "algorithmCompare.hpp"

int main(int argc, const char * argv[]) {
    
    while(true)
    {
        std::vector<Job> jobsVector;
        std::vector<Job> RRVector;
        std::cout << "Welcome to Justin's cpu scheduler!\n\n";
        unsigned short input = 0;
        std::cout << "Please enter your selection (1= FCFS: 2= RR: 3= Compare) or 0 to quit:\t";
        
        while(!(std::cin>>input))
        {
            if(std::cin.eof()||std::cin.bad())
                break;
            
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid entry (1= FCFS: 2= RR: 3= Compare) or 0 to quit:\t";
        }
        if (std::cin.eof())
        {
            std::cout << "No value enterd\n";
            break;
        }
        if (std::cin.bad())
        {
            std::cout<< "Input steam is bad\n";
            break;
        }
        
        if (input < 0 || input > 3)
            std::cout << "Invalid entry\n";
        
        std::cout << "\n\n";
        if(input == 0)
            break;
        
        unsigned totalWaitTime = 0;
        unsigned averageWaitTime = 0;
        unsigned totalRRWaitTime = 0;
        unsigned avgRRTime = 0;
        int cputimeQuantum = 0;
     
        srand((unsigned)time(0));

        
        std::vector<int> arrivalTimes;
        //Generating and sorting arrival times
        for(size_t i = 0; i< 5; i++)
        {
            if(i == 0)
                arrivalTimes.push_back(0);
            arrivalTimes.push_back(std::rand()%20);
        }
        std::sort(arrivalTimes.begin(), arrivalTimes.end());
        
        
        //Generating random "Jobs"
        for(size_t i = 0; i < 5; i++)
        {
            std::string jobName = "P" + std::to_string(i);
            jobsVector.push_back(Job(jobName, 1 + std::rand()%10 , 1 + std::rand()%10, arrivalTimes[i]));
            
        }
        
        
        
        RRVector = jobsVector;
        
        /*
         //These are used for whitebox testing
         
            RRVector.push_back(Job("P0", 9, 4, 0));
            RRVector.push_back(Job("P1", 9, 6, 2));
            RRVector.push_back(Job("P2", 1, 0, 12));
            RRVector.push_back(Job("P3", 3, 0, 13));
            RRVector.push_back(Job("P4", 3, 0, 13));
        */
    //-------------------------------------------------------------------------------
    //***************************** RUN FCFS TEST **********************************|
    //-------------------------------------------------------------------------------
        
        //Calculate the wait time
        for(size_t i = 0; i < jobsVector.size(); ++i)
        {
            jobsVector[i]._waitingTime = 0;
            for(size_t j = 0; j < i; j++)
            {
                jobsVector[i]._waitingTime += jobsVector[j]._burstTime;
            }
            if(jobsVector[i]._waitingTime < jobsVector[i]._arrivalTime)
                jobsVector[i]._waitingTime = 0;
            else
                jobsVector[i]._waitingTime -= jobsVector[i]._arrivalTime;
        }
        
        if(input == 1)
        {
            std::cout << "-------------------------------------- FCFS Results --------------------------------------\n\n";

            //Print table header
            std::cout.flags(std::ios::left);
            std::cout << std::setw(18) << "Process"
            << std::setw(18)
            << "Burst Time"
            << std::setw(18)
            << "Priority"
            << std::setw(18)
            << "Arrival Time"
            << std::setw(18)
            << "Waiting Time"
            << "\n------------------------------------------------------------------------------------------\n";
            
            //Print the vectors contents
            for (auto i = jobsVector.begin(); i != jobsVector.end(); ++i)
            {
                std::cout << std::setw(18) << i->_processName
                << std::setw(18)
                << i->_burstTime
                << std::setw(18)
                << i->_priority
                << std::setw(18)
                << i->_arrivalTime
                << std::setw(18)
                << i->_waitingTime << std::endl;
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
        

        else if(input == 2)
        {
            std::cout << "\nPlease enter a quantum value (integer):\t";
            
            while(!(std::cin >> cputimeQuantum))
            {
                if(std::cin.eof()||std::cin.bad())
                    break;
                
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Please enter a valid number:\t";
            }
            if (std::cin.eof())
            {
                std::cout << "No value enterd\n";
                break;
            }
            if (std::cin.bad())
            {
                std::cout<< "Input steam is bad\n";
                break;
            }
            
            if (cputimeQuantum <= 0)
                std::cout << "Please enter an number greater than 0:\nt";
            std::cout << "\n\n";
        
        
            std::cout << "Quantum Time: " << cputimeQuantum <<"\n\n";
            
            std::cout << "\n\n------------------------------------ RR Results -------------------------------------------\n\n";

            
          
            //create burst checker thingy
            std::vector<long long> burstTime;
            std::vector<unsigned> arrivalTime;
            for(size_t i = 0; i < RRVector.size(); i++)
            {
                burstTime.push_back(RRVector[i]._burstTime);
                arrivalTime.push_back( RRVector[i]._arrivalTime);
            }
            
            int processTime = 0;
            int totalWaitingTime = 0;
            while(true)
            {
                bool done = true;
                bool jobProcessed = false;
               // long long count = RRVector.size() -1;
                for(size_t i = 0; i < RRVector.size(); i++) //, count--)
                {
                    //If arival_time > processTime
                    if (arrivalTime[i] > processTime && jobProcessed)
                    {
                        if(i == RRVector.size()) //No jobs were ready
                        {
                            processTime ++; //Increase the time
                            done = false;
                        }
                        else
                        {
                            done = false;
                        }
                        //goto next job (i++)
                    }
                    else if (burstTime[i] > 0)
                    {
                        jobProcessed = true;
        
                       // burstTime[i] = burstTime[i] - cputimeQuantum;
                        if (burstTime[i] <= cputimeQuantum)
                        {
                            processTime +=   cputimeQuantum - burstTime[i];
                            totalWaitingTime += cputimeQuantum - burstTime[i];
                            RRVector[i]._waitingTime = totalWaitingTime - RRVector[i]._burstTime - arrivalTime[i];
                            burstTime[i] = 0;

                            if (RRVector[i]._waitingTime < 0)
                                RRVector[i]._waitingTime = 0;
                        }
                        else
                        {
                            done = false;
                            burstTime[i] = burstTime[i] - cputimeQuantum;
                            processTime += cputimeQuantum;
                            totalWaitingTime += cputimeQuantum;
                        }
                    }
                }
                if(done)
                    break;
            }

            //Print table header
            std::cout.flags(std::ios::left);
            std::cout << std::setw(18) << "Process"
            << std::setw(18)
            << "Burst Time"
            << std::setw(18)
            << "Priority"
            << std::setw(18)
            << "Arrival Time"
            << std::setw(18)
            << "Waiting Time"
            << "\n------------------------------------------------------------------------------------------\n";
            
            //Print the vectors contents
            for (auto i = RRVector.begin(); i != RRVector.end(); ++i)
            {
                std::cout << std::setw(18) << i->_processName
                << std::setw(18)
                << i->_burstTime
                << std::setw(18)
                << i->_priority
                << std::setw(18)
                << i->_arrivalTime
                << std::setw(18)
                << i->_waitingTime << std::endl;
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
    
        if (input == 3)
        {
            runCompare();
        }
        std::cout << "\n-------------------------------------------------------------------\n";
        std::cout << "|******************************************************************|\n";
        std::cout << "-------------------------------------------------------------------\n\n";
    }
    return 0;
}
