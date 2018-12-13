//
//  algorithmCompare.cpp
//  SchedulingAlg
//
//  Created by Justin Grabowski on 12/11/18.
//  Copyright © 2018 Justin Grabowski. All rights reserved.
//

#include "algorithmCompare.hpp"
#include <iomanip>
#include <fstream>
#include <algorithm>


//This funciton will compare the FCFS and Round Robin algorithms
// on the same set of data
void runCompare(){
    
    //Functions Local variables
    std::vector<Job> jobs = getUsersData();
    int totalWaitTime = 0;
    double averageWaitTime = 0;
    int totalRRWaitTime = 0;
    double avgRRTime = 0;
    unsigned cputimeQuantum = 0;
    
    std::ofstream outputFile;
    outputFile.open("schedularAnalytics.txt");
    
    outputFile << "\n\n----------------------------------Running Comparison Tests--------------------------------\n\n";
    std::cout << "\n\n----------------------------------Running Comparison Tests--------------------------------\n\n";
    
    /******************** FCCFS ********************/
    
    
        //Copy the jobs vector
        std::vector<Job> FCFS_jobs = jobs;
        
        outputFile << "-------------------------------------- FCFS Results --------------------------------------\n\n";
        std::cout << "-------------------------------------- FCFS Results --------------------------------------\n\n";
    
    
    for(size_t i = 0; i < FCFS_jobs.size(); ++i)
    {
        FCFS_jobs[i]._waitingTime = 0;
        for(size_t j = 0; j < i; j++)
        {
            FCFS_jobs[i]._waitingTime += FCFS_jobs[j]._burstTime;
        }
        if(FCFS_jobs[i]._waitingTime < FCFS_jobs[i]._arrivalTime)
            FCFS_jobs[i]._waitingTime = 0;
        else
            FCFS_jobs[i]._waitingTime -= FCFS_jobs[i]._arrivalTime;
        
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
        
        outputFile.flags(std::ios::left);
        outputFile << std::setw(18)<< "Process"
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
        for (auto i = FCFS_jobs.begin(); i != FCFS_jobs.end(); ++i)
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
            
            outputFile << std::setw(18) << i->_processName
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
        totalWaitTime = 0;
        
        while(numProcesses < FCFS_jobs.size())
        {
            totalWaitTime += FCFS_jobs[numProcesses]._waitingTime;
            numProcesses++;
        }
    
        //Calculate the average wait time for the FCFS test
        averageWaitTime = (double)totalWaitTime/numProcesses;
        
        std::cout << "\n\nAverage Wait Time: " << averageWaitTime << "\n\n";
        outputFile << "\n\nAverage Wait Time: " << averageWaitTime << "\n\n";
    

    
    /******************** Round Robin ********************/

    
        std::cout << "\n\n------------------------------------ RR Results -------------------------------------------\n\n";
        outputFile << "\n\n----------------------------------- RR Results -------------------------------------------\n\n";

        std::vector<Job> RR_jobs = jobs;

        cputimeQuantum = 2;
        
        std::cout << "Quantum Time: " << cputimeQuantum <<"\n\n";
        outputFile << "Quantum Time: " << cputimeQuantum <<"\n\n";
        
        //create burst checker thingy
        int burstTime[RR_jobs.size()];
        unsigned arrivalTime[RR_jobs.size()];
        for(size_t i = 0; i < RR_jobs.size(); i++)
        {
            burstTime[i] = RR_jobs[i]._burstTime;
            arrivalTime[i] = RR_jobs[i]._arrivalTime;
        }
    
        int burstT[RR_jobs.size()];
        unsigned arrivalT[RR_jobs.size()];
    
        for(size_t i = 0; i < RR_jobs.size(); i++)
        {
            burstT[i] = RR_jobs[i]._burstTime;
            arrivalT[i] = RR_jobs[i]._arrivalTime;
        }
        //Calculate the wait times for RR
        
        int totalTime = 0;
        std::cout << "Total Time: " << totalTime << "\n\n";
        
       //-------------------------------------------------------
    
        std::vector<Job> processes = jobs;
    
        //-------------------------------------------------------

    int processTime = 0;
    int totalWaitingTime = 0;
    while(true)
    {
        bool done = true;
        size_t count = RR_jobs.size()-1;
        for(size_t i = 0; i < RR_jobs.size(); i++, count--)
        {
            //If arival_time > processTime
            if (arrivalTime[i] > processTime)
            {
                if(count == 0) //No jobs were ready
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
                burstTime[i] = burstTime[i] - cputimeQuantum;
                if (burstTime[i] <= 0)
                {
                    processTime += RR_jobs[i]._burstTime + burstTime[i];
                    totalRRWaitTime += RR_jobs[i]._burstTime + burstTime[i];
                    RR_jobs[i]._waitingTime += totalWaitingTime - arrivalTime[i];
                    if (RR_jobs[i]._waitingTime < 0)
                        RR_jobs[i]._waitingTime = 0;
                }
                else
                {
                    done = false;
                    processTime += cputimeQuantum;
                    totalWaitingTime += cputimeQuantum;
                }
            }
        }
        if(done)
            break;
    }

        //--------------------------------
    
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
    
        outputFile.flags(std::ios::left);
        outputFile << std::setw(18)<< "Process"
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
        for (auto i = RR_jobs.begin(); i != RR_jobs.end(); ++i)
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
            
            outputFile << std::setw(18) << i->_processName
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
        totalRRWaitTime = 0;
        while(numRRProcesses < RR_jobs.size())
        {
            totalRRWaitTime += RR_jobs[numRRProcesses]._waitingTime;
            numRRProcesses++;
        }
        
        std::cout << "\nTotal wait time: " << totalRRWaitTime;
        std::cout << "\nNumber of processes: " <<numRRProcesses;
        avgRRTime = (double)totalRRWaitTime/numRRProcesses;
        
        outputFile << "\n\nAverage Wait Time: " << avgRRTime << "\n\n";
        std::cout << "\n\nAverage Wait Time: " << avgRRTime << "\n\n";
    
 
    outputFile.close();
}

std::vector<Job> getUsersData(){
    std::vector<Job> jobs;
    unsigned numJobs;
    
    //Temp data to create the jobs
    std::string _processName;
    
    //Get users input:
    std::cout << "Enter the number of jobs to test: ";
    while(!(std::cin>>numJobs))
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
        
    }
    if (std::cin.bad())
    {
        std::cout<< "Input steam is bad\n";
        //Do something
    }
    
    std::vector<int> arrivalTimes;
    //Generating and sorting arrival times
    for(size_t i = 0; i< numJobs; i++)
    {
        if(i == 0)
            arrivalTimes.push_back(0);
        arrivalTimes.push_back(std::rand()%20);
    }
    std::sort(arrivalTimes.begin(), arrivalTimes.end());
    
    
    //Generating random "Jobs"
    for(size_t i = 0; i < numJobs; i++)
    {
        std::string jobName = "P" + std::to_string(i);
        jobs.push_back(Job(jobName, 1 + std::rand()%10 , 1 + std::rand()%10, arrivalTimes[i]));
        
    }

    std::cout << "\n\n";
    
    return jobs;
}
