int Prefix_ (const std::string& Str, unsigned i, const std::vector<int>& Prefix);
std::vector<int> AllPrefixes (const std::string& Str);

std::vector<int> SubStrSearch (const std::string& Str, const std::string& SubStr);

std::vector<int> AllPrefixes (const std::string& Str)
    {
    size_t Str_size = Str.size ();

    std::vector<int> res = {0};
    res.resize (Str_size, 0);

    for (int i = 1; i < Str_size; i++)
        {
        res[i] = Prefix_ (Str, i, res);
        }

    return res;
    }

int Prefix_ (const std::string& Str, unsigned i, const std::vector<int>& AllPrefixes)
    {
    int x = AllPrefixes[i-1];

    while (1)
        {
        if (Str [x] == Str[i]) return x+1;
        else
            {
            x = AllPrefixes[x];
            if (x == 0)
                {
                if (Str[i] == Str[0]) return 1;
                else return 0;
                }
            }
        }

    return 0;
    }

std::vector<int> SubStrSearch (const std::string& Str, const std::string& SubStr)
    {
    std::vector<int> prefix (AllPrefixes (SubStr));

    size_t j = 0;
    std::vector<int> resault;

    size_t Str_size = Str.size ();

    for (size_t i = 0; i < Str_size; i++)
        {
        if (j == SubStr.size ())
            {
            resault.push_back(i-j);

            j = prefix[j-1];
            }

        if (Str[i] == SubStr[j]) {j++;}
        else
            {
            if (j >= 1)
                {
                j = prefix[j-1];
                i--;
                }
            }

        }

    if (j == SubStr.size ())
        {
        j = 0;

        resault.push_back (Str.size ()-SubStr.size ()-1);
        }

    return resault;
    }
