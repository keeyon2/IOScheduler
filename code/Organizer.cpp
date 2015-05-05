#include "Organizer.h"

Orgainzer::Organizer(ReplaceAlg algorithm, deque<Instruction> instructions)
{
    replacement_alg = algorithm;
    all_instructions = instructions;
    
    current_time = 0;
    total_movement = 0;
    current_track = 0;
    max_wait_time = 0;
    total_wait_time = 0;
    next_free_time = 0;
    avg_turnaround = 0.0;
    avg_wait_time = 0.0;
    disk_processing = false;

    // Check if we add anything new
    ProcessInstructions(); 

} 

void Organizer::ProcessInstructions() {
    while(!all_instructions.empty() || disk_processing)
    {
        // Add Instructions to alg ready queue if time is right
        int total_insts = all_instructions.size();
        for (int i = 0; i < total_insts; i++;)
        {
            if (all_instructions.at(i).incoming_time == current_time)
            {
                replacement_alg.AddInstruction(all_instructions.at(i));
                all_instructions.erase(all_instructions.begin() + i);
            }

        }

        // Empty if ready
        if (next_free_time == current_time && disk_processing)
        {
            disk_processing = false;
        } 

        // If not running but have ready, start new operation 
        if (!disk_processing && !replacement_alg.ReadyQueue.empty())
        {
            Instruction current_instruction = replacement_alg.GetInstruction();
            disk_processing = true; 
            int seek_time = abs(current_track - current_instruction.track);
            next_free_time = 1 + current_time + seek_time;
            total_movement += seek_time;
        }

        

    }
}
