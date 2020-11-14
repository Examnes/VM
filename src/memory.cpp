#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "memory.hh"

word &memory::operator[](word idx)
{
    return arr[idx];
}

memory::memory(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t i = 0;
    while (std::getline(file, line, ','))
    {
        arr[i++] =  std::stol(line.c_str());
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





