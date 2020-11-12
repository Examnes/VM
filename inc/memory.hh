#if !defined(MEMORY_HH)
#define MEMORY_HH

#include "word.hh"
#include <cstddef>
#include <string>

class memory
{
private:
    word* arr;
    size_t size;
public:
    word &operator[](size_t idx);
    memory(std::string filename);
    memory(memory&& other);
    memory(const memory&  other);
    memory& operator=(memory&& other);
    memory& operator=(const memory& other);
    memory() = default;
    ~memory();
};

#endif // MEMORY_HH
