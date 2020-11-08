#if !defined(MEMORY_HH)
#define MEMORY_HH

#include "word.hh"
#include <cstddef>
#include <string>

class memory
{
private:
    word *arr;
    size_t size;
    bool out_of_bounds;

public:
    word &operator[](size_t idx);
    memory &operator=(memory &&other)
    {
        std::swap(arr, other.arr);
        std::swap(size, other.size);
        std::swap(out_of_bounds, other.out_of_bounds);
        return *this;
    }
    memory(std::string filename, size_t offset);
    memory() = default;
    bool is_out_of_bounds()
    {
        return out_of_bounds;
    }
    ~memory();
};

#endif // MEMORY_HH
