//
//  algorithmCompare.hpp
//  SchedulingAlg
//
//  Created by Justin Grabowski on 12/11/18.
//  Copyright © 2018 Justin Grabowski. All rights reserved.
//

#ifndef algorithmCompare_hpp
#define algorithmCompare_hpp

#include <stdio.h>
#include <vector>
#include "Job.hpp"

void runCompare();

/*
* Print a prompt that will ask the user to input
*  the tesst data
*
* @return: vector<Job> jos; the vector
*  containing the Jobs that the algorithms will
*  run on
*/
std::vector<Job> getUsersData();


#endif /* algorithmCompare_hpp */
