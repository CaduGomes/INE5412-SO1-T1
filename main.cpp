#include "File.hpp"
#include "INE5412.hpp"
#include "RM.hpp"
#include "EDF.hpp"

// TODO: diagrama UML, relatório, registrador

int main()
{
	File file;

	vector<ProcessParams *> original_process = file.read_file();

	vector<ProcessParams *> processes_copy;

	for (ProcessParams *process : original_process)
	{

		for (int i = 1; i < process->get_period_quantity(); i++)
		{

			if (i == 1)
			{

				int new_creation_time = i * process->get_deadline_time();

				int new_deadline_time = new_creation_time + process->get_period_time();

				ProcessParams *new_process = new ProcessParams(*process, new_creation_time, new_deadline_time);

				processes_copy.push_back(new_process);
			}
			else
			{
				int new_creation_time = processes_copy[processes_copy.size() - 1]->get_creation_time() + process->get_period_time();

				int new_deadline_time = new_creation_time + process->get_period_time();

				ProcessParams *new_process = new ProcessParams(*process, new_creation_time, new_deadline_time);

				processes_copy.push_back(new_process);
			}
		}
	}

	for (ProcessParams *process : processes_copy)
	{
		original_process.push_back(process);
	}

	RM *rm = new RM();

	vector<ProcessParams *> process_copy_for_rm;

	for (ProcessParams *obj : original_process)
	{
		process_copy_for_rm.push_back(new ProcessParams(*obj));
	}

	INE5412 *rm_cpu = new INE5412(rm, process_copy_for_rm);

	rm_cpu->start();

	delete rm_cpu;

	delete rm;

	cout << "Fim da execução do RM" << endl
		 << endl
		 << endl;

	EDF *edf = new EDF();

	vector<ProcessParams *> process_copy_for_edf;

	for (ProcessParams *obj : original_process)
	{
		process_copy_for_edf.push_back(new ProcessParams(*obj));
	}

	INE5412 *edf_cpu = new INE5412(edf, process_copy_for_edf);

	edf_cpu->start();

	delete edf_cpu;
	delete edf;

	for (ProcessParams *p : original_process)
	{
		delete p;
	}

	cout << "Fim da execução do EDF" << endl;
	return 0;
}
