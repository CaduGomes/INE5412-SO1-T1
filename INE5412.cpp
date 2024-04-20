#include "INE5412.hpp"
#include <unistd.h>

INE5412::INE5412(Algorithm *algorithm, vector<ProcessParams *> processes)
{
    INE5412::algorithm = algorithm;
    INE5412::stack_pointer = processes;
}

INE5412::~INE5412()
{
    delete INE5412::algorithm;
    vector<ProcessParams *>::iterator iter = INE5412::stack_pointer.begin();
    for (iter = INE5412::stack_pointer.begin(); iter < INE5412::stack_pointer.end(); iter++)
    {
        delete *iter;
    }
}

void INE5412::check_process_status()
{
    vector<ProcessParams *>::iterator iter = this->stack_pointer.begin();

    // Se o creation_time do processo for igual ao current_time e o status for "new", muda o status para "ready"
    for (iter = this->stack_pointer.begin(); iter < stack_pointer.end(); iter++)
    {
        ProcessParams *p = *iter;
        if (p->get_creation_time() == this->current_time && p->get_status() == "new")
        {
            p->set_status("ready");
            cout << "Process " << p->get_id() << " is ready" << endl;
        }
    }
}

void INE5412::start()
{
    while (true)
    {
        bool all_processes_finished = true;
        for (ProcessParams *p : this->stack_pointer)
        {
            cout << *p;
            if (p->get_status() != "finished")
            {
                all_processes_finished = false;
                        }
        }

        if (all_processes_finished)
        {
            cout << "All processes finished" << endl;
            break;
        }

        cout << "Current time: " << this->current_time << endl;
        if (this->program_counter != NULL)
        {
            cout << "Current process: " << this->program_counter->get_id() << endl;
        }

        this->check_process_status();

        this->program_counter;

        if (this->program_counter == NULL)
        {
            this->program_counter = this->algorithm->select_process(this->stack_pointer);

            if (this->program_counter == NULL)
            {
                cout << "No process selected" << endl;
                this->current_time++;
                sleep(1);
                continue;
            }
        }

        this->program_counter->set_status("running");
        cout << "Running process " << this->program_counter->get_id() << endl;

        bool isProcessFinished = this->program_counter->is_finished(this->current_time);

        if (isProcessFinished)
        {
            cout << "Process " << this->program_counter->get_id() << " finished" << endl;
            this->program_counter = NULL;
        }

        this->current_time++;
        sleep(1);

        cout << "--------------------------------------------" << endl;
    }
}
