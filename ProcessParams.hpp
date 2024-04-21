#ifndef PROCESS_PARAMS_HPP
#define PROCESS_PARAMS_HPP
#include <fstream>
#include <iostream>

using namespace std;

class ProcessParams
{
public:
    ProcessParams(int creation_time, int duration_time, int period_time, int priority, int deadline, int period_quantity);

    ProcessParams(const ProcessParams &p, int creation_time, int deadline_time);

    ProcessParams(const ProcessParams &p);

    void set_id(int id);

    int get_id();

    int get_creation_time();

    int get_deadline_time();

    int get_period_time();

    int get_priority();

    int get_period_quantity();

    int get_turnaround_time();

    bool was_preemptive();

    int get_waiting_time();

    void add_wait_time();

    void set_status(string status);

    int get_total_time();

    void set_finish_time(int finish_time);

    bool is_ready();
    bool is_finished();
    bool is_running();
    bool is_new();

    void run(int current_time);

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