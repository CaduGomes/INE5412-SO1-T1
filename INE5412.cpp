#include "INE5412.hpp"
#include <unistd.h>

INE5412::INE5412(Algorithm *algorithm, vector<ProcessParams *> processes)
{
    this->algorithm = algorithm;
    this->stack_pointer = processes;
}

INE5412::~INE5412()
{
    delete this->algorithm;
    vector<ProcessParams *>::iterator iter = this->stack_pointer.begin();
    for (iter = this->stack_pointer.begin(); iter < this->stack_pointer.end(); iter++)
    {
        delete *iter;
    }

    this->stack_pointer.clear();

    if (this->program_counter != nullptr)
    {
        delete this->program_counter;
    }

    cout << "Context switches: " << this->context_switches << endl;
}

void INE5412::check_processes_status()
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

void INE5412::check_processes_deadline()
{
    vector<ProcessParams *>::iterator iter = this->stack_pointer.begin();

    for (iter = this->stack_pointer.begin(); iter < stack_pointer.end(); iter++)
    {
        ProcessParams *p = *iter;
        if (p->get_deadline_time() == this->current_time && p->get_status() != "finished")
        {
            cout << "Process " << p->get_id() << " missed deadline" << endl;
            p->set_status("finished");
        }
    }
}

bool INE5412::should_finish()
{
    bool all_processes_finished = true;
    for (ProcessParams *p : this->stack_pointer)
    {
        if (p->get_status() != "finished")
        {
            all_processes_finished = false;
            break;
        }
    }

    return all_processes_finished;
}

void INE5412::start()
{
    while (true)
    {

        for (ProcessParams *p : this->stack_pointer)
        {
            cout << *p;
        }

        cout << "Current time: " << this->current_time << endl;

        if (this->should_finish())
        {
            cout << "All processes finished" << endl;
            break;
        }

        this->check_processes_status();
        this->check_processes_deadline();

        ProcessParams *current_process = this->algorithm->select_process(this->stack_pointer);

        if (current_process == nullptr && this->program_counter->get_status() == "finished")
        {
            cout << "No process to run" << endl;
            this->current_time++;
            sleep(1);
            continue;
        }

        if (this->program_counter == nullptr || this->program_counter->get_status() == "finished")
        {
            this->program_counter = current_process;
        }
        else if (current_process != nullptr && this->program_counter->get_priority() < current_process->get_priority())
        {

            this->program_counter->set_status("ready");
            cout << "Context switched" << endl;
            this->context_switches++;
            this->program_counter = current_process;
        }

        this->program_counter->run(this->current_time);

        this->current_time++;
        sleep(1);

        cout << "--------------------------------------------" << endl;
    }
}
