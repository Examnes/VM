#if !defined(MEMORY_HH)
#define MEMORY_HH
#include <string>
#include "types.hh"

class memory
{
private:
    word arr[65536];
public:
    word &operator[](word idx);
    memory() = default;
};

#endif // MEMORY_HH
