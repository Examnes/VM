#include "memory.hh"
#include <stdexcept>

word& memory::operator[](size_t idx)
{
    if (idx > size)
        throw std::range_error("Address out of bounds " + std::to_string(idx));
    return arr[idx];
}

memory::memory(size_t sz)
{
    new word[sz];
}

memory::~memory()
{
    delete [] arr;
}