#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include <vector>

#include "ProcessParams.hpp"

class Algorithm
{
public:
    virtual ProcessParams *select_process(vector<ProcessParams *> processes) = 0;
    virtual int compare_and_return_priority_id(ProcessParams *p1, ProcessParams *p2) = 0;
};

#endif