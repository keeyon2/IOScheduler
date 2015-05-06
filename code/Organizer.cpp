#include "Organizer.h"

Organizer::Organizer(char * algorithm, deque<Instruction> instructions)
{
    all_instructions = instructions;
    
    //operating_inst(0, 0, 0);
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

    // Check if we add anything new
    SetAlgorithm(algorithm);
    ProcessInstructions(algorithm); 
    PrintResults();

} 

void Organizer::SetAlgorithm(char* algorithm)
{
    /*
    string alg_string = string(algorithm);

    if (alg_string == "i")
    {
        FIFOalg fifo_alg;
        replacement_alg = &fifo_alg;
    }
    else if (alg_string == "j")
    {
    }
    else if(alg_string == "s")
    {
    }
    else if(alg_string == "c")
    {
    }
    else if(alg_string == "f")
    {
    }
    */
}

void Organizer::ProcessInstructions(char* algorithm) {

    string alg_string = string(algorithm);

    FIFOalg fifo_alg;

    ReplaceAlg * replacement_alg = &fifo_alg;
    if (alg_string == "i")
    {
        replacement_alg = &fifo_alg;
    }
    else if (alg_string == "j")
    {
    }
    else if(alg_string == "s")
    {
    }
    else if(alg_string == "c")
    {
    }
    else if(alg_string == "f")
    {
    }

    while(!all_instructions.empty() || disk_processing)
    {
        // Add Instructions to alg ready queue if time is right
        deque<int> addedInsts;
        int total_insts = all_instructions.size();
        for (int i = 0; i < total_insts; i++)
        {
            if (all_instructions[i].incoming_time == current_time)
            {
                replacement_alg->AddInstruction(all_instructions[i]);
                cout << current_time << ":     " << all_instructions[i].index <<
                    " add " << all_instructions[i].track << endl;
                addedInsts.push_back(i);
            }
        }
        
        
        for (int i = 0; i < addedInsts.size(); i++)
        {
            //cout << "Want to Delete from All Insts" << endl;
            all_instructions.erase(all_instructions.begin() + (addedInsts[i] - i));
            //cout << "Deleted from All Insts" << endl;
        }
       
        // DEGUB PRINT   
        /*
        for (int i = 0; i < all_instructions.size(); i++)
        {
            all_instructions[i].PrintData();
        }
        */
        // DEBUG PRINT FINISH

        // Empty if ready
        if ((next_free_time == current_time) && disk_processing)
        {
            disk_processing = false;
            int this_inst_wait_time = current_time - operating_inst.incoming_time;
            cout << current_time << ":     " << operating_inst.index << " finish " 
                << this_inst_wait_time << endl;
            current_track = operating_inst.track;
            total_turnaround_time = total_turnaround_time + 
                (current_time - operating_inst.incoming_time);
        } 

        bool RQueueAvail = !replacement_alg->ReadyQueue.empty();
        //cout << "Ready Queue Avail with size: " << replacement_alg->ReadyQueue.size() << endl; 
        
        // If not running but have ready, start new operation 
        if (!disk_processing && RQueueAvail)
        {
            int sizeZ = replacement_alg->ReadyQueue.size();

            // Grab next inst and delete from all
            /*
            int replace_inst_ind = replacement_alg->GetInstruction(all_instructions);
            Instruction current_instruction = all_instructions[replace_inst_ind];
            all_instructions.erase(all_instructions.begin() + replace_inst_ind);
            */
            Instruction current_instruction = replacement_alg->GetInstruction();

            cout << current_time << ":     " << current_instruction.index <<
                " issue " << current_instruction.track << " " << current_track << endl;

            current_instruction.start_time = current_time;
            operating_inst = current_instruction;

            int current_inst_wait_time = current_time - current_instruction.incoming_time;
            if (max_wait_time < current_inst_wait_time)
                max_wait_time = current_inst_wait_time;

            total_wait_time += current_inst_wait_time;
            disk_processing = true; 

            int seek_time = abs(current_track - current_instruction.track);
            next_free_time = current_time + seek_time;
            total_movement += seek_time;
        }

        // Make sure at end we subtract 1 from this to compute total amount of steps
        current_time += 1;
    }
}

void Organizer::PrintResults() {
    int total_time = current_time - 1;
    avg_turnaround = double (total_turnaround_time) / double (total_inst);
    avg_wait_time = double (total_wait_time) / double (total_inst);
    
    printf("SUM: %d %d %.2lf %.2lf %d\n",
 total_time,
 total_movement,
 avg_turnaround,
 avg_wait_time,
 max_wait_time);
}
