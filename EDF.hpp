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
    ProcessParams *select_process(vector<ProcessParams *> processes);

private:
};

#endif