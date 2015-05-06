#ifndef FSCANalg_H
#define FSCANalg_H

#include "ReplaceAlg.h"

using std::deque;
using std::cout;
using std::endl;

class FSCANalg : public ReplaceAlg
{
    public:
        FSCANalg();
        deque<Instruction> SecondaryQueue;
        Instruction GetInstruction(int current_track_pos);
        bool RQueueAvail();
        void AddInstruction(Instruction inst, bool is_running);
        bool direction_up;
};

#endif
