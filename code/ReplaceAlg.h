#ifndef ReplaceAlg_H
#define ReplaceAlg_H

#include <iostream>
#include <deque>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "Instruction.h"

using std::deque;
using std::vector;
using std::cout;
using std::endl;
using std::sort;
using std::reverse;

class ReplaceAlg
{
    public:
        deque<Instruction> ReadyQueue;
        virtual void AddInstruction(Instruction inst, bool is_running);
        virtual bool RQueueAvail();
        //virtual int GetInstruction(deque<Instruction> All_Instructions) = 0;
        virtual Instruction GetInstruction(int current_track_pos) = 0;
        int FindSimilarInstIndex(deque<Instruction> All_Instructions, Instruction inst);
        ReplaceAlg();
};

#endif
