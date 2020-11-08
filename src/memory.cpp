#include "memory.hh"
#include <stdexcept>
#include <vector>
#include <fstream>

word& memory::operator[](size_t idx)
{
    if (idx <= size)
        return arr[idx];
    return arr[size - 1];
}

memory::memory(std::string filename, size_t offset)
{
    std::vector<word> temp;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file,line,','))
    {
        temp.push_back(std::stoi(line));
    }
    arr = new word[temp.size() + offset];
    size = temp.size() + offset;
    std::copy(temp.begin(),temp.end(),arr + offset);
    out_of_bounds = false;
}

memory::~memory()
{
    delete [] arr;
}