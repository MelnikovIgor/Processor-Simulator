#include "cstdlib"
#include "windows.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>

#include "Stack.h"
#include "Consts.h"

bool DO_DEBAG = false;
#define DEBAG if(DO_DEBAG)

class CBuffer
    {
    private:
    double buffer_[Buffer_max_size] = {};

    public:
    double& operator [] (unsigned i)
        {
        assert (i < Buffer_max_size);
        return buffer_[i];
        }

    void Push (unsigned i, double x);
    double Pop (unsigned i);

    void Dump ()
        {
        std::cout << "\n\n" ;
        for (int i = 0; i < Buffer_max_size; i++)
        {std::cout <<"   " << buffer_[i] <<"\n";  }
        }
    };

class CProc
    {
    private:
    CStack stack_;
    CBuffer buffer_;

    double ax, bx, cx, dx;

    std::vector<double> list_;
    unsigned cursor = 0;

    public:
    CProc () :
        stack_ (),
        ax (0),
        bx (0),
        cx (0),
        dx (0)
        {}

    CProc (const CProc& Proc) :
        stack_ (Proc.stack_),
        ax (0),
        bx (0),
        cx (0),
        dx (0)
        {}

    void     Push (int push_type, double new_item);
    void   Pop (int pop_type, int where);
    size_t StackSize () const {return stack_.MySize ();}
    void     DumpStack () const {stack_.Dump ();}
    void DumpBuffer  () {buffer_.Dump();}

    bool add ();
    bool sub ();
    bool mul ();
    bool div ();

    bool dup();
	bool mysqrt();
	bool mysin();
	bool mycos();

    void* DoComand (int Num, double Parametr = 0);

	void Performer ();
    void ExtractFromFile (char name[]);

	bool Binar (int x);

	void Dump ();
    };

bool CompareWords (char word1[], int Sz1, char word2[], int SZ2);

int main ()
    {
    CProc main_proc;

    main_proc.ExtractFromFile ("ComputerCode.txt");
    main_proc.Performer (); //std::cout << "fuck ";

    main_proc.Dump ();

    system ("pause");

    return 0;
    }


void CBuffer::Push (unsigned i, double x)
    {
    assert (i < Buffer_max_size);
    buffer_[i] = x;
    }

double CBuffer::Pop (unsigned i)
    {
    assert (i < Buffer_max_size);
    return buffer_[i];
    }


void CProc::Push (int push_type, double new_item)
    {
    switch (push_type)
        {
        case 0:
            {
            stack_.Push (new_item);
            break;
            }

        case 1:
            {
            stack_.Push (buffer_[(unsigned)new_item]);
            break;
            }

        case 2:
            {
            switch ((int)new_item)
                {
                case 0: stack_.Push (ax); break;
                case 1: stack_.Push (bx); break;
                case 2: stack_.Push (cx); break;
                case 3: stack_.Push (dx); break;

                default: break;
                }

            break;
            }

        default: break;
        }
    }

void CProc::Pop (int pop_type, int where)
    {
    switch (pop_type)
        {
        case 0:
            {
            stack_.Pop ();

            break;
            }

        case 1:
            {
            buffer_[where] = stack_.Pop ();

            break;
            }

        case 2:
            {
            switch (where)
                {
                case 0: ax = stack_.Pop (); break;
                case 1: bx = stack_.Pop (); break;
                case 2: cx = stack_.Pop (); break;
                case 3: dx = stack_.Pop (); break;

                default: break;
                }

            break;
            }

        default: break;
        }
    }

bool CProc::add ()
    {
    if (StackSize() < 2) return false;

    double x = stack_.Pop ();
    double y = stack_.Pop ();

    stack_.Push (x+y);

    return true;
    }

bool CProc::sub ()
    {
    if (StackSize() < 2) return false;

    double x = stack_.Pop ();
    double y = stack_.Pop ();

    stack_.Push (x-y);

    return true;
    }

bool CProc::mul ()
    {
    if (StackSize() < 2) return false;

    double x = stack_.Pop ();
    double y = stack_.Pop ();

    stack_.Push (x*y);

    return true;
    }

bool CProc::div ()
    {
    if (StackSize() < 2) return false;

    double x = stack_.Pop ();
    double y = stack_.Pop ();

    if (!y) return false;
    else     stack_.Push (x/y);

    return true;
    }

bool CProc::dup ()
    {
    if (StackSize() < 1) return false;

    double x = stack_.Pop ();

    stack_.Push (x);
    stack_.Push (x);

    return true;
    }

bool CProc::mysqrt ()
    {
    if (StackSize() < 1) return false;

    double x = stack_.Pop ();

    stack_.Push (sqrt(x));

    return true;
    }

bool CProc::mysin ()
    {
    if (StackSize() < 1) return false;

    double x = stack_.Pop ();

    stack_.Push (sin(x));

    return true;
    }

bool CProc::mycos ()
    {
    if (StackSize() < 1) return false;

    double x = stack_.Pop ();

    stack_.Push (cos (x));

    return true;
    }


void* CProc::DoComand (int Num, double Parametr)
    {
    switch (Num)
        {
        case Null_num: return 0;
        case Add_num:  add  (); break;
        case Sub_num:  sub  (); break;
        case Mul_num:  mul  (); break;
        case Div_num:  div  (); break;

        case Dup_num:  dup  (); break;
        case Sqrt_num: mysqrt (); break;
        case Sin_num:  mysin  (); break;
        case Cos_num:  mycos  (); break;

        case Pop_num:
            {
            DEBAG std::cout << "Pop " << cursor << " ";
            Pop  (list_[cursor+1], list_[cursor+2]);

            cursor += 2;
            DEBAG std::cout << cursor << "\n";
            break;
            }

        case Push_num:
            {
                DEBAG std::cout << "Push " << cursor << " ";
            Push  (list_[cursor+1], list_[cursor+2]);

            cursor += 2; DEBAG std::cout << cursor << "\n";

            break;
            }

        case Jump_num:
            {
            cursor = list_[cursor+1];

            break;
            }

        case Mark_num:
            {
            cursor++;
<<<<<<< HEAD
=======

>>>>>>> 7c38118a02af56f2347fc6ba9ec7d4b0583c9ba4
            break;
            }

        default: return false;
        }

    return false;
    }

void CProc::Performer ()
    {
    double fun = 0;

    while (cursor < list_.size ())
        {
        fun = list_[cursor];
        std::cout << fun << " ";
        DoComand (fun);

        cursor++;
        }

    std::cout << "\n";
    }

void CProc::ExtractFromFile (char name[])
    {
    float in_num = 0, line_num = 0, num = 0;

    FILE * code_file;
    code_file = fopen (name,"r");

    fscanf (code_file, "%f ", &in_num);

    for (int i = 0; i < (int)in_num; i++)
        {
        fscanf (code_file, "%f ", &line_num);

        for (int j = 0; j < line_num; j++)
            {
            fscanf (code_file, "%f ", &num);

            list_.push_back ((double)num);
            }
        }

    fclose (code_file);
    }

void CProc::Dump ()
    {
<<<<<<< HEAD
    for (int i = 0; i < list_.size (); i++) std::cout << list_[i] << " ";
    std::cout << "\n";
    DumpStack ();
    DumpBuffer ();

    }

=======
    DumpStack ();

    std::cout << "\n   " << ax
              << "  "    << bx
              << "  "    << cx
              << "  "    << dx << "\n";

    DumpBuffer ();
    }
>>>>>>> 7c38118a02af56f2347fc6ba9ec7d4b0583c9ba4
