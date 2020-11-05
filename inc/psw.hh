#if !defined(PSW_HH)
#define PSW_HH
#include "interpretator.hh"

struct psw
{
    word IP;
    word FLAGS;
    dword registers[8];
};

#endif // PSW_HH
