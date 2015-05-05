#ifndef Organizer_H
#define Organizer_H

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <deque>
#include <cmath>

#include "Instruction.h"
#include "ReplaceAlg.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::deque;
using std::reverse;
using std::getline;

class Organizer
{
    public:

        ifstream stream;

        ReplaceAlg replacement_alg;
        deque<Instruction> all_instructions;

        int current_time, total_movement, current_track,
            max_wait_time, total_wait_time, next_free_time;

        double avg_turnaround, avg_wait_time;
        bool disk_processing;
        
        Organizer(ReplaceAlg algorithm, deque<Instruction> instructions);

}; 

#endif
