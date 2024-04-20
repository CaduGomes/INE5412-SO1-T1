#ifndef PROCESS_PARAMS_HPP
#define PROCESS_PARAMS_HPP
#include <fstream>

using namespace std;

class ProcessParams
{
public:
    friend ostream &operator<<(ostream &os, const ProcessParams &p)
    {
        os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
        return os;
    }

    ProcessParams(int c, int d, int p);

private:
    int creation_time;
    int duration; // seconds
    int priority;
};

#endif