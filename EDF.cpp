#include "EDF.hpp"

ProcessParams *EDF::select_process(vector<ProcessParams *> processes)
{
    ProcessParams *selected_process = processes[0];
    for (size_t i = 1; i < processes.size(); i++)
    {
        // if (processes[i]->get_deadline() < selected_process->get_deadline())
        // {
        //     selected_process = processes[i];
        // }
    }
    return selected_process;
}