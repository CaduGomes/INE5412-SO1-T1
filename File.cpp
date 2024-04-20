#include "File.hpp"

File::File()
{
	myfile.open("entrada.txt");
	if (!myfile.is_open())
	{
		cout << "Erro ao abrir o arquivo!\n";
	}
}

vector<ProcessParams *> File::read_file()
{
	int creation_time, duration, period, priority, deadline, period_quantity;

	if (!myfile.is_open())
	{
		cout << "Arquivo não está aberto!" << endl;
	}

	vector<ProcessParams *> processes;
	while (myfile >> creation_time >> duration >> period >> deadline >> priority >> period_quantity)
	{
		ProcessParams *p = new ProcessParams(creation_time, duration, period, deadline, priority, period_quantity);
		p->set_id(processes.size() + 1);
		processes.push_back(p);
	}

	cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;

	return processes;
}