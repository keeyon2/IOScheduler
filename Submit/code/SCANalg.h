#ifndef SCANalg_H
#define SCANalg_H

#include "ReplaceAlg.h"

using std::deque;
using std::cout;
using std::endl;

class SCANalg : public ReplaceAlg
{
    public:
        SCANalg();
        Instruction GetInstruction(int current_track_pos);
        bool direction_up;
};

#endif
