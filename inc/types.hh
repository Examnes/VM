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

#endif // TYPES_HH
