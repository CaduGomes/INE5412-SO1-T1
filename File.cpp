#include "File.hpp"

File::File()
{
	myfile.open("entrada.txt");
	if (!myfile.is_open())
	{
		cout << "Erro ao abrir o arquivo!\n";
	}
}

void File::read_file()
{

	int a, b, c;

	if (!myfile.is_open())
	{
		cout << "Arquivo não está aberto!" << endl;
	}

	while (myfile >> a >> b >> c)
	{
		ProcessParams *p = new ProcessParams(a, b, c);
		processes.push_back(p);
	}

	cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
}

void File::print_processes_params()
{
	vector<ProcessParams *>::iterator iter = processes.begin();

	for (iter; iter < processes.end(); iter++)
	{
		ProcessParams *p = *iter;
		cout << *p;
	}
}

File::~File()
{
	for (int i = 0; i < processes.size(); i++)
	{
		ProcessParams *p = processes[i];
		delete p;
	}
}
