#if !defined(COMMAND_HH)
#define COMMAND_HH

#include <stdint.h>
#include <limits>
#include "types.hh"
#include "psw.hh"
#include "memory.hh"
#include <array>

using result_type = uint64_t;
#define SIGN_BIT(x) (x >> (sizeof(x) * 8 - 1))
#define DEF_AS_BASE(x) typedef x base

namespace CMD
{
    class command
    {
    protected:
        union COP
        {
            struct
            {
                word r3 : 3;
                word r2 : 3;
                word r1 : 3;
                word op : 7;
                word address;
            } op;
            word parts[2];
        } operation;

    public:
        void init(word first, word second)
        {
            operation.parts[0] = first;
            operation.parts[1] = second;
        }
        command() = default;
        virtual void execute(psw &state, std::array<regtype, 8> &reg, memory &m) = 0;
        virtual word get_size() = 0;
    };

    class common_command : public command
    {
    public:
        word get_size()
        {
            return 1;
        }
    };

    class extended_command : public command
    {
    public:
        word get_size()
        {
            return 2;
        }
    };
} // namespace CMD

#endif // COMMAND_HH
