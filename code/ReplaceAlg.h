#ifndef ReplaceAlg_H
#define ReplaceAlg_H

#include <iostream>
#include <deque>
#include "Instruction.h"

using std::deque;
using std::cout;
using std::endl;

class ReplaceAlg
{
    public:
        deque<Instruction> ReadyQueue;
        void AddInstruction(Instruction inst);
        //virtual int GetInstruction(deque<Instruction> All_Instructions) = 0;
        virtual Instruction GetInstruction() = 0;
        int FindSimilarInstIndex(deque<Instruction> All_Instructions, Instruction inst);
        ReplaceAlg();
};

#endif
