#include "File.hpp"
#include "INE5412.hpp"
#include "RM.hpp"
#include "EDF.hpp"

int main()
{
	File file;

	vector<ProcessParams *> processes = file.read_file();

	for (ProcessParams *process : processes)
	{
		for (int i = 1; i < process->get_period_quantity(); i++)
		{
			if (i == 1)
			{

				int new_creation_time = i * process->get_deadline_time();

				int new_deadline_time = new_creation_time + process->get_period_time();

				ProcessParams *new_process = new ProcessParams(*process, new_creation_time, new_deadline_time);

				processes.push_back(new_process);
			}
			else
			{
				int new_creation_time = processes[processes.size() - 1]->get_creation_time() + process->get_period_time();

				int new_deadline_time = new_creation_time + process->get_period_time();

				ProcessParams *new_process = new ProcessParams(*process, new_creation_time, new_deadline_time);

				processes.push_back(new_process);
			}
		}
	}

	RM *rm = new RM();

	INE5412 *cpu = new INE5412(rm, processes);

	cpu->start();

	delete cpu;
	delete rm;

	cout << "Fim da execução do RM" << endl
		 << endl
		 << endl;

	// EDF *edf = new EDF();

	// INE5412 *cpu = new INE5412(edf, processes);

	// cpu->start();

	// delete cpu;
	// delete edf;

	cout << "Fim da execução do EDF" << endl;
	return 0;
}
