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

struct Job
{
    //Constructor
    Job(std::string processName,unsigned burstTime,
        unsigned short priority, unsigned arrivalTime);
    
    std::string _processName;
    unsigned _burstTime;
    unsigned short _priority;
    unsigned _arrivalTime;
    unsigned _waitingTime;
    unsigned short getPriority() const;
};

#endif /* Job_hpp */
