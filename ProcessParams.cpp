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

ProcessParams::ProcessParams(const ProcessParams &p, int creation_time, int deadline_time)
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

ProcessParams::ProcessParams(const ProcessParams &p)
{
    ProcessParams::creation_time = p.creation_time;
    ProcessParams::duration_time = p.duration_time;
    ProcessParams::period_time = p.period_time;
    ProcessParams::deadline_time = p.deadline_time;
    ProcessParams::priority = p.priority;
    ProcessParams::period_quantity = p.period_quantity;
    ProcessParams::status = p.status;
    ProcessParams::id = p.id;
}

void ProcessParams::set_id(int id)
{
    ProcessParams::id = id;
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

int ProcessParams::get_id()
{
    return id;
}

int ProcessParams::get_creation_time()
{
    return creation_time;
}

int ProcessParams::get_deadline_time()
{
    return deadline_time;
}

int ProcessParams::get_period_time()
{
    return period_time;
}

int ProcessParams::get_priority()
{
    return priority;
}

int ProcessParams::get_period_quantity()
{
    return period_quantity;
}

int ProcessParams::get_turnaround_time()
{
    return finish_time - creation_time;
}

bool ProcessParams::was_preemptive()
{
    return finish_time == deadline_time;
}

int ProcessParams::get_waiting_time()
{
    return waiting_time;
}

void ProcessParams::add_wait_time() { waiting_time++; }

void ProcessParams::set_status(string status)
{
    this->status = status;
}

int ProcessParams::get_total_time()
{
    return total_time;
}

void ProcessParams::set_finish_time(int finish_time)
{
    this->finish_time = finish_time;
}

bool ProcessParams::is_ready()
{
    return status == "ready";
}
bool ProcessParams::is_finished()
{
    return status == "finished";
}
bool ProcessParams::is_running()
{
    return status == "running";
}
bool ProcessParams::is_new()
{
    return status == "new";
}
