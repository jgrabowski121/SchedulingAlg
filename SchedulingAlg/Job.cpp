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

Job::Job(std::string processName, unsigned burstTime,
         unsigned short priority, unsigned arrivalTime)
{
    _processName = processName;
    _burstTime = burstTime;
    _priority = priority;
    _arrivalTime = arrivalTime;
    _waitingTime = 0;
};

unsigned short Job::getPriority() const
{
    return _priority;
}

bool operator <(const Job &lhs, const Job &rhs)
{
    return lhs.getPriority() < rhs.getPriority();
}

