#if !defined(MEMORY_HH)
#define MEMORY_HH
#include "types.hh"

class memory
{
private:
    word arr[65536];
public:
    word &operator[](word address);
    memory() = default;
    memory(memory&) = delete;
    memory(memory&&) = delete;
};

#endif // MEMORY_HH
