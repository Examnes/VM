#if !defined(TYPES_HH)
#define TYPES_HH

#include <cstdint>
using word = uint16_t;
using dword = uint32_t;

union regtype
{
    word part[2];
    float floating;
    dword integer;
    int32_t signed_integer;
};

union operation_type
{
    struct
    {
        word r3 : 3;
        word r2 : 3;
        word r1 : 3;
        word op : 7;
        word address;
    } op;
    word parts[2];
};

struct psw
{
    word IP {};
    struct
    {
        word zf : 1;
        word sf : 1;
        word of : 1;
        word cf : 1;
        word ipcf: 1;
    } FLAGS {};
};

#endif // TYPES_HH
