#ifndef EDF_HPP
#define EDF_HPP
#include <iostream>
#include <fstream>
#include <vector>

#include "Algorithm.hpp"

using namespace std;

class EDF : public Algorithm
{

public:
    ~EDF(){};
    ProcessParams *select_process(vector<ProcessParams *> processes);
    int compare_and_return_priority_id(ProcessParams *p1, ProcessParams *p2);
};

#endif