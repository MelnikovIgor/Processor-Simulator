#include "cstdlib"
#include "windows.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <cstdio>

#include "Consts.h"
#include "SubStrSearch.h"

struct CPoint
    {
    int x, y;
    };

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

//std::cout << "FUCK" <<AllFunctions[Mark_possition].name_ << "FUCK";
    std::vector<CPoint> marks;
    std::vector<int> find_words = SubStrSearch (str_code, AllFunctions[Mark_possition].name_);

//std::cout << "FUCK";
    marks.resize (find_words.size ());
    for (int i = 0; i < marks.size (); i++)
        {
        marks[i].x = find_words[i];
        }

    int com_num = 0;
    int mark_i = 0;


    for (int i = 0; i < str_code.size (); i++)
        {
        if (str_code[i] == ';') com_num ++;
        if (marks[mark_i].x == i)
            {
            marks[mark_i].y = com_num;

            mark_i++;
            }
        }

    for (int i = 0; i < marks.size (); i++)
        {
        std::cout << marks[i].x << " " << marks[i].y << "\n";
        }
//std::cout << "FUCK";

    for (int i = 0; i < Num_of_functions; i++)
        {
        find_words = SubStrSearch (str_code, AllFunctions[i].name_);
        n_of_commands += find_words.size ();

        for (int k = 0; k < find_words.size (); k++)
        for (int j = 0; j < AllFunctions[i].name_.size () && j < AllFunctions[i].num_name_.size (); j++)
            {
            str_code[find_words[k]+j] = AllFunctions[i].num_name_[j];
            }
        }

    for (int i = 0; i < str_code.size (); i++)
        {
        if (str_code[i] == '(') {str_code[i] = '0';}
        if (str_code[i] == '[') {str_code[i] = '1';}

        if (str_code[i] == ')') {str_code[i] = ' ';}
        if (str_code[i] == ']') {str_code[i] = ' ';}
        }

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
