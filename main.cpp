#include "File.hpp"
#include "INE5412.hpp"
#include "RM.hpp"

int main()
{
	File file;

	vector<ProcessParams *> processes = file.read_file();

	for (ProcessParams *process : processes)
	{
		for (int i = 1; i < process->get_period_quantity(); i++)
		{
			int new_creation_time = process->get_creation_time() + i * process->get_period_time();

			int new_deadline_time = new_creation_time + process->get_period_time();

			int new_period_time = new_creation_time + process->get_period_time();

			ProcessParams *new_process = new ProcessParams(new_creation_time, process->get_duration_time(), new_period_time, new_deadline_time, process->get_priority(), 1);

			new_process->set_id(process->get_id());

			processes.push_back(new_process);
		}
	}

	// for (ProcessParams *process : processes)
	// {
	// 	cout << *process;
	// }

	RM *rm = new RM();

	INE5412 *cpu = new INE5412(rm, processes);

	cpu->start();

	delete cpu;
	delete rm;

	return 0;
}
