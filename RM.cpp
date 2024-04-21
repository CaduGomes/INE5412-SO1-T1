#include "RM.hpp"

ProcessParams *RM::select_process(vector<ProcessParams *> processes)
{

    int index_of_priority_process = -1;
    int highest_priority = 0;

    for (size_t i = 0; i < processes.size(); i++)
    {
        ProcessParams *process = processes[i];

        if (process->is_ready())
        {
            if (process->get_priority() > highest_priority)
            {
                highest_priority = process->get_priority();
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

int RM::compare_and_return_priority_id(ProcessParams *p1, ProcessParams *p2)
{
    if (p1->get_priority() > p2->get_priority())
    {
        return p1->get_id();
    }

    return p2->get_id();
}