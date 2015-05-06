#include "SCANalg.h"

SCANalg::SCANalg() {
    direction_up = true;
}

Instruction SCANalg::GetInstruction(int current_track_pos) {
    vector<int> track_times;
    int selected_track = -1;
    for (int i = 0; i < ReadyQueue.size(); i++)
    {
        track_times.push_back(ReadyQueue[i].track);
    }

    sort (track_times.begin(), track_times.end());

    // determine the direction
    if (direction_up) 
    {
        for (int i = 0; i < track_times.size(); i++)
        {
            if (track_times[i] >= current_track_pos)
            {
                selected_track = track_times[i];
                break;
            }
        }

        if (selected_track == -1)
        {
            direction_up = false;
            selected_track = track_times.back();
        }
    }

    // Going down
    else
    {
        reverse(track_times.begin(), track_times.end());
        for (int i = 0; i < track_times.size(); i++)
        {
            if (track_times[i] <= current_track_pos)
            {
                selected_track = track_times[i];
                break;
            }
        }
        if (selected_track == -1)
        {
            direction_up = true;
            selected_track = track_times.back();
        }
    }

    for (int i = 0; i < ReadyQueue.size(); i++)
    {
        if (ReadyQueue[i].track == selected_track)
        {
            Instruction return_inst = ReadyQueue[i]; 
            ReadyQueue.erase(ReadyQueue.begin() + i);
            return return_inst;
        }
    } 

    cout << "ERROR, selected Scan Track not found in ready queue" << endl;
    exit (EXIT_FAILURE);

    Instruction return_inst = ReadyQueue.at(0); 
    ReadyQueue.erase(ReadyQueue.begin());

    return return_inst;
}
