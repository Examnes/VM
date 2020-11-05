#if !defined(MEMORY_HH)
#define MEMORY_HH

#include "interpretator.hh"
#include <cstddef>

class memory
{
private:
    word* arr;
    size_t size;
public:
    word& operator[](size_t idx);
    memory(size_t sz);
    ~memory();
};


#endif // MEMORY_HH
