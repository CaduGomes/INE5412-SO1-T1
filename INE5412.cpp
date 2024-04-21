#include "INE5412.hpp"
#include <unistd.h>

INE5412::INE5412(Algorithm *algorithm, vector<ProcessParams *> processes)
{
    this->algorithm = algorithm;
    this->stack_pointer = processes;

    for (ProcessParams *p : processes)
    {
        this->processesIds.insert(p->get_id());
    }

    cout << "=----------------------------------= Diagrama =------------------------------------=" << endl;
    cout << "tempo    ";

    for (int id : this->processesIds)
    {

        cout << "P" << id << "    ";
    }

    cout << endl;
}

struct Data
{
    int id;
    int turnaround_time;
    int media_espera;
    int deadlines;
    int count;
};

INE5412::~INE5412()
{
    cout << "=-----------------------------------= Processos =-------------------------------------=" << endl;
    cout << "|  ID  | Turnaround Time | Turnaround Time Médio |  Média espera  |  Total deadlines |" << endl;

    vector<Data> data = vector<Data>(this->stack_pointer.size() + 1, {0, 0, 0, 0, 0});

    for (ProcessParams *p : this->stack_pointer)
    {
        data[p->get_id()].turnaround_time = p->get_turnaround_time();
        data[p->get_id()].media_espera += p->get_waiting_time();
        data[p->get_id()].deadlines += p->was_preemptive() ? 1 : 0;
        data[p->get_id()].count++;
    }

    for (ProcessParams *p : this->stack_pointer)
    {
        double media_espera = data[p->get_id()].media_espera / data[p->get_id()].count;
        double turnaround_time = data[p->get_id()].turnaround_time / data[p->get_id()].count;
        cout << "=-------------------------------------------------------------------------------------=" << endl;

        cout << "|  P" << p->get_id();
        if (p->get_id() < 10)
        {
            cout << "  |";
        }
        else
        {
            cout << " |";
        }

        if (p->get_turnaround_time() < 10)
        {
            cout << "        " << p->get_turnaround_time() << "        |";
        }
        else
        {
            cout << "       " << p->get_turnaround_time() << "        |";
        }

        if (turnaround_time < 10)
        {
            cout << "            " << turnaround_time << "          |";
        }
        else
        {
            cout << "           " << turnaround_time << "          |";
        }

        if (media_espera < 10)
        {
            cout << "        " << media_espera << "       |";
        }
        else
        {
            cout << "       " << media_espera << "       |";
        }

        if (data[p->get_id()].deadlines < 10)
        {
            cout << "         " << data[p->get_id()].deadlines << "        |" << endl;
        }
        else
        {
            cout << "        " << data[p->get_id()].deadlines << "        |" << endl;
        }

        // cout << "| P" << p->get_id() << " |         " << p->get_turnaround_time() << "        |            " << turnaround_time << "         |        " << media_espera << "          |      " << data[p->get_id()].deadlines << "     |" << endl;
    }

    cout << "=-------------------------------------------------------------------------------------=" << endl;
    cout << "Núm. total de trocas de contexto: " << this->context_switches << endl;
}

void INE5412::check_processes_status()
{
    for (ProcessParams *p : this->stack_pointer)
    {
        if (p->get_deadline_time() == this->current_time && p->get_status() != "finished")
        {
            // cout << "Process " << p->get_id() << " missed deadline" << endl;
            p->set_finish_time(this->current_time);
            p->set_status("finished");
        }
        else if (p->get_creation_time() == this->current_time && p->get_status() == "new")
        {
            p->set_status("ready");
            // cout << "Process " << p->get_id() << " is ready" << endl;
        }
    }
}

void INE5412::check_waiting_time()
{
    for (ProcessParams *p : this->stack_pointer)
    {
        if (p->get_status() == "ready")
        {
            p->add_wait_time();
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

        this->check_processes_status();

        if (this->should_finish())
        {
            cout << endl
                 << endl;
            break;
        }

        if (this->current_time < 9)
        {
            cout << this->current_time << " - " << this->current_time + 1;
        }
        else if (this->current_time == 9)
        {
            cout << this->current_time << " -" << this->current_time + 1;
        }
        else
        {
            cout << this->current_time << "-" << this->current_time + 1;
        }

        ProcessParams *current_process = this->algorithm->select_process(this->stack_pointer);

        if (current_process == nullptr && (this->program_counter == nullptr || this->program_counter->get_status() == "finished"))
        {
            cout << "No process to run" << endl;
            this->current_time++;
            this->check_waiting_time();
            sleep(1);
            continue;
        }

        if (this->program_counter == nullptr || this->program_counter->get_status() == "finished")
        {
            this->program_counter = current_process;
            this->context_switches++;
        }
        else if (current_process != nullptr)
        {
            int result_priority = this->algorithm->compare_and_return_priority_id(this->program_counter, current_process);

            if (result_priority == current_process->get_id()) // deve alterar o processo em execução
            {
                this->program_counter->set_status("ready");
                // cout << "Context switched" << endl;
                this->context_switches++;
                this->program_counter = current_process;
            }
        }

        this->program_counter->run(this->current_time);

        this->current_time++;

        this->check_waiting_time();
        sleep(0.5);
        cout << "  ";

        for (int id : this->processesIds)
        {
            // cout << " ";
            string status = "new";
            for (ProcessParams *p : this->stack_pointer)
            {
                if (p->get_id() == id)
                {
                    if (p->get_status() == "ready")
                    {
                        status = "ready";
                    }
                    else if (p->get_status() == "running")
                    {
                        status = "running";
                    }
                }
            }

            if (status == "new")
            {
                cout << "      ";
            }
            else if (status == "ready")
            {
                cout << "  --  ";
            }
            else if (status == "running")
            {
                cout << "  ##  ";
            }
        }

        cout << endl;
    }
}
