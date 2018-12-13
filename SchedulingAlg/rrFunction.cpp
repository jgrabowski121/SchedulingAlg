//
//  rrFunction.cpp
//  SchedulingAlg
//
//  Created by Justin Grabowski on 12/12/18.
//  Copyright © 2018 Justin Grabowski. All rights reserved.
//

#include "rrFunction.hpp"
#include "Job.hpp"




/*

std::vector<Job> processes = jobs;
while(true)
{
    bool finnished = true;
    bool foundNext = false;
    bool jobProccessed = false;
    for(size_t i = 0; i < processes.size(); i++)
    {
        if(burstT[i] > 0) //This process has not finnished
        {
            finnished = false;
            foundNext = false;
            if(processes[i]._arrivalTime > totalTime) //Job cannot be processed yet
            {
                for(size_t j = i; j < processes.size(); j++)
                {
                    if(processes[j]._arrivalTime <= totalTime) // There will be a job processed this round of checking
                    {
                        foundNext = true;
                        continue;
                    }
                }
                if (!foundNext && jobProccessed == false)
                {
                    totalTime = totalTime + cputimeQuantum; //Increace time to allow late arrivals to begin
                    //std::cout << "Not Found Next: Total Time " << totalTime << "\n";
                }
                continue;
                
            }
            else if(burstT[i] > cputimeQuantum) // This process will not be complete after this iiteration
            {
                totalTime += cputimeQuantum;
                burstT[i] -= cputimeQuantum;
                jobProccessed = true;
            }
            else
            {
                totalTime = totalTime + burstT[i];
                processes[i]._waitingTime = totalTime - processes[i]._burstTime;
                burstT[i] = 0;
                jobProccessed = true;
            }
        }
    }
    if(finnished == true)
        break;
    
}
*/
/*

int t = 0;
while(true)
{
    bool finnished = true;
    for(size_t i = 0; i < RR_jobs.size(); i++)
    {
        if (arrivalTime[i] > t)
        {
            t++;
            //i--;
        }
        
        // Check for arrivals after t=0
        else if (arrivalTime[i] <= t)
        {
            if(arrivalTime[i] <= cputimeQuantum)
            {
                if (burstTime[i] > 0)
                {
                    finnished = false; // there are more jobs to complete
                    if(burstTime[i] > cputimeQuantum) // This process will not be complete after this iiteration
                    {
                        t += cputimeQuantum; //add the quantum duration
                        burstTime[i] = burstTime[i] - cputimeQuantum; // Subtract this cpu quantum from the burtTime remaining
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
    }
    if(finnished)
        break;
    
    }


 */

/*
 
 //Push the processes that start at 0 into the readyQueue
 std::vector<Job> readyQueue;
 std::vector<Job> waitingQueue;
 for(size_t i = 0; i < processes.size(); i++)
 {
 if (processes[i]._arrivalTime == 0)
 readyQueue.push_back(processes[i]);
 else
 waitingQueue.push_back(processes[i]);
 
 }
 
 
 
 
 int t_total= 0;
 while(true)
 {
 bool finnished = true;
 // bool jobProcessed = false;
 
 for(int i = 0; i < processes.size(); i++)
 {
 //Use the ready queue
 for(int i = 0; i < readyQueue.size(); i++)
 {
 //Check for new arrivals
 for(size_t i = 0; i < waitingQueue.size(); i++)
 {
 if (waitingQueue[i]._arrivalTime <= t_total)
 {
 readyQueue.push_back(waitingQueue[i]);
 waitingQueue.pop_back();
 std::cout<< "Job arrived: " << readyQueue.back()._processName << "\n";
 }
 
 }
 if(readyQueue[i]._burstTime > 0) //This process has not finnished
 {
 finnished = false;
 
 if(readyQueue[i]._burstTime > cputimeQuantum)
 {
 t_total += cputimeQuantum;
 readyQueue[i]._burstTime -= cputimeQuantum;
 }
 else
 {
 t_total = t_total + readyQueue[i]._burstTime;
 readyQueue[i]._waitingTime = t_total - readyQueue[i]._burstTime;
 std::cout << "Waiting Time: " << readyQueue[i]._waitingTime;
 readyQueue[i]._burstTime = 0;
 }
 }
 }
 }
 if(finnished == true)
 break;
 }
 */

