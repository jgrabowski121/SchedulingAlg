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

void runCompare(){
    
    //Functions Local variables
    std::vector<Job> jobs = getUsersData();
    unsigned totalWaitTime = 0;
    double averageWaitTime = 0;
    unsigned totalRRWaitTime = 0;
    double avgRRTime = 0;
    unsigned cputimeQuantum = 0;
    
    std::ofstream outputFile;
    outputFile.open("schedularAnalytics.txt");
    
    //----------------------------------------
    
    outputFile << "Data Generated: \n\n";
    std::cout << "Data Generated: \n\n";
    for (auto i = jobs.begin(); i != jobs.end(); ++i)
    {
        std::cout << i->_processName
        << "\tBurst Time: " << i->_burstTime
        << "\tPriority: " << i->_priority
        << "\tArrival Time: " << i->_arrivalTime << std::endl;
        
        
        outputFile << "\tBurst Time: " << i->_burstTime
        << "\tPriority: " << i->_priority
        << "\tArrival Time: " << i->_arrivalTime << std::endl;
    }
    
    outputFile << "\n\n----------------------------------Running Comparison Tests--------------------------------\n\n";
    std::cout << "\n\n----------------------------------Running Comparison Tests--------------------------------\n\n";
    
    /******************** FCCFS ********************/
    
    {
        //Copy the jobs vector
        std::vector<Job> FCFS_jobs = jobs;
        
        outputFile << "-------------------------------------- FCFS Results --------------------------------------\n\n";
        std::cout << "-------------------------------------- FCFS Results --------------------------------------\n\n";
        
        
        //Calculate the wait times
        for(size_t i = 0; i < FCFS_jobs.size(); ++i)
        {
            FCFS_jobs[i]._waitingTime = 0;
            for(size_t j = 0; j < i; j++)
            {
                FCFS_jobs[i]._waitingTime += FCFS_jobs[j]._burstTime;
            }
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
        
        while(++numProcesses < FCFS_jobs.size())
        {
            totalWaitTime += FCFS_jobs[numProcesses]._waitingTime;
            std::cout << totalWaitTime<<"\n";
        }
        
       // std::cout << "totalWaitTime " << totalWaitTime;
       // std::cout << "numProcesses " << numProcesses;
        averageWaitTime =(double)totalWaitTime/numProcesses;
        
        std::cout << "\n\nAverage Wait Time: " << averageWaitTime << "\n\n";
        outputFile << "\n\nAverage Wait Time: " << averageWaitTime << "\n\n";
    }
    
    
    /******************** Round Robin ********************/

    {
        std::cout << "\n\n------------------------------------ RR Results -------------------------------------------\n\n";
        outputFile << "\n\n----------------------------------- RR Results -------------------------------------------\n\n";

        std::vector<Job> RR_jobs = jobs;

        cputimeQuantum = 2;
        
        std::cout << "Quantum Time: " << cputimeQuantum <<"\n\n";
        outputFile << "Quantum Time: " << cputimeQuantum <<"\n\n";
        
        //create burst checker thingy
        unsigned burstTime[RR_jobs.size()];
        for(size_t i = 0; i < RR_jobs.size(); ++i)
        {
            burstTime[i] = RR_jobs[i]._burstTime;
        }
        
        //Calculate the wait times for RR
        
       int totalTime = 0;
        std::cout << "Total Time: " << totalTime << "\n\n";
        
        while(true)
        {
            bool finnished = true;
            //int totalTime = 0;
            bool foundNext = false;
            for(size_t i = 0; i < RR_jobs.size(); i++)
            {
                if(burstTime[i] > 0) //This process has not finnished
                {
                    finnished = false;
                    foundNext = false;
                    if(RR_jobs[i]._arrivalTime > totalTime) //Job cannot be processed yet
                    {
                        for(size_t j = i; j < RR_jobs.size(); j++)
                        {
                            if(RR_jobs[j]._arrivalTime <= totalTime) // There will be a job processed this round of checking
                            {
                                foundNext = true;
                                continue;
                            }
                        }
                        if (!foundNext)
                        {
                            totalTime = totalTime + cputimeQuantum; //Increace time to allow late arrivals to begin
                            std::cout << "Not Found Next: Total Time " << totalTime << "\n";
                        }
                        continue;
                    
                    }
                    else if(burstTime[i] > cputimeQuantum) // This process will not be complete after this iiteration
                    {
                        totalTime += cputimeQuantum;
                        burstTime[i] -= cputimeQuantum;
                    }
                    else
                    {
                        totalTime = totalTime + burstTime[i];
                        RR_jobs[i]._waitingTime = totalTime - RR_jobs[i]._burstTime;
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
            
            //Write to the output file
            outputFile << i->_processName
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
        
        
   
        avgRRTime = (double)totalRRWaitTime/numRRProcesses;
        
        outputFile << "\n\nAverage Wait Time: " << avgRRTime << "\n\n";
        std::cout << "\n\nAverage Wait Time: " << avgRRTime << "\n\n";
    }
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
        arrivalTimes.push_back(std::rand()%10);
    }
    std::sort(arrivalTimes.begin(), arrivalTimes.end());
    
    //Generating random "Jobs"
    for(size_t i = 0; i < numJobs; i++)
    {
        std::string jobName = "P" + std::to_string(i);
        jobs.push_back(Job(jobName, std::rand()%10 , std::rand()%10, arrivalTimes[i]));
        
    }

    std::cout << "\n\n";
    
    return jobs;
}
