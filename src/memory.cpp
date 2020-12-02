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