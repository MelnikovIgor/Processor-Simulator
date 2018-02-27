struct Function
    {
    int num_;
    std::string name_;
    std::string num_name_;
    };

const int Null_num = 0;
const int Add_num  = 2;
const int Sub_num  = 3;
const int Mul_num  = 4;
const int Div_num  = 5;

const int Dup_num  = 6;
const int Sqrt_num = 7;
const int Sin_num  = 8;
const int Cos_num  = 9;

const int Pop_num  = 1;
const int Push_num = 11;

const int Jump_num = 12;
const int Mark_num = 13;

const int Mark_possition = 12;

Function AllFunctions[13] = {{Null_num       , "Null " , "1 0  " },
                             {Add_num        , "add "  , "1 2 "  },
                             {Sub_num        , "sub "  , "1 3 "  },
                             {Mul_num        , "mul "  , "1 4 "  },
                             {Div_num        , "div "  , "1 5 "  },
                             {Dup_num        , "dup "  , "1 6 "  },
                             {Sqrt_num       , "sqrt " , "1 7  " },
                             {Sin_num        , "sin "  , "1 8 "  },
                             {Cos_num        , "cos "  , "1 9 "  },
                             {Pop_num        , "pop "  , "3 1 "  },
                             {Push_num       , "push " , "3 11 " },
                             {Jump_num       , "jump " , "2 12 " },
                             {Mark_num       , "mark " , "2 13 " }
                            };

const int Buffer_max_size = 20;
const int Num_of_functions = 13;


