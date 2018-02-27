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
void FindMark (std::string& str_code);

int main()
    {
    Compile ();

    return 0;
    }

void Compile ()
    {
    std::string str_code = GetCode ("Code.txt");

    unsigned n_of_commands = 0;

<<<<<<< HEAD
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
=======
    for (int i = 0; i < str_code.size (); i++)
        {
        if (str_code[i] == '(') {str_code[i] = '0';}
        if (str_code[i] == '[') {str_code[i] = '1';}

        if (str_code[i] == ')') {str_code[i] = ' ';}
        if (str_code[i] == ']') {str_code[i] = ' ';}
        }

    for (int i = 0; i < Num_of_functions; i++)
        {
        if (i == Jump_possition) FindMark (str_code);
        std::vector<int> find_words = SubStrSearch (str_code, AllFunctions[i].name_);
>>>>>>> 7c38118a02af56f2347fc6ba9ec7d4b0583c9ba4
        n_of_commands += find_words.size ();

        for (int k = 0; k < find_words.size (); k++)
        for (int j = 0; j < AllFunctions[i].name_.size () && j < AllFunctions[i].num_name_.size (); j++)
            {
            str_code[find_words[k]+j] = AllFunctions[i].num_name_[j];
            }
        }

    for (int i = 0; i < str_code.size (); i++)
<<<<<<< HEAD
        {
        if (str_code[i] == '(') {str_code[i] = '0';}
        if (str_code[i] == '[') {str_code[i] = '1';}

        if (str_code[i] == ')') {str_code[i] = ' ';}
        if (str_code[i] == ']') {str_code[i] = ' ';}
        }

    for (int i = 0; i < str_code.size (); i++)
=======
>>>>>>> 7c38118a02af56f2347fc6ba9ec7d4b0583c9ba4
    if (str_code[i] == ';') str_code[i] = '\n';

    PupCode ("ComputerCode.txt", str_code, n_of_commands);
    }

void FindMark (std::string& str_code)
    {
    int last_stop = 0;
    int n_of_commands_before = 0;
    int n_of_param_before = 0;
    std::string lable_name;
    std::string lable_num_in_code;
    bool space = true;

    std::vector<int> find_label = SubStrSearch (str_code, AllFunctions[Mark_possition].name_);

    for (int i = 0; i < find_label.size (); i++)
        {
        for (int j = 0; j < find_label[i]; j++)
            {
            if (space && str_code[j] != ' ')
                {
                n_of_param_before++;
                space = false;
                }
            else
                {
                if (str_code[j] == ' ') space = true;
                }
            }

        for (int j = 0; j < find_label[i]; j++)
            if (str_code[j] == ';') n_of_commands_before++;

        char str[15] = "";
        sprintf(str, "   %d   ", n_of_param_before-2*n_of_commands_before+1);

        lable_num_in_code.insert (lable_num_in_code.size (), str);

        int label_begin = 0;

        for (int j = find_label[i]+5; 1; j++)
            if (str_code[j] != ' ')
                {
                label_begin = j;
                break;
                }

        for (int j = label_begin; str_code[j] != ' '; j++)
            lable_name.push_back (str_code[j]);

        lable_name.push_back (' ');

        std::vector<int> find_label_usings = SubStrSearch (str_code, lable_name);

        for (int j = 0; j < find_label_usings.size (); j++)
            {
            str_code.erase (find_label_usings[j], lable_name.size ());
            str_code.insert (find_label_usings[j], lable_num_in_code);

            for (int k = j+1; k < find_label_usings.size (); k++) find_label_usings[k] = find_label_usings[k] - lable_name.size ()+lable_num_in_code.size ();
            }

        last_stop = find_label[i];

        lable_num_in_code.clear ();
        n_of_commands_before = 0;
        n_of_param_before = 0;
        }
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

    return resualt;
    }

void PupCode (char file_[], const std::string &code_, unsigned func_sz)
    {
    FILE * File = fopen (file_, "w");

    fprintf (File, "%f \n", (float)func_sz);
    fprintf (File, "%s ", code_.c_str());

    fclose (File);
    }
