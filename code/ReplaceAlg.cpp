#include "ReplaceAlg.h"

ReplaceAlg::ReplaceAlg(){
}

void ReplaceAlg::AddInstruction(Instruction inst){
    ReadyQueue.push_back(inst);
}

Instruction ReplaceAlg::GetInstruction() {
    cout << "Please never print this" << endl;
    return Instruction(0, 0);
}

