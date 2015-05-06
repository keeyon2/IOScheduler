#include "FIFOalg.h"

Instruction FIFOalg::GetInstruction(int current_track_pos) {
    Instruction return_inst = ReadyQueue.at(0); 
    ReadyQueue.pop_front();

    return return_inst;
}
