#include "memory.hh"
#include <stdexcept>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>

word &memory::operator[](size_t idx)
{
    if (idx <= 65536)
        return arr[idx];
    return arr[65535];
}

memory::memory(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t i = 0;
    while (std::getline(file, line, ','))
    {
        arr[i++] = atol(line.c_str());
    }
}

memory::memory(const memory& other)
{
    std::copy(other.arr,other.arr + 65536,arr);
}

memory& memory::operator=(const memory& other)
{
    std::copy(other.arr,other.arr + 65536,arr);
    return *this;
}
