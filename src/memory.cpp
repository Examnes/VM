#include "memory.hh"
#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

word &memory::operator[](size_t idx)
{
    if (idx < size)
        return arr[idx];
    return arr[size - 1];
}

memory::memory(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<word> temp;
    while (std::getline(file, line, ','))
    {
        temp.push_back( std::stol(line.c_str()) );
    }
    size = temp.size() + 1;
    arr = new word[size];
    std::copy(temp.begin(),temp.end(),arr);
}

memory::memory(memory&& other)
{
    std::swap(size,other.size);
    std::swap(arr,other.arr);
}

memory& memory::operator=(memory&& other)
{
    std::swap(size,other.size);
    std::swap(arr,other.arr);
    return *this;
}

memory::memory(const memory& other)
{
    arr = new word[other.size];
    std::copy(other.arr,other.arr + other.size,arr);
    size = other.size;
}

memory& memory::operator=(const memory& other)
{
    arr = new word[other.size];
    std::copy(other.arr,other.arr + other.size,arr);
    size = other.size;
    return *this;
}

memory::~memory()
{
    delete[] arr;
}
