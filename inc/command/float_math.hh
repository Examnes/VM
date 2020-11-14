#if !defined(FLOAT_MATH_HH)
#define FLOAT_MATH_HH

#include "base_command.hh"

namespace CMD
{
    //все арифметические операции над числами с плавающей точкой аналогичны операциям с обычными числами
    //только используется другое представление регистров floating
    class fadd : public common_command
    {
    public:
        void execute(psw &state, registers &reg, memory &m)
        {
            reg.floating[operation.op.r1] = reg.floating[operation.op.r2] + reg.floating[operation.op.r3];
        }
    };

    class fsub : public common_command
    {
    public:
        void execute(psw &state, registers &reg, memory &m)
        {
            reg.floating[operation.op.r1] = reg.floating[operation.op.r2] - reg.floating[operation.op.r3];
        }
    };

    class fmul : public common_command
    {
    public:
        void execute(psw &state, registers &reg, memory &m)
        {
            reg.floating[operation.op.r1] = reg.floating[operation.op.r2] * reg.floating[operation.op.r3];
        }
    };

    class fdiv : public common_command
    {
    public:
        void execute(psw &state, registers &reg, memory &m)
        {
            reg.floating[operation.op.r1] = reg.floating[operation.op.r2] / reg.floating[operation.op.r3];
        }
    };
} // namespace CMD

#endif // FLOAT_MATH_HH
