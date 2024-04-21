#include "File.hpp"
#include "INE5412.hpp"
#include "RM.hpp"
#include "EDF.hpp"

// TODO: diagrama UML, relatório, registrador

int main()
{
	File file;

	vector<ProcessParams> original_process = file.read_file();

	const size_t initial_size = original_process.size();

	for (size_t i = 0; i < initial_size; i++)
	{
		ProcessParams process = original_process[i];

		if (process.get_period_quantity() > 1)
		{
			int new_creation_time = process.get_deadline_time();

			int new_deadline_time = new_creation_time + process.get_period_time();

			ProcessParams new_process(process, new_creation_time, new_deadline_time);

			original_process.push_back(new_process);

			for (int j = 2; j < process.get_period_quantity(); j++)
			{
				int new_creation_time = original_process[original_process.size() - 1].get_creation_time() + process.get_period_time();

				int new_deadline_time = new_creation_time + process.get_period_time();

				ProcessParams new_process(process, new_creation_time, new_deadline_time);

				original_process.push_back(new_process);
			}
		}
	}

	cout << "Iniciando execução do RM" << endl;

	vector<ProcessParams *> processes_rm;

	for (ProcessParams process : original_process)
	{
		processes_rm.push_back(new ProcessParams(process));
	}

	RM *rm = new RM();

	INE5412 *rm_cpu = new INE5412(rm, processes_rm);

	rm_cpu->start();

	delete rm_cpu;

	delete rm;

	cout << "Fim da execução do RM" << endl
		 << endl
		 << endl;

	EDF *edf = new EDF();

	vector<ProcessParams *> processes_edf;

	for (ProcessParams process : original_process)
	{
		processes_edf.push_back(new ProcessParams(process));
	}

	INE5412 *edf_cpu = new INE5412(edf, processes_edf);

	edf_cpu->start();

	delete edf_cpu;
	delete edf;

	cout << "Fim da execução do EDF" << endl;
	return 0;
}
