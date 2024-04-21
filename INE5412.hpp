#ifndef INE5412_HPP
#define INE5412_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#include "Algorithm.hpp"

using namespace std;

class INE5412
{

public:
    INE5412(Algorithm *algorithm, vector<ProcessParams *> processes);

    void start();
    void check_processes_status();

    bool should_finish();

    void check_waiting_time();

    void print_processes_status();

    ~INE5412();

private:
    vector<ProcessParams *> stack_pointer;
    ProcessParams *program_counter = nullptr;
    string status; // "new" | "ready" | "running" | "finished" | "blocked"
    Algorithm *algorithm;
    int current_time = 0;
    int context_switches = 0;
    std::set<int> processesIds;
};

#endif