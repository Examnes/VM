#if !defined(MEMORY_HH)
#define MEMORY_HH
#include "types.hh"
#include <iostream>

class memory
{
private:
    word arr[65536];
public:
    word &operator[](word address);
    memory() = default;
    memory(const memory& o) = delete;
    memory(memory&& o) = delete;
};

#endif // MEMORY_HH
