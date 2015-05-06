#ifndef FIFOalg_H
#define FIFOalg_H

#include "ReplaceAlg.h"

using std::deque;
using std::cout;
using std::endl;

class FIFOalg : public ReplaceAlg
{
    public:
        Instruction GetInstruction(int current_track_pos);
};

#endif
