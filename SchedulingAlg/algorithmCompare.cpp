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
    
    
    
    int t_total = 0;
    while(true)
    {
        bool finnished = true;
        for(size_t i = 0; i < processes.size(); i++)
        {
            // **This job has not arrived yet**
            if (arrivalT[i] > t_total)
            {
                t_total++;
                i--;
            }
            //Process jobs that have arrived
            else if (arrivalT[i] <= t_total)
            {
                if (arrivalT[i] > cputimeQuantum)
                {
                    for (size_t j = 0; j < RR_jobs.size(); j++)
                    {
                        if (arrivalT[j] < arrivalT[i])
                        {
                            if(burstT[j] > 0)
                            {
                                finnished = false;
                                if (burstT[j] > cputimeQuantum)
                                {
                                    t_total = t_total + cputimeQuantum;
                                    burstT[j] = burstT[j] - cputimeQuantum;
                                    arrivalT[j] = arrivalT[j] + cputimeQuantum;
                                }
                                else
                                {
                                    t_total = t_total + burstT[j];
                                    processes[j]._waitingTime = t_total - burstT[j] - arrivalT[j];
                                    burstT[j] = 0;
                                }
                            }
                        }
                    }
                    if (burstT[i] > 0)
                    {
                        finnished = false;
                        if (burstT[i] > cputimeQuantum)
                        {
                            t_total = t_total + cputimeQuantum;
                            burstT[i] = burstT[i] - cputimeQuantum;
                            arrivalT[i] = arrivalT[i] + cputimeQuantum;
                        }
                        else
                        {
                            t_total = t_total + burstT[i];
                            processes[i]._waitingTime = t_total
                            - processes[i]._burstTime - processes[i]._arrivalTime;
                            burstT[i] = 0;
                        }
                    }
                }
                // These jobs can be done because they have arrived during the
                // quantums time frame
                else if(arrivalT[i] <= cputimeQuantum)
                {
                    if (burstT[i] > 0)
                    {
                        finnished = false; // there are more jobs to complete
                        if(burstT[i] > cputimeQuantum) // This process will not be complete after this iiteration
                        {
                            t_total += cputimeQuantum; //add the quantum duration
                            burstT[i] = burstT[i] - cputimeQuantum; // Subtract this cpu quantum from the burtTime remaining
                            arrivalT[i] = arrivalT[i] + cputimeQuantum;
                        }
                        else
                        {
                            t_total += burstT[i];
                            processes[i]._waitingTime = t_total - processes[i]._burstTime -
                            processes[i]._arrivalTime;
                            burstT[i] = 0;
                        }
                    }
                }
     
            }
        }
        if(finnished)
            break;
    }
        //-------------------------------------------------------

    int processTime = 0;
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
                    done = false;
                    //goto next job (i++)
            }
            else if (burstTime[i] > 0)
            {
                
                std::cout << "Calculating";
                burstTime[i] = burstTime[i] - cputimeQuantum;
                std::cout << "Burst Time: " << burstTime[i] << "\n";
                
                if (burstTime[i] <= 0)
                {
                    processTime += RR_jobs[i]._burstTime + burstTime[i];
                    RR_jobs[i]._waitingTime += processTime - RR_jobs[i]._burstTime - arrivalTime[i];
                    if (RR_jobs[i]._waitingTime < 0)
                        RR_jobs[i]._waitingTime = 0;
                }
                else
                {
                    done = false;
                    processTime += cputimeQuantum;
                    
                }
            }
            
        }
        if(done)
            break;
    }
    
/*
        int t = 0;
        while(true)
        {
            bool finnished = true;
            for(size_t i = 0; i < RR_jobs.size(); i++)
            {
                // Check for arrivals after t=0
                if (arrivalTime[i] <= t)
                {
                    if(arrivalTime[i] <= cputimeQuantum)
                    {
                        if (burstTime[i] > 0)
                        {
                            finnished = false;
                            if(burstTime[i] > cputimeQuantum) // This process will not be complete after this iiteration
                            {
                                t += cputimeQuantum;
                                burstTime[i] = burstTime[i] - cputimeQuantum;
                                arrivalTime[i] = arrivalTime[i] + cputimeQuantum;
                            }
                            else
                            {
                                t += burstTime[i];
                                RR_jobs[i]._waitingTime = t - RR_jobs[i]._burstTime -
                                RR_jobs[i]._arrivalTime;
                                burstTime[i] = 0;
                            }
                        }
                    }
                    else if (arrivalTime[i] > cputimeQuantum)
                    {
                        for (size_t j = 0; j < RR_jobs.size(); j++)
                        {
                            if (arrivalTime[j] < arrivalTime[i])
                            {
                                if(burstTime[j] > 0)
                                {
                                    finnished = false;
                                    if (burstTime[j] > cputimeQuantum)
                                    {
                                        t = t + cputimeQuantum;
                                        burstTime[j] = burstTime[j] - cputimeQuantum;
                                        arrivalTime[j] = arrivalTime[j] + cputimeQuantum;
                                    }
                                    else
                                    {
                                        t = t + burstTime[j];
                                        RR_jobs[j]._waitingTime = t - burstTime[j] - arrivalTime[j];
                                        burstTime[j] = 0;
                                    }
                                }
                            }
                        }
                        if (burstTime[i] > 0)
                        {
                            finnished = false;
                            if (burstTime[i] > cputimeQuantum)
                            {
                                t = t + cputimeQuantum;
                                burstTime[i] = burstTime[i] - cputimeQuantum;
                                arrivalTime[i] = arrivalTime[i] + cputimeQuantum;
                            }
                            else
                            {
                                t = t + burstTime[i];
                                RR_jobs[i]._waitingTime = t
                                - RR_jobs[i]._burstTime - RR_jobs[i]._arrivalTime;
                                burstTime[i] = 0;
                            }
                        }
                    }
                }
                else if (arrivalTime[i]> cputimeQuantum)
                {
                    t++;
                    i--;
                }
            }
            if(finnished)
                break;
            
        }
 */
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
        
        
        
        std::cout << "\n\n--------------------------------- RR Justin Results -------------------------------------------\n\n";
        outputFile << "\n\n-------------------------------- RR Justin Results -------------------------------------------\n\n";

    
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
        for (auto i = processes.begin(); i != processes.end(); ++i)
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
        size_t count = 0;
        int toalWait = 0;
        while(count < processes.size())
        {
            toalWait += processes[count]._waitingTime;
            count++;
        }
        
        
        std::cout << "\nTotal wait time: " << toalWait;
        std::cout << "\nNumber of processes: " <<count;
        avgRRTime = (double)toalWait/count;
        
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
     
    
    //Uncomment this for test data
    //jobs.push_back(Job("P1", 2 ,0, 0));
    //jobs.push_back(Job("P2", 6 ,0, 6));
    //jobs.push_back(Job("P3", 8 ,18, 18));
    //jobs.push_back(Job("P4", 4 ,24, 18));
    

    std::cout << "\n\n";
    
    return jobs;
}
