//
//  algorithmCompare.cpp
//  SchedulingAlg
//
//  Created by Justin Grabowski on 12/11/18.
//  Copyright © 2018 Justin Grabowski. All rights reserved.
//

#include "algorithmCompare.hpp"
#include <iomanip>

void runCompare(){
    
    //Functions Local variables
    std::vector<Job> jobs = getUsersData();
    unsigned totalWaitTime = 0;
    unsigned averageWaitTime = 0;
    unsigned totalRRWaitTime = 0;
    unsigned avgRRTime = 0;
    unsigned cputimeQuantum = 0;
    //----------------------------------------
    
    
    std::cout << "Data Entered: \n\n";
    for (auto i = jobs.begin(); i != jobs.end(); ++i)
    {
        std::cout << i->_processName
        << "\tBurst Time: " << i->_burstTime
        << "\tPriority: " << i->_priority
        << "\tArrival Time: " << i->_arrivalTime << std::endl;
    }
    
    std::cout << "\n\n-----------------Running Comparison Tests-----------------\n\n";
    
    
    /******************** FCCFS ********************/
    
    {
        //Copy the jobs vector
        std::vector<Job> FCFS_jobs = jobs;
        
        std::cout << "----------------- FCFS Results -----------------\n\n ";
        
        //Calculate the wait times
        for(size_t i = 0; i < FCFS_jobs.size(); ++i)
        {
            FCFS_jobs[i]._waitingTime = 0;
            for(size_t j = 0; j < i; j++)
                FCFS_jobs[i]._waitingTime += FCFS_jobs[j]._burstTime;
        }
        
        //Print the vectors contents
        for (auto i = FCFS_jobs.begin(); i != FCFS_jobs.end(); ++i)
        {
            std::cout << i->_processName
            << std::setw(8)
            << "\tBurst Time: " << i->_burstTime
            << std::setw(16)
            << "\tPriority: " << i->_priority
            << std::setw(22)
            << "\tArrival Time: " << i->_arrivalTime
            << std::setw(18)
            << "\tWaiting Time: " << i->_waitingTime << std::endl;
        }
        
        //Calculate the average waiting time
        size_t numProcesses = 0;
        
        while(++numProcesses < FCFS_jobs.size())
        {
            totalWaitTime += FCFS_jobs[numProcesses]._waitingTime;
        }
        
        averageWaitTime = totalWaitTime/numProcesses;
        
        std::cout << "\n\nAverage Wait Time: " << averageWaitTime << "\n\n";
    }
    
    
    /******************** Round Robin ********************/

    {
        std::cout << "\n\n------------------ RR Results ------------------\n\n";
        std::vector<Job> RR_jobs = jobs;

        cputimeQuantum = 2;
        
        std::cout << "Quantum Time: " << cputimeQuantum <<"\n\n";
        

        //create burst checker thingy
        unsigned burstTime[RR_jobs.size()];
        for(size_t i = 0; i < RR_jobs.size(); ++i)
        {
            burstTime[i] = RR_jobs[i]._burstTime;
        }
        
        //Calculate the wait times for RR
        
        int t= 0;
        while(true)
        {
            bool finnished = true;
            
            for(int i = 0; i < RR_jobs.size(); i++)
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
                        RR_jobs[i]._waitingTime = t - burstTime[i];
                        burstTime[i] = 0;
                    }
                }
            }
            if(finnished == true)
                break;
        }
        
        //Print the vectors contents
        for (auto i = RR_jobs.begin(); i != RR_jobs.end(); ++i)
        {
            std::cout << i->_processName
            << std::setw(8)
            << "\tBurst Time: " << i->_burstTime
             << std::setw(16)
            << "\tPriority: " << i->_priority
             << std::setw(22)
            << "\tArrival Time: " << i->_arrivalTime
            << std::setw(18)
            << "\tWaiting Time: " << i->_waitingTime << std::endl;
        }
        
        //Calculate the average waiting time
        size_t numRRProcesses = 0;
        
        while(++numRRProcesses < RR_jobs.size())
        {
            totalRRWaitTime += RR_jobs[numRRProcesses]._waitingTime;
        }
        
        avgRRTime = totalRRWaitTime/numRRProcesses;
        
        std::cout << "\n\nAverage Wait Time: " << avgRRTime << "\n\n";
    }
    
    
}

std::vector<Job> getUsersData(){
    std::vector<Job> jobs;
    unsigned numJobs;
    
    //Temp data to create the jobs
    std::string _processName;
    unsigned _burstTime;
    unsigned short _priority;
    unsigned _arrivalTime;
    
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
        std::cout << "No value eneterd\n";
    if (std::cin.bad())
        std::cout<< "Input steam is bad\n";
    
    for(size_t i = 0; i < numJobs; i++)
    {
        
        std::string jobName = "P" + std::to_string(i);

        //Get the burst time
        std::cout << "Job P" << i << " burst time: ";
        while(!(std::cin>>_burstTime))
        {
            if(std::cin.eof()||std::cin.bad())
                break;
            
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid number:\t";
        }
        
        if (std::cin.eof())
            std::cout << "No value eneterd\n";
        if (std::cin.bad())
            std::cout<< "Input steam is bad\n";
        
        std::cout << "Job P" << i << " priority: ";
        
        //Get the priority
        while(!(std::cin>>_priority))
        {
            if(std::cin.eof()||std::cin.bad())
                break;
            
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid number:\t";
        }
        
        if (std::cin.eof())
            std::cout << "No value eneterd\n";
        if (std::cin.bad())
            std::cout<< "Input steam is bad\n";
        
        
        std::cout << "Job P" << i << " arrival time: ";
        
        //Get the arrival time
        while(!(std::cin>>_arrivalTime))
        {
            if(std::cin.eof()||std::cin.bad())
                break;
            
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid number:\t";
        }
        if (std::cin.eof())
            std::cout << "No value eneterd\n";
        if (std::cin.bad())
            std::cout<< "Input steam is bad\n";
        
        //Add the entered job to the 'jobs' vector
        jobs.push_back(Job(jobName, _burstTime, _priority, _arrivalTime));
        std::cout << "\n\n";
    }
    return jobs;
}
