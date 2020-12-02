#if !defined(MATH_HH)
#define MATH_HH
#include "math_base.hh"

namespace CMD
{
    class add : public arithmetic_command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            //чтобы нормально ставить флаги нужно чтобы в результат поместился результат даже с переполнением.
            result_type res = (result_type)reg[operation.op.r2].integer + reg[operation.op.r3].integer;
            reg[operation.op.r1].integer = res;
            set_all_flags(reg, state, res);
        }
    };

    class sub : public arithmetic_command
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            result_type res = (result_type)reg[operation.op.r2].signed_integer - reg[operation.op.r3].signed_integer;
            reg[operation.op.r1].integer = res;
            set_all_flags(reg, state, res);
        }
    };

    class mul : public arithmetic_command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {

            result_type res = (result_type)reg[operation.op.r2].integer * reg[operation.op.r3].integer;
            reg[operation.op.r1].integer = res;
            set_all_flags(reg, state, res);
        }
    };

    class _div : public arithmetic_command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            result_type res = (result_type)reg[operation.op.r2].integer / reg[operation.op.r3].integer;
            reg[operation.op.r1].integer = res;
            set_all_flags(reg, state, res);
        }
    };
} // namespace CMD

#endif // MATH_HH
