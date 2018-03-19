#include "cstdlib"
#include "windows.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <cstdio>

#include "Consts.h"
#include "SubStrSearch.h"

void Compile ();

std::string GetCode  (char FileName[]);
void        PupCode  (char file_[], const std::string &code_, unsigned func_sz);
void        FindMark (std::string& str_code);

int main()
{
    Compile ();

    return 0;
}

void Compile ()
{
    std::string str_code = GetCode ("Code.txt");

    unsigned n_of_commands = 0;

    for (size_t i = 0; i < str_code.size (); i++)
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

        n_of_commands += find_words.size ();

        for (size_t k = 0; k < find_words.size (); k++)
        for (size_t j = 0; j < AllFunctions[i].name_.size () && j < AllFunctions[i].num_name_.size (); j++)
        {
            str_code[find_words[k]+j] = AllFunctions[i].num_name_[j];
        }
    }

    n_of_commands = 0;

    for (size_t i = 0; i < str_code.size (); i++)
    {
        if (str_code[i] == ';')
            {
            n_of_commands++;
            str_code[i] = '\n';
            }
    }

    PupCode ("ComputerCode.txt", str_code, n_of_commands);
}

void FindMark (std::string& str_code)
{
      /*int n_of_commands_before = 0;
        int n_of_param_before = 0;
        std::string lable_name;
        std::string lable_num_in_code;
        bool space = true;     */

    std::vector<int> find_label = SubStrSearch (str_code, AllFunctions[Mark_possition].name_);

    for (size_t i = 0; i < find_label.size (); i++)
    {
        int n_of_commands_before = 0;
        int n_of_param_before = 0;
        std::string lable_name;
        std::string lable_num_in_code;
        bool space = true;

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
        sprintf(str, "   %d   ", n_of_param_before-2*n_of_commands_before+1+i);

        lable_num_in_code.insert (lable_num_in_code.size (), str);

        int label_begin = 0;

        for (int j = find_label[i]+5; 1; j++)
            if (str_code[j] != ' ')
            {
                label_begin = j;
                break;
            }

        lable_name.push_back (' ');

        for (int j = label_begin; str_code[j] != ' '; j++)
            lable_name.push_back (str_code[j]);

        lable_name.push_back (' ');

        std::vector<int> find_label_usings = SubStrSearch (str_code, lable_name);

        for (size_t j = 0; j < find_label_usings.size (); j++)
        {
            str_code.erase (find_label_usings[j], lable_name.size ());
            str_code.insert (find_label_usings[j], lable_num_in_code);


            for (size_t k = j+1; k < find_label_usings.size (); k++)
                find_label_usings[k] = find_label_usings[k] - lable_name.size ()+lable_num_in_code.size ();
        }

        /*
        n_of_commands_before = 0;
        n_of_param_before = 0;
        lable_name.clear ();
        lable_num_in_code.clear ();
        find_label_usings.clear ();
        space = true;   */

        find_label = SubStrSearch (str_code, AllFunctions[Mark_possition].name_);
    }
}

std::string GetCode (char FileName[])
{
    FILE* codeFile = fopen (FileName, "rb");

    fseek (codeFile, 0, SEEK_END);
    int codeSize = ftell (codeFile);
    rewind (codeFile);

    char* code = static_cast<char*> (calloc (sizeof (char), codeSize));

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
            code[i] == ']' || code[i] == '[' || code[i] == ' ')
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

    fprintf (File, "%f \n", static_cast<float> (func_sz));
    fprintf (File, "%s ", code_.c_str());

    fclose (File);
}
