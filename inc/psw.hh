#if !defined(PSW_HH)
#define PSW_HH

#include "word.hh"

struct psw
{
    word IP;
    word FLAGS;
    enum flag_bits
    {
        zf = 1,
        sf = 1 << 1,
        of = 1 << 2,
        cf = 1 << 3
    };
    union
    {
        dword integer[8] = {0,0,0,0,0,0,0,0};
        struct
        {
            word low;
            word up;
        } splited[8];
        int32_t signed_integer[8];
        float floating[8];
    } reg;
    bool stop = false;
};

#endif // PSW_HH
