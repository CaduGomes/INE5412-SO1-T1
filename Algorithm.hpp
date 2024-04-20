#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include <vector>

#include "ProcessParams.hpp"

class Algorithm
{
public:
    virtual ProcessParams *select_process(vector<ProcessParams *> processes) = 0;
};

#endif