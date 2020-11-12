#if !defined(MEMORY_HH)
#define MEMORY_HH

#include "word.hh"
#include <cstddef>
#include <string>

class memory
{
private:
    word arr[65536] = {0};
public:
    word &operator[](size_t idx);
    memory(std::string filename);
    memory(const memory& other);
    memory& operator=(const memory& other);
    memory() = default;
};

#endif // MEMORY_HH
