#include "EDF.hpp"
#include <limits>

ProcessParams *EDF::select_process(vector<ProcessParams *> processes)
{

    int index_of_priority_process = -1;
    int earliest_deadline = numeric_limits<int>::max();
    int earliest_total_time = -1;

    for (size_t i = 0; i < processes.size(); i++)
    {
        ProcessParams *process = processes[i];

        if (process->is_ready())
        {
            if (process->get_deadline_time() < earliest_deadline)
            {
                earliest_deadline = process->get_deadline_time();
                index_of_priority_process = i;
                earliest_total_time = process->get_total_time();
            }
            else if (process->get_deadline_time() == earliest_deadline)
            {
                if (process->get_total_time() > earliest_total_time)
                {
                    earliest_total_time = process->get_total_time();
                    index_of_priority_process = i;
                    earliest_deadline = process->get_deadline_time();
                }
            }
        }
    }

    if (index_of_priority_process == -1)
    {
        return nullptr;
    }

    return processes[index_of_priority_process];
}

int EDF::compare_and_return_priority_id(ProcessParams *p1, ProcessParams *p2)
{
    if (p1->get_deadline_time() <= p2->get_deadline_time())
    {
        return p1->get_id();
    }

    return p2->get_id();
}