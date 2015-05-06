#include "Organizer.h"

Organizer::Organizer(char * algorithm, deque<Instruction> instructions)
{
    all_instructions = instructions;
    all_instructions_stats = instructions;
    
    current_time = 0;
    current_track = 0;
    next_free_time = 0;
    disk_processing = false;
    total_inst = instructions.size();
    total_turnaround_time = 0;

    avg_turnaround = 0.0;
    avg_wait_time = 0.0;

    total_movement = 0;
    max_wait_time = 0;
    total_wait_time = 0;
    cout << "TRACE" << endl;
    // Check if we add anything new
    ProcessInstructions(algorithm); 
    PrintResults();

} 

void Organizer::ProcessInstructions(char* algorithm) {

    string alg_string = string(algorithm);

    FIFOalg fifo_alg;
    SSTFalg sstf_alg;
    SCANalg scan_alg;

    ReplaceAlg * replacement_alg = &fifo_alg;
    
    // FIFO
    if (alg_string == "i")
    {
        replacement_alg = &fifo_alg;
    }
    
    //SSTF
    else if (alg_string == "j")
    {
        replacement_alg = &sstf_alg;
    }

    //SCAN
    else if(alg_string == "s")
    {
        replacement_alg = &scan_alg;
    }

    //CSCAN
    else if(alg_string == "c")
    {
    }

    //FSCAN
    else if(alg_string == "f")
    {
    }

    while(!all_instructions.empty() || disk_processing)
    {
        // Add Instructions to alg ready queue if time is right
        deque<int> addedInsts;
        addedInsts.clear();
        int total_insts = all_instructions.size();
        for (int i = 0; i < total_insts; i++)
        {
            if (all_instructions[i].incoming_time == current_time)
            {
                replacement_alg->AddInstruction(all_instructions[i]);
                printf("%d:  %4d add %d\n",
                        current_time,
                        all_instructions[i].index,
                        all_instructions[i].track);
                addedInsts.push_back(i);

                all_instructions_stats[all_instructions[i].index].incoming_time = current_time;
            }
        }
        
        for (int i = 0; i < addedInsts.size(); i++)
        {
            all_instructions.erase(all_instructions.begin() + (addedInsts[i] - i));
        }
       
        // Empty if ready
        if ((next_free_time == current_time) && disk_processing)
        {
            disk_processing = false;
            int this_inst_wait_time = current_time - operating_inst.incoming_time;
            printf("%d:  %4d finish %d\n",
                    current_time,
                    operating_inst.index,
                    this_inst_wait_time);

            current_track = operating_inst.track;

            total_turnaround_time = total_turnaround_time + 
                (current_time - operating_inst.incoming_time);

            all_instructions_stats[operating_inst.index].finish_time = current_time;
        } 

        bool RQueueAvail = !replacement_alg->ReadyQueue.empty();
        
        // If not running but have ready, start new operation 
        if (!disk_processing && RQueueAvail)
        {
            int sizeZ = replacement_alg->ReadyQueue.size();

            // Grab next inst and delete from all
            Instruction current_instruction = replacement_alg->GetInstruction(current_track);

            printf("%d:  %4d issue %d %d\n",
                    current_time,
                    current_instruction.index,
                    current_instruction.track,
                    current_track); 

            current_instruction.start_time = current_time;
            operating_inst = current_instruction;

            int current_inst_wait_time = current_time - current_instruction.incoming_time;
            if (max_wait_time < current_inst_wait_time)
                max_wait_time = current_inst_wait_time;

            all_instructions_stats[current_instruction.index].start_time = current_time;

            disk_processing = true; 

            int seek_time = abs(current_track - current_instruction.track);
            next_free_time = current_time + seek_time;
            total_movement += seek_time;

            if (seek_time == 0)
                continue;
        }

        // Make sure at end we subtract 1 from this to compute total amount of steps
        current_time += 1;
    }
}

void Organizer::PrintResults() {
    int total_time = current_time - 1;
    double t_turn_time = 0.0;
    double t_wait_time = 0.0;

    cout << "IOREQS INFO" << endl;
    for (int i = 0; i < all_instructions_stats.size(); i++)
    {
        printf("%5d: %5d %5d %5d\n",
            all_instructions_stats[i].index,
            all_instructions_stats[i].incoming_time,
            all_instructions_stats[i].start_time,
            all_instructions_stats[i].finish_time);
        t_turn_time = t_turn_time + 
            double (all_instructions_stats[i].finish_time - all_instructions_stats[i].incoming_time);
        t_wait_time = t_wait_time + 
            double (all_instructions_stats[i].start_time - all_instructions_stats[i].incoming_time);
    }

    avg_turnaround = double (t_turn_time) / double (all_instructions_stats.size());
    avg_wait_time = double (t_wait_time) / double (all_instructions_stats.size());
    printf("SUM: %d %d %.2lf %.2lf %d\n",
 total_time,
 total_movement,
 avg_turnaround,
 avg_wait_time,
 max_wait_time);
}
