#include "INE5412.hpp"
#include <unistd.h>
#include <iomanip>

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

// Destrutor da classe INE5412, limpa memória e faz o prints de resultados
INE5412::~INE5412()
{
    cout << "=-----------------------------------= Processos =-------------------------------------=" << endl;
    cout << "|  ID  | Turnaround Time | Turnaround Time Médio |  Média espera  |  Total deadlines |" << endl;

    // Cria um vetor de dados para armazenar os resultados dos processos agrupados por ID
    vector<Data> data = vector<Data>(this->stack_pointer.size() + 1, {0, 0, 0, 0, 0});
    for (ProcessParams *p : this->stack_pointer)
    {
        data[p->get_id()].turnaround_time += p->get_turnaround_time();
        data[p->get_id()].media_espera += p->get_waiting_time();
        data[p->get_id()].deadlines += p->was_preemptive() ? 1 : 0;
        data[p->get_id()].count++;
    }

    // Imprime os resultados dos processos, tem vários IFs para printar alinhado
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
            cout << "          " << std::fixed << std::setprecision(2) << turnaround_time << "         |";
        }
        else
        {
            cout << "         " << std::fixed << std::setprecision(2) << turnaround_time << "         |";
        }

        if (media_espera < 10)
        {
            cout << "      " << std::fixed << std::setprecision(2) << media_espera << "      |";
        }
        else
        {
            cout << "     " << std::fixed << std::setprecision(2) << media_espera << "      |";
        }

        if (data[p->get_id()].deadlines < 10)
        {
            cout << "         " << data[p->get_id()].deadlines << "        |" << endl;
        }
        else
        {
            cout << "        " << data[p->get_id()].deadlines << "        |" << endl;
        }
    }

    cout << "=-------------------------------------------------------------------------------------=" << endl;
    cout << "Núm. total de trocas de contexto: " << this->context_switches << endl;

    // Deleta os processos
    for (ProcessParams *p : this->stack_pointer)
    {
        delete p;
    }

    // Limpa os vetores
    this->stack_pointer.clear();
    this->processesIds.clear();
}

// Verifica se algum processo perdeu o deadline ou se algum processo está pronto para ser executado
void INE5412::check_processes_status()
{
    for (ProcessParams *p : this->stack_pointer)
    {
        if (p->get_deadline_time() == this->current_time && p->is_finished() == false)
        {
            p->set_finish_time(this->current_time);
            p->set_status("finished");
        }
        else if (p->get_creation_time() == this->current_time && p->is_new())
        {
            p->set_status("ready");
        }
    }
}

// Incrementa o tempo de espera dos processos que estão prontos
void INE5412::check_waiting_time()
{
    for (ProcessParams *p : this->stack_pointer)
    {
        if (p->is_ready())
        {
            p->add_wait_time();
        }
    }
}

// Verifica se todos os processos terminaram
bool INE5412::should_finish()
{
    bool all_processes_finished = true;
    for (ProcessParams *p : this->stack_pointer)
    {
        if (p->is_finished() == false)
        {
            all_processes_finished = false;
            break;
        }
    }

    return all_processes_finished;
}

// Imprime o status dos processos no momento atual
void INE5412::print_processes_status()
{

    if (this->current_time < 10)
    {
        cout << this->current_time - 1 << " - " << this->current_time;
    }
    else if (this->current_time == 10)
    {
        cout << this->current_time - 1 << " -" << this->current_time;
    }
    else
    {
        cout << this->current_time - 1 << "-" << this->current_time;
    }

    cout << "  ";

    for (int id : this->processesIds)
    {
        string status = "new";
        for (ProcessParams *p : this->stack_pointer)
        {
            if (p->get_id() == id && p->is_ready())
            {
                status = "ready";
                break;
            }
        }

        if (this->program_counter != nullptr && id == this->program_counter->get_id())
        {
            cout << "  ##  ";
        }
        else if (status == "new")
        {
            cout << "      ";
        }
        else if (status == "ready")
        {
            cout << "  --  ";
        }
    }

    cout << endl;
}

// Muda o contexto do processo que está sendo executado
void INE5412::change_context(ProcessParams *process)
{
    this->program_counter = process;
    this->context_switches++;
}

void INE5412::start()
{
    while (true)
    {
        INE5412::check_processes_status();

        if (this->should_finish())
        {
            cout << endl
                 << endl;
            break;
        }

        // Se o processo atual terminou, seta o program counter para null
        if (this->program_counter != nullptr && this->program_counter->is_finished())
        {
            this->program_counter = nullptr;
        }

        // Seleciona o processo a ser executado usando o algoritmo
        ProcessParams *selected_process = this->algorithm->select_process(this->stack_pointer);

        // O algoritmo pode retornar null se não houver processos prontos para serem executados
        if (selected_process != nullptr)
        {
            // Se o program counter for null, seta o program counter para o processo selecionado
            if (this->program_counter == nullptr)
            {
                INE5412::change_context(selected_process);
            }
            else
            {
                // Compara o processo atual com o processo selecionado para ver se o processo selecionado tem prioridade
                int result_priority = this->algorithm->compare_and_return_priority_id(this->program_counter, selected_process);

                // Se o processo selecionado tem prioridade, seta o program counter para o processo selecionado
                if (result_priority == selected_process->get_id())
                {
                    // Muda o processo que estava executando para ready
                    this->program_counter->set_status("ready");
                    INE5412::change_context(selected_process);
                }
            }
        }

        // Se o program counter não for null, executa o processo
        if (this->program_counter != nullptr)
        {
            this->program_counter->run(this->current_time);
        }

        this->current_time++;

        INE5412::check_waiting_time();
        INE5412::print_processes_status();
        sleep(1);
    }
}
