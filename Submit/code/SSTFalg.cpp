#include "SSTFalg.h"

Instruction SSTFalg::GetInstruction(int current_track_pos) {
    int min_seek_time = 32000;
    int min_seek_index = 0;
    int current_seek_time = 0;
    for (int i = 0; i < ReadyQueue.size(); i++)
    {
        current_seek_time = abs(current_track_pos - ReadyQueue[i].track); 
        if (current_seek_time < min_seek_time)
        {
            min_seek_time = current_seek_time;
            min_seek_index = i;
        }
    }
    Instruction return_inst = ReadyQueue.at(min_seek_index); 
    ReadyQueue.erase(ReadyQueue.begin() + min_seek_index);

    return return_inst;
}
