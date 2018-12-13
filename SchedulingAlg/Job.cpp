//
//  Job.cpp
//  SchedulingAlg
//
//  Created by Justin Grabowski on 12/9/18.
//  Copyright © 2018 Justin Grabowski. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include "Job.hpp"

//Constructor
Job::Job(std::string processName, int burstTime,
         unsigned short priority, unsigned arrivalTime)
{
    _processName = processName;
    _burstTime = burstTime;
    _priority = priority;
    _arrivalTime = arrivalTime;
    _waitingTime = 0;
};



