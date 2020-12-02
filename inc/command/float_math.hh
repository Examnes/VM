#if !defined(FLOAT_MATH_HH)
#define FLOAT_MATH_HH

#include "base_command.hh"

namespace CMD
{
    class fadd : public common_command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            reg[operation.op.r1].floating = reg[operation.op.r2].floating + reg[operation.op.r3].floating;
        }
    };

    class fsub : public common_command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            reg[operation.op.r1].floating = reg[operation.op.r2].floating - reg[operation.op.r3].floating;
        }
    };

    class fmul : public common_command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            reg[operation.op.r1].floating = reg[operation.op.r2].floating * reg[operation.op.r3].floating;
        }
    };

    class fdiv : public common_command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            reg[operation.op.r1].floating = reg[operation.op.r2].floating / reg[operation.op.r3].floating;
        }
    };
} // namespace CMD

#endif // FLOAT_MATH_HH
