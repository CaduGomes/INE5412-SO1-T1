#include "File.hpp"
#include "INE5412.hpp"
#include "RM.hpp"

int main()
{
	File file;

	vector<ProcessParams *> processes = file.read_file();

	vector<ProcessParams *>::iterator iter = processes.begin();

	for (iter; iter < processes.end(); iter++)
	{
		ProcessParams *p = *iter;
		cout << *p;
	}

	RM *rm = new RM();

	INE5412 *cpu = new INE5412(rm, processes);

	cpu->start();

	delete cpu;
	delete rm;

	return 0;
}
