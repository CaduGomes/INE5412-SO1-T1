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
    vector<ProcessParams *> read_file();
    File();

private:
    ifstream myfile;
};

#endif