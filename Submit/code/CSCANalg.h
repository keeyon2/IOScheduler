#ifndef CSCANalg_H
#define CSCANalg_H

#include "ReplaceAlg.h"

using std::deque;
using std::cout;
using std::endl;

class CSCANalg : public ReplaceAlg
{
    public:
        CSCANalg();
        Instruction GetInstruction(int current_track_pos);
};

#endif
