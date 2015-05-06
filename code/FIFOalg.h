#ifndef FIFOalg_H
#define FIFOalg_H

#include "ReplaceAlg.h"

using std::deque;
using std::cout;
using std::endl;

class FIFOalg : public ReplaceAlg
{
    public:
        Instruction GetInstruction();
};

#endif
