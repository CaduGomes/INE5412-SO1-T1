#include "EDF.hpp"

ProcessParams *EDF::select_process(vector<ProcessParams *> processes)
{

    size_t index_of_priority_process = -1;
    int earliest_deadline = 0;

    for (size_t i = 0; i < processes.size(); i++)
    {
        ProcessParams *process = processes[i];

        if (process->is_ready())
        {
            if (process->get_deadline_time() > earliest_deadline)
            {
                earliest_deadline = process->get_deadline_time();
                index_of_priority_process = i;
            }
        }
    }

    if (index_of_priority_process == -1)
    {
        return nullptr;
    }

    return processes[index_of_priority_process];
}