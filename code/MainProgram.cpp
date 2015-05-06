#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <deque>

#include "Organizer.h"
#include "Instruction.h"
#include "ReplaceAlg.h"
#include "FIFOalg.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::deque;


bool PeekEnd(ifstream* stream) {
    return (stream->peek(), stream->eof());
}

void ReadUntilCharacter(ifstream* stream){
    char c;
    while(!PeekEnd(stream))
    {
        c = stream->peek();
        if ((c == ' ') || (c == '\t') || (c == '\n'))
        {
            stream->get(c);
        }
        else
            return;
    }
    if (PeekEnd(stream))
    {
        //Reset to the start of the file
        return;
    }
}

int ExtractNumber(ifstream* stream) {
    string number;
    char c;
    char d_me[256];
    ReadUntilCharacter(stream);
    // Check if commented line
    //ReadUntilInstruction();
    // If we have readed End of the file Expect Number
    if (PeekEnd(stream))
    {
        //Error
    }

    while (!PeekEnd(stream))
    {
        stream->get(c);
        if (c == '#')
        {
            cout << "Extract Number but starting at #" << endl;
            stream->getline(d_me, 256);
            continue;
        }

        if ((c != ' ') && (c != '\t') && (c != '\n'))
        {
            if (!isdigit(c))
            {

                cout << "SHOULD BE DIGIT: " << c << endl;
                cout << "But is: " << c << endl;
                return -2;
            }

            number += c;
        }
        else
            break;
    }
    return atoi(number.c_str());
}

void ReadInstructions(deque<Instruction>* instrs, char* in_file){

    ifstream stream;  
    stream.open(in_file);
    int time = 0;
    int track = 0;
    int counter = 0;
    string line;
    char c;

    while(!PeekEnd(&stream))
    {
        c = stream.peek();
        if (!isdigit(c))
        {
            getline(stream, line);
        }
        else
        {
            time = ExtractNumber(&stream);
            track = ExtractNumber(&stream);
            Instruction temp_inst (time, track, counter);
            instrs->push_back(temp_inst);
            counter += 1;
        }
    }
}


int main(int argc, char **argv)
{
  char *svalue = NULL;
  int c;

  opterr = 0;
  while ((c = getopt (argc, argv, "s:")) != -1)
    switch (c)
      {
      case 's':
        svalue = optarg;
        break;
      case '?':
        if (optopt == 's')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

    // Instructions
    char* input_file = argv[argc - 1];
    deque<Instruction> AllInstructions;
    ReadInstructions(&AllInstructions, input_file);  

    Organizer org(svalue, AllInstructions);
     
    return 0;
    // Printing out to test
}
