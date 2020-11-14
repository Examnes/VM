#if !defined(PSW_HH)
#define PSW_HH

#include "types.hh"

struct psw
{
    word IP;
    struct
    {
        word zf : 1;
        word sf : 1;
        word of : 1;
        word cf : 1;
        word stop : 1;
    } FLAGS;
};

#endif // PSW_HH