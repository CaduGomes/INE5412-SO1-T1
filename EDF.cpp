#include "EDF.hpp"
#include <limits>
// Seleciona o processo com maior prioridade para ser executado
ProcessParams *EDF::select_process(vector<ProcessParams *> processes)
{
    int index_of_priority_process = -1;
    int earliest_total_time = -1;

    // Inicializa a variável com o maior valor possível
    int earliest_deadline = numeric_limits<int>::max();

    for (size_t i = 0; i < processes.size(); i++)
    {
        ProcessParams *process = processes[i];
        // Se o processo estiver pronto para ser executado
        if (process->is_ready())
        {
            // Se o processo tiver deadline menor que o menor deadline encontrado até o momento
            // ele é armazenado como o processo com menor deadline até o momento
            if (process->get_deadline_time() < earliest_deadline)
            {
                earliest_deadline = process->get_deadline_time();
                index_of_priority_process = i;
                earliest_total_time = process->get_total_time();
            }
            // Se o processo tiver deadline igual ao menor deadline encontrado até o momento
            else if (process->get_deadline_time() == earliest_deadline)
            {
                // Se o processo tiver tempo total maior que o maior tempo total encontrado até o momento
                // ele é armazenado como o processo com maior tempo total até o momento
                if (process->get_total_time() > earliest_total_time)
                {
                    earliest_total_time = process->get_total_time();
                    index_of_priority_process = i;
                    earliest_deadline = process->get_deadline_time();
                }
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

int EDF::compare_and_return_priority_id(ProcessParams *p1, ProcessParams *p2)
{
    // Se o deadline do processo 1 for menor ou igual ao deadline do processo 2 retorna o id do processo 1
    if (p1->get_deadline_time() <= p2->get_deadline_time())
    {
        return p1->get_id();
    }

    return p2->get_id();
}