#include "cstdlib"
#include "windows.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>

#include "Stack.h"
#include "Consts.h"

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
            {
            std::cout <<"   " << buffer_[i] <<"\n";
            }
    }
};

class CProc
{
private:
    CStack stack_;
    CBuffer buffer_;

    double ax, bx, cx, dx;

    std::vector<double> list_;
    std::vector<size_t> call_list_;
    unsigned cursor = 0;

public:
    CProc ();
    CProc (const CProc& Proc);

    void     Push (int push_type, double new_item);
    void     Pop (int pop_type, int where);
    size_t   StackSize () const {return stack_.MySize ();}
    void     DumpStack () const {stack_.Dump ();}
    void     DumpBuffer  () {buffer_.Dump();}

    bool     add ();
    bool     sub ();
    bool     mul ();
    bool     div ();
    bool     dup();
	bool     mysqrt();
	bool     mysin();
	bool     mycos();

    bool     DoComand (int Num);
	void     Performer ();
    void     OneTurnPerformer ();
    bool     End () {return cursor >= list_.size ();};

    void     ExtractFromFile (const char name[]);

	void     Dump ();
};

int main ()
{
    int const N = 1;
    int timer = 0;
    CProc* main_proc = new CProc [1];

    for (int i = 0; i < N; i++) main_proc[i].ExtractFromFile ("ComputerCode.txt");

    while (1)
    {
        for (int i = 0; i < N; i++)
        {
            main_proc[i].Performer ();

            if (main_proc[i].End () == true) timer++;
        }

        if (timer == N) break;
        else
            timer = 0;
    }

    for (int i = 0; i < N; i++) main_proc[i].Dump ();

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


CProc::CProc () :
    stack_ (),
    buffer_ (),
    ax (0),
    bx (0),
    cx (0),
    dx (0),
    list_ (),
    call_list_ ()
    {}

CProc::CProc (const CProc& Proc) :
    stack_ (Proc.stack_),
    buffer_ (Proc.buffer_),
    ax (0),
    bx (0),
    cx (0),
    dx (0),
    list_ (),
    call_list_ ()
    {}

//{ Functions
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
            stack_.Push (buffer_[static_cast<size_t>(new_item)]);
            break;
        }

        case 2:
        {
            switch (static_cast<int>(new_item))
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
//}

bool CProc::DoComand (int Num)
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
            Pop  (static_cast<int> (list_[cursor+1]), static_cast<int> (list_[cursor+2]));

            cursor += 2;
            break;
        }

        case Push_num:
        {
            Push  (static_cast<int> (list_[cursor+1]), static_cast<int> (list_[cursor+2]));

            cursor += 2;
            break;
        }

        case Jump_num:
        {
           // std::cout << "{"<<cursor << " " << (int)list_[cursor+1]<<" "<< list_[list_[cursor+1]]<< "}\n";
            cursor = static_cast<int> (list_[cursor+1]);

            break;
        }

        case Mark_num:
        {
            cursor++;

            break;
        }

        case If_num:
        {
            bool do_it = static_cast<int> (stack_.Pop ()*2) != 0;

            if (do_it)
            {
                cursor = static_cast<int> (list_[cursor+1]);
            }
            else
            {
                cursor++;
            }

            break;
        }

        case Jump_if_equal:
            {
            double x = stack_.Pop ();
            double y = stack_.Pop ();

            if (fabs (x - y) < 0.000001)
                {
                cursor = static_cast<int> (list_[cursor+1]);
                }
            else
                {
                cursor++;
                }

            break;
            }

        case Jump_if_not_equal:
            {
            double x = stack_.Pop ();
            double y = stack_.Pop ();

            if (fabs (x - y) >= 0.000001)
                {
                cursor = static_cast<int> (list_[cursor+1]);
                }
            else
                {
                cursor++;
                }

            break;
            }

        case Jump_if_pos:
            {
            double x = stack_.Pop ();

            if (x >= 0.000001)
                {
                cursor = static_cast<int> (list_[cursor+1]);
                }
            else
                {
                cursor++;
                }

            break;
            }

        case Call_num:
            {
               // std::cout << list_[cursor+1] << "\n";
            call_list_.push_back(cursor+1);
            cursor = static_cast<int> (list_[cursor+1])+1;

            break;
            }

        case Return_num:
            {
            cursor = call_list_[call_list_.size() - 1];
            call_list_.resize(call_list_.size()-1);

            break;
            }

        default: return true;
    }//Dump ();

    return false;
}

void CProc::Performer ()
{
    int fun = 0;

    while (cursor < list_.size ())
    {
        //std::cout << list_[cursor] << " " << cursor << "\n";
        fun = static_cast<int> (list_[cursor]);
        DoComand (fun);

        cursor++;
    }
}

void CProc::OneTurnPerformer ()
    {
    int fun = 0;

    if (cursor < list_.size ())
        {
        //std::cout << list_[cursor] << " " << cursor << "\n";
        fun = static_cast<int> (list_[cursor]);
        DoComand (fun);

        cursor++;
        }
    }

void CProc::ExtractFromFile (const char name[])
{
    float in_num = 0, line_num = 0, num = 0;

    FILE * code_file;
    code_file = fopen (name,"r");

    fscanf (code_file, "%f ", &in_num);

    for (int i = 0; i < static_cast<int> (in_num); i++)
    {
        fscanf (code_file, "%f ", &line_num);

        for (int j = 0; j < line_num; j++)
        {
            fscanf (code_file, "%f ", &num);

            list_.push_back (static_cast<double> (num));
        }
    }

    fclose (code_file);
}

void CProc::Dump ()
{
    DumpStack ();

    std::cout << "\n   " << ax
              << "  "    << bx
              << "  "    << cx
              << "  "    << dx
              << "\n\n   "    << cursor << "\n";

    for (unsigned i = 0; i < list_.size (); i++)
    {
        if (i%10 == 0) std::cout << "\n    ";

        std::cout << list_[i] << " ";
    }

    std::cout << "\n";

    DumpBuffer ();
}