/*
 int t_total= 0;
 while(true)
 {
 bool finnished = true;
 //int totalTime = 0;
 bool foundNext = false;
 for(size_t i = 0; i < processes.size(); i++)
 {
 if(burstT[i] > 0) //This process has not finnished
 {
 finnished = false;
 foundNext = false;
 if(processes[i]._arrivalTime > t_total) //Job cannot be processed yet
 {
 for(size_t j = i; j < processes.size(); j++)
 {
 if(processes[j]._arrivalTime <= t_total) // There will be a job processed this round of checking
 {
 foundNext = true;
 continue;
 }
 }
 if (!foundNext)
 {
 t_total = t_total + cputimeQuantum; //Increace time to allow late arrivals to begin
 std::cout << "Not Found Next: Total Time " << t_total << "\n";
 }
 continue;
 
 }
 else if(burstT[i] > cputimeQuantum) // This process will not be complete after this iiteration
 {
 t_total += cputimeQuantum;
 burstT[i] -= cputimeQuantum;
 }
 else
 {
 t_total = t_total + burstTime[i];
 processes[i]._waitingTime = t_total - processes[i]._burstTime;
 burstT[i] = 0;
 }
 }
 }
 if(finnished == true)
 break;
 }
 */
/*
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
*/







//Final
/*
int processTime = 0;
while(true)
{
    bool done = true;
    size_t count = RR_jobs.size()-1;
    for(size_t i = 0; i < RR_jobs.size(); i++, count--)
    {
        std::cout << "Top of for loop\n";
        //If arival_time > processTime
        if (arrivalTime[i] > processTime)
        {
            std::cout << "Arrival time to late" << "\n";
            
            if(count == 0) //No jobs were ready
            {
                processTime += cputimeQuantum;
                done = false;
            }
            else
                done = false;
            //i++; //goto next job (i++)
        }
        //else
        
        
        else if (burstTime[i] > 0)
        {
            
            std::cout << "Calculating";
            burstTime[i] = burstTime[i] - cputimeQuantum;
            std::cout << "Burst Time: " << burstTime[i] << "\n";
            
            if (burstTime[i] <= 0)
            {
                processTime += RR_jobs[i]._burstTime + burstTime[i];
                RR_jobs[i]._waitingTime += processTime - RR_jobs[i]._arrivalTime - RR_jobs[i]._burstTime;
            }
            else
            {
                done = false;
                processTime += cputimeQuantum;
                
            }
        }
        // burstTime = burstTime - quantum
        //if (burstTime > 0)
        // This job is not done//
        
        }
        if(done)
        break;
        }
*/


/*
int processTime = 0;
while(true)
{
    bool temps = false;
    bool done = true;
    size_t count = RR_jobs.size()-1;
    for(size_t i = 0; i < RR_jobs.size(); i++, count--)
    {
        std::cout << "Top of for loop\n";
        //If arival_time > processTime
        if (arrivalTime[i] > processTime)
        {
            std::cout << "Arrival time to late" << "\n";
            
            if(count == 0) //No jobs were ready
            {
                processTime += cputimeQuantum;
                done = false;
            }
            else
                done = false;
            //i++; //goto next job (i++)
        }
        //else
        
        
        else if (burstTime[i] <= cputimeQuantum && burstTime[i] > 0)
        {
            processTime += burstTime[i];
            burstTime[i] = 0;
            temps = true;
        }
        else if (burstTime[i] > 0)
        {
            
            std::cout << "Calculating";
            burstTime[i] = burstTime[i] - cputimeQuantum;
            processTime += cputimeQuantum;
            std::cout << "Burst Time: " << burstTime[i] << "\n";
            done = false;
        }
        
        else if (burstTime[i] == 0 && temps == 1)
        {
            //processTime += RR_jobs[i]._burstTime;// + burstTime[i];
            RR_jobs[i]._waitingTime += processTime - arrivalTime[i] - burstTime[i];
            temps = 0;
        }
        else
        {
            done = false;
            processTime += cputimeQuantum;
            
        }
        
        // burstTime = burstTime - quantum
        //if (burstTime > 0)
        // This job is not done//
        
        }
        if(done)
        break;
        }
*/
