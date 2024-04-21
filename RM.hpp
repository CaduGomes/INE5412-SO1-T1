#ifndef RM_HPP
#define RM_HPP
#include <iostream>
#include <fstream>
#include <vector>

#include "Algorithm.hpp"

using namespace std;

class RM : public Algorithm
{

public:
    ProcessParams *select_process(vector<ProcessParams *> processes);
    int compare_and_return_priority_id(ProcessParams *p1, ProcessParams *p2);
};

#endif