#include "File.hpp"
#include "INE5412.hpp"
#include "RM.hpp"
#include "EDF.hpp"

int main()
{
	File file;

	// Le o arquivo de entrada e armazena os processos
	vector<ProcessParams> original_process = file.read_file();

	// ---- Cria novos processos para os processos periodicos ----

	// Armazena o tamanho inicial do vetor de processos
	const size_t initial_size = original_process.size();

	for (size_t i = 0; i < initial_size; i++)
	{
		ProcessParams process = original_process[i];

		if (process.get_period_quantity() > 1)
		{
			// O primeiro processo periodico tem o creation time igual ao deadline time do processo original
			int new_creation_time = process.get_deadline_time();

			int new_deadline_time = new_creation_time + process.get_period_time();

			ProcessParams new_process(process, new_creation_time, new_deadline_time);

			original_process.push_back(new_process);

			for (int j = 2; j < process.get_period_quantity(); j++)
			{
				// O creation time dos demais processos periodicos é igual ao creation time do processo anterior + o period time
				int new_creation_time = original_process[original_process.size() - 1].get_creation_time() + process.get_period_time();

				int new_deadline_time = new_creation_time + process.get_period_time();

				ProcessParams new_process(process, new_creation_time, new_deadline_time);

				original_process.push_back(new_process);
			}
		}
	}

	cout << "Iniciando execução do RM" << endl;

	// Cria um vetor de processos (pointer) para o algoritmo RM
	vector<ProcessParams *> processes_rm;
	for (ProcessParams process : original_process)
	{
		processes_rm.push_back(new ProcessParams(process));
	}
	// Instancia o algoritmo RM
	RM *rm = new RM();
	// Instancia a CPU com o algoritmo RM e os processos
	INE5412 *rm_cpu = new INE5412(rm, processes_rm);
	// Inicia a execução do algoritmo RM na CPU
	rm_cpu->start();

	// Deleta os processos e o CPU
	delete rm_cpu;
	delete rm;

	cout << "Fim da execução do RM" << endl
		 << endl
		 << endl;

	// Cria um vetor de processos (pointer) para o algoritmo EDF
	vector<ProcessParams *> processes_edf;
	for (ProcessParams process : original_process)
	{
		processes_edf.push_back(new ProcessParams(process));
	}
	// Instancia o algoritmo EDF
	EDF *edf = new EDF();
	// Instancia a CPU com o algoritmo EDF e os processos
	INE5412 *edf_cpu = new INE5412(edf, processes_edf);
	// Inicia a execução do algoritmo EDF na CPU
	edf_cpu->start();

	// Deleta os processos e o CPU
	delete edf_cpu;
	delete edf;

	cout << "Fim da execução do EDF" << endl;
	return 0;
}
