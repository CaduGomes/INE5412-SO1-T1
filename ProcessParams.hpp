#ifndef PROCESS_PARAMS_HPP
#define PROCESS_PARAMS_HPP
#include <fstream>
#include <iostream>

using namespace std;

class ProcessParams
{
public:
    friend ostream &operator<<(ostream &os, const ProcessParams &p)
    {
        os << "Id = " << p.id << " status = " << p.status << " total = " << p.total_time << " creation time = " << p.creation_time << " duration = " << p.duration_time << " priority = " << p.priority << " period = " << p.period_time << " deadline = " << p.deadline_time << " period_quantity = " << p.period_quantity << endl;
        return os;
    }

    ProcessParams(int creation_time, int duration_time, int period_time, int priority, int deadline, int period_quantity);

    ProcessParams(const ProcessParams &p, int creation_time, int deadline_time);
    ProcessParams(const ProcessParams &p);

    void set_id(int id);

    int get_id() { return id; }

    int get_creation_time() { return creation_time; }

    int get_deadline_time() { return deadline_time; }

    int get_period_time() { return period_time; }

    int get_priority() { return priority; }

    int get_period_quantity() { return period_quantity; }

    int get_turnaround_time() { return finish_time - creation_time; }

    bool was_preemptive() { return finish_time == deadline_time; }

    int get_waiting_time() { return waiting_time; }

    void add_wait_time() { waiting_time++; }

    void set_status(string status) { this->status = status; }

    int get_total_time() { return total_time; }

    void set_finish_time(int finish_time) { this->finish_time = finish_time; }

    bool is_ready();

    void run(int current_time);

    string get_status() { return status; }

private:
    int id;

    int duration_time = 0; // o tempo que o processo leva para terminar
    int deadline_time = 0; // o tempo limite para o processo terminar
    int period_time = 0;   // o tempo que o processo deve esperar para ser executado novamente

    int creation_time = 0; // o momento em que o processo mudou para ready
    int finish_time = 0;   // o momento em que o processo mudou para finished
    int start_time = -1;   // o momento em que o processo mudou para running

    int total_time = 0; // o tempo total que o processo levou para terminar

    int waiting_time = 0; // o tempo que o processo esperou para ser executado

    int priority = 0;
    int period_quantity = 0;

    string status; // "new" | "ready" | "running" | "finished"
};

#endif