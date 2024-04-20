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
#include "ProcessParams.hpp"

ProcessParams::ProcessParams(int c, int d, int p)
{
    creation_time = c;
    duration = d;
    priority = p;
}
#include "File.hpp"

int main()
{
	File f;
	f.read_file();
	f.print_processes_params();
}
#ifndef FILE_HPP
#define FILE_HPP
#include <iostream>
#include <fstream>
#include <vector>

#include "ProcessParams.hpp"

using namespace std;

class File
{

public:
    void read_file();
    void print_processes_params();
    File();  // This is the constructor declaration
    ~File(); // This is the destructor: declaration

private:
    ifstream myfile;
    vector<ProcessParams *> processes;
};

#endif#ifndef PROCESS_PARAMS_HPP
#define PROCESS_PARAMS_HPP
#include <fstream>

using namespace std;

class ProcessParams
{
public:
    ProcessParams(int c, int d, int p);

    friend ostream &operator<<(ostream &os, const ProcessParams &p)
    {
        os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
        return os;
    }

private:
    int creation_time;
    int duration; // seconds
    int priority;
};

#endif