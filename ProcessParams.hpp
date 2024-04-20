#ifndef PROCESS_PARAMS_HPP
#define PROCESS_PARAMS_HPP
#include <fstream>

using namespace std;

class ProcessParams
{
public:
    friend ostream &operator<<(ostream &os, const ProcessParams &p)
    {
        os << "Id = " << p.id << " creation time = " << p.creation_time << " duration = " << p.duration_time << " priority = " << p.priority << " period = " << p.period << " deadline = " << p.deadline_time << " period_quantity = " << p.period_quantity << endl;
        return os;
    }

    ProcessParams(int creation_time, int duration_time, int period, int priority, int deadline, int period_quantity);

    void set_id(int id);

    int get_id() { return id; }

    int get_creation_time() { return creation_time; }

    void set_finish_time(int finish_time) { this->finish_time = finish_time; }

    void set_total_time(int total_time) { this->total_time = total_time; }

    void set_status(string status) { this->status = status; }

    int get_period() { return period; }

    int get_priority() { return priority; }

    int get_period_quantity() { return period_quantity; }

    int get_finish_time() { return finish_time; }

    bool is_ready()
    {
        if (status == "ready")
        {
            return true;
        }
        return false;
    }

    bool is_finished(int current_time)
    {

        if (status == "finished")
        {
            return true;
        }

        if (start_time == 0)
        {
            start_time = current_time;
        }

        if (duration_time == total_time)
        {
            status = "finished";
            finish_time = current_time;
            return true;
        }

        total_time++;
        return false;
    }

    string get_status() { return status; }

private:
    int id;

    int duration_time; // o tempo que o processo leva para terminar
    int creation_time; // quando o processo deve mudar para ready
    int deadline_time; // o tempo limite para o processo terminar

    int finish_time;    // o momento em que o processo terminou
    int start_time = 0; // o momento em que o processo terminou
    int total_time = 0; // o tempo total que o processo levou para terminar

    int priority;
    int period;
    int period_quantity;

    string status; // "new" | "ready" | "running" | "finished"
};

#endif