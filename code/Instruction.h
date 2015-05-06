#ifndef Instruction_H
#define Instruction_H

#include <iostream>

using std::cout;
using std::endl;

class Instruction
{
    public:
        int incoming_time;
        int track;
        int index;
        int start_time;

        Instruction(int time, int track, int index);
        Instruction();
        void PrintData();
};

#endif
