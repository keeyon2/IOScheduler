#include "ReplaceAlg.h"

ReplaceAlg::ReplaceAlg(){
}

void ReplaceAlg::AddInstruction(Instruction inst){
    ReadyQueue.push_back(inst);
}

Instruction ReplaceAlg::GetInstruction() {
    cout << "Please never print this" << endl;
    return Instruction(0, 0, 0);
}

int ReplaceAlg::FindSimilarInstIndex(deque<Instruction> All_Instructions, Instruction inst){
    for (int i = 0; i < All_Instructions.size(); i++)
    {
        if (All_Instructions[i].incoming_time == inst.incoming_time &&
                All_Instructions[i].track == inst.track)
        {
            return i;
        }

    }
    
    cout << "Didnt find return Inst in all Inst" << endl;
    cout << "This inst was Time: " << inst.incoming_time << " track: " << inst.track << endl;
    cout << endl;
    return -1;
}
