#include "memory.hh"

word &memory::operator[](word address)
{
    return arr[address];
} 