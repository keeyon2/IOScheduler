#ifndef SSTFalg_H
#define SSTFalg_H

#include "ReplaceAlg.h"

using std::deque;
using std::cout;
using std::endl;

class SSTFalg : public ReplaceAlg
{
    public:
        Instruction GetInstruction(int current_track_pos);
};

#endif
