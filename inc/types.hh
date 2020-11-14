#if !defined(TYPES_HH)
#define TYPES_HH

#include <cstdint>
using word = uint16_t;
using dword = uint32_t;

union registers
{
    dword integer[8] = {0};
    int32_t signed_integer[8];
    float floating[8];
};

#endif // TYPES_HH
