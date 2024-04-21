#include "ProcessParams.hpp"

using namespace std;

ProcessParams::ProcessParams(int creation_time, int duration_time, int period_time, int deadline_time, int priority, int period_quantity)
{
    ProcessParams::creation_time = creation_time;
    ProcessParams::duration_time = duration_time;
    ProcessParams::period_time = period_time;
    ProcessParams::deadline_time = deadline_time;
    ProcessParams::priority = priority;
    ProcessParams::period_quantity = period_quantity;
    ProcessParams::status = "new";
}

ProcessParams::ProcessParams(ProcessParams p, int creation_time, int deadline_time)
{
    ProcessParams::creation_time = creation_time;
    ProcessParams::duration_time = p.duration_time;
    ProcessParams::period_time = p.period_time;
    ProcessParams::deadline_time = deadline_time;
    ProcessParams::priority = p.priority;
    ProcessParams::period_quantity = 1;
    ProcessParams::status = "new";
    ProcessParams::id = p.id;
}

ProcessParams::ProcessParams(ProcessParams *p)
{
    ProcessParams::creation_time = p->creation_time;
    ProcessParams::duration_time = p->duration_time;
    ProcessParams::period_time = p->period_time;
    ProcessParams::deadline_time = p->deadline_time;
    ProcessParams::priority = p->priority;
    ProcessParams::period_quantity = p->period_quantity;
    ProcessParams::status = p->status;
    ProcessParams::id = p->id;
}

void ProcessParams::set_id(int id)
{
    ProcessParams::id = id;
}

bool ProcessParams::is_ready()
{
    if (status == "ready")
    {
        return true;
    }
    return false;
}

void ProcessParams::run(int current_time)
{
    total_time++;

    if (start_time == -1)
    {
        start_time = current_time;
    }

    if (current_time == deadline_time)
    {
        status = "finished";
        finish_time = current_time;
        return;
    }

    if (total_time == duration_time)
    {
        status = "finished";
        finish_time = current_time + 1;
        return;
    }

    status = "running";
}