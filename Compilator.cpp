#include "cstdlib"
#include "windows.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <cstdio>

#include "Consts.h"
#include "SubStrSearch.h"

void Compile ();

std::string GetCode (char FileName[]);
void PupCode (char file_[], const std::string &code_, unsigned func_sz);

int main()
    {
    Compile ();

    return 0;
    }

void Compile ()
    {
    std::string str_code = GetCode ("Code.txt");

    unsigned n_of_commands = 0;

    int last_stop = 0;
    //int n_of_commands_before = 0;

    /*std::vector<int> find_marks = SubStrSearch (str_code, AllFunctions[Mark_num].name_);
    for (int i = 0; i < find_marks.size (); i++)
        {
        for (int j = last_stop; j < find_marks[i]; j++)
            {
            if (str_code[i] == ';') n_of_commands_before++;
            }

        int mark_begin;
        int

        for (int j = find_marks[i]+5; 1; j++)
            {

            }

        last_stop = find_marks[i];
        }*/

    for (int i = 0; i < Num_of_functions; i++)
        {
        std::vector<int> find_words = SubStrSearch (str_code, AllFunctions[i].name_);
        n_of_commands += find_words.size ();

        for (int k = 0; k < find_words.size (); k++)
        for (int j = 0; j < AllFunctions[i].name_.size () && j < AllFunctions[i].num_name_.size (); j++)
            {
            str_code[find_words[k]+j] = AllFunctions[i].num_name_[j];
            }
        }
      //  std::cout << str_code << "\n";

    for (int i = 0; i < str_code.size (); i++)
        {
        if (str_code[i] == '(') {str_code[i] = '0';}
        if (str_code[i] == '[') {str_code[i] = '1';}

        if (str_code[i] == ')') {str_code[i] = ' ';}
        if (str_code[i] == ']') {str_code[i] = ' ';}
        }
//std::cout << str_code;
    for (int i = 0; i < str_code.size (); i++)
    if (str_code[i] == ';') str_code[i] = '\n';

    PupCode ("ComputerCode.txt", str_code, n_of_commands);


    }

std::string GetCode (char FileName[])
    {
    FILE* codeFile = fopen (FileName, "rb");

    fseek (codeFile, 0, SEEK_END);
    int codeSize = ftell (codeFile);
    rewind (codeFile);

    char* code = (char*) calloc (sizeof (char), codeSize);

    fread (code, 1, codeSize, codeFile);

    fclose (codeFile);

    for (int i = 0; i < codeSize; i++)
        {
        if (code[i] == '\r' || code[i] == '\n' || code[i] == '\0') code[i] = ' ';
        }

    std::string resualt;

    for (int i = 0; i < codeSize; i++)
        {
        if (code[i] == ';' || code[i] == '(' || code[i] == ')' ||
            code[i] == ']' || code[i] == '[')
            {
            for (int j = 0; j < 5; j++) resualt.push_back (' ');
            resualt.push_back (code[i]);
            for (int j = 0; j < 5; j++) resualt.push_back (' ');
            }
        else
        resualt.push_back (code[i]);
        }

    //std::cout << resualt;

    return resualt;
    }

void PupCode (char file_[], const std::string &code_, unsigned func_sz)
    {
    FILE * File = fopen (file_, "w");

    fprintf (File, "%f \n", (float)func_sz);
    fprintf (File, "%s ", code_.c_str());

    fclose (File);
    }