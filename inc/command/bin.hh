#if !defined(BIN_MATH_HH)
#define BIN_MATH_HH

#include "base_command.hh"

namespace CMD
{
    class bor : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].integer = p.reg[operation.op.r2].integer | p.reg[operation.op.r3].integer;
        }
    };

    class bxor : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].integer = p.reg[operation.op.r2].integer ^ p.reg[operation.op.r3].integer;
        }
    };

    class band : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].integer = p.reg[operation.op.r2].integer & p.reg[operation.op.r3].integer;
        }
    };

    class bnot : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].integer = ~p.reg[operation.op.r2].integer;
        }
    };
} // namespace CMD

#endif // BIN_MATH_HH
