#include "ProcessParams.hpp"

ProcessParams::ProcessParams(int creation_time, int duration_time, int period, int deadline_time, int priority, int period_quantity)
{
    ProcessParams::creation_time = creation_time;
    ProcessParams::duration_time = duration_time;
    ProcessParams::period = period;
    ProcessParams::deadline_time = deadline_time;
    ProcessParams::priority = priority;
    ProcessParams::period_quantity = period_quantity;
    ProcessParams::status = "new";
}

void ProcessParams::set_id(int id)
{
    ProcessParams::id = id;
}