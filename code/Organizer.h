#ifndef Organizer_H
#define Organizer_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <deque>
#include <cmath>

#include "Instruction.h"
#include "ReplaceAlg.h"
#include "FIFOalg.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::deque;
using std::reverse;
using std::getline;
using std::abs;

class Organizer
{
    public:

        ifstream stream;

        //ReplaceAlg * replacement_alg;
        deque<Instruction> all_instructions;

        int current_time, total_movement, current_track,
            max_wait_time, total_wait_time, next_free_time, 
            total_inst, total_turnaround_time;

        Instruction operating_inst;

        double avg_turnaround, avg_wait_time;
        bool disk_processing;
        
        Organizer(char* algorithm, deque<Instruction> instructions);
        void ProcessInstructions(char* algorithm);
        void PrintResults();
        void SetAlgorithm(char* algorithm);
}; 


#endif
