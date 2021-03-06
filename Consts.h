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
const int Ax_num = -1;
const int Bx_num = -1;
const int Cx_num = -1;
const int Dx_num = -1;

const int Jump_num = 12;
const int Mark_num = 13;

const int If_num = 14;
const int Jump_if_equal = 15;
const int Jump_if_not_equal = 16;
const int Jump_if_pos = 17;
const int Call_num = 18;
const int Return_num = 19;




const int Num_of_functions = 23;

const int Mark_possition = Num_of_functions-1;
const int Jump_possition = Num_of_functions-2;

Function AllFunctions[Num_of_functions] = {{Null_num       , " Null " , " 1 0  " },
                                           {Add_num        , " add "  , " 1 2 "  },
                                           {Sub_num        , " sub "  , " 1 3 "  },
                                           {Mul_num        , " mul "  , " 1 4 "  },
                                           {Div_num        , " div "  , " 1 5 "  },
                                           {Dup_num        , " dup "  , " 1 6 "  },
                                           {Sqrt_num       , " sqrt " , " 1 7  " },
                                           {Sin_num        , " sin "  , " 1 8 "  },
                                           {Cos_num        , " cos "  , " 1 9 "  },
                                           {Pop_num        , " pop "  , " 3 1 "  },
                                           {Push_num       , " push " , " 3 11 " },
                                           {Ax_num         , " ax  "  , " 2 0 "  },
                                           {Bx_num         , " bx  "  , " 2 1 "  },
                                           {Cx_num         , " cx  "  , " 2 2 "  },
                                           {Dx_num         , " dx  "  , " 2 3 "  },
                                           {If_num         , " if   " , " 2 14 " },
                                           {Jump_if_pos    , " jump_pos ", " 2 17     "},
                                           {Jump_if_equal  , " jump_eq ", " 2 15    "},
                                           {Jump_if_not_equal  , " jump_n_eq ", "   2 16    "},
                                           {Call_num       , " call   ", "  2 18  "},
                                           {Return_num     , " return ", "  2 19  "},
                                           {Jump_num       , " jump " , " 2 12 " },
                                           {Mark_num       , " mark " , " 2 13 " }
                            };

const int Buffer_max_size = 20;


