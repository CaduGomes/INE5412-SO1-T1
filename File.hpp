#ifndef FILE_HPP
#define FILE_HPP
#include <iostream>
#include <fstream>
#include <vector>

#include "ProcessParams.hpp"

using namespace std;

class File
{

public:
    void read_file();
    void print_processes_params();
    File();  // This is the constructor declaration
    ~File(); // This is the destructor: declaration

private:
    ifstream myfile;
    vector<ProcessParams *> processes;
};

#endif