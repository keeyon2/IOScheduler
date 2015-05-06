#include "Instruction.h"

Instruction::Instruction()
{
}

Instruction::Instruction(int time, int track, int index)
{
    incoming_time = time;
    this->track = track;
    this->index = index;
    start_time = -1000;
}

void Instruction::PrintData()
{
    cout << "Inst :" << index << " Time: " << incoming_time << " track: " << track << endl;
} 

