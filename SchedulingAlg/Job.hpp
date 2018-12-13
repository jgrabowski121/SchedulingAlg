//
//  Job.hpp
//  SchedulingAlg
//
//  Created by Justin Grabowski on 12/9/18.
//  Copyright © 2018 Justin Grabowski. All rights reserved.
//

#ifndef Job_hpp
#define Job_hpp

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include "Job.hpp"


//Creating the onject to hold processes
struct Job
{
    //Constructor
    Job(std::string processName,int burstTime,
        unsigned short priority, unsigned arrivalTime);
    
    std::string _processName;
    int _burstTime;
    unsigned short _priority;
    unsigned _arrivalTime;
    int _waitingTime;
    unsigned short getPriority() const;
};

#endif /* Job_hpp */
