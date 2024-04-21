#include "RM.hpp"

// Seleciona o processo com maior prioridade para ser executado
ProcessParams *RM::select_process(vector<ProcessParams *> processes)
{
    int index_of_priority_process = -1;
    int highest_priority = 0;

    for (size_t i = 0; i < processes.size(); i++)
    {
        ProcessParams *process = processes[i];

        // Se o processo estiver pronto para ser executado
        if (process->is_ready())
        {
            // Se o processo tiver prioridade maior que a maior prioridade encontrada até o momento
            // ele é armazenado como o processo com maior prioridade até o momento
            if (process->get_priority() > highest_priority)
            {
                highest_priority = process->get_priority();
                index_of_priority_process = i;
            }
        }
    }

    // Se não houver processos prontos para serem executados, retorna null
    if (index_of_priority_process == -1)
    {
        return nullptr;
    }
    // Retorna o processo com maior prioridade
    return processes[index_of_priority_process];
}

// Compara dois processos e retorna o id do processo com maior prioridade
int RM::compare_and_return_priority_id(ProcessParams *p1, ProcessParams *p2)
{
    // Se a prioridade do processo 1 for maior ou igual a prioridade do processo 2 retorna o id do processo 1
    if (p1->get_priority() >= p2->get_priority())
    {
        return p1->get_id();
    }

    return p2->get_id();
}