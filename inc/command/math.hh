#if !defined(MATH_HH)
#define MATH_HH
#include "math_base.hh"

namespace CMD
{
    class add : public arithmetic_command
    {
    public:
        void execute(processor_state& p)
        {
            //чтобы нормально ставить флаги нужно чтобы в результат поместился результат даже с переполнением.
            result_type res = (result_type)p.reg[operation.op.r2].integer + p.reg[operation.op.r3].integer;
            p.reg[operation.op.r1].integer = res;
            set_all_flags(p,res);
        }
    };

    class sub : public arithmetic_command
    {
    public:
        virtual void execute(processor_state& p)
        {
            result_type res = (result_type)p.reg[operation.op.r2].signed_integer - p.reg[operation.op.r3].signed_integer;
            p.reg[operation.op.r1].integer = res;
            set_all_flags(p,res);
        }
    };

    class mul : public arithmetic_command
    {
    public:
        void execute(processor_state& p)
        {

            result_type res = (result_type)p.reg[operation.op.r2].integer * p.reg[operation.op.r3].integer;
            p.reg[operation.op.r1].integer = res;
            set_all_flags(p, res);
        }
    };

    class _div : public arithmetic_command
    {
    public:
        void execute(processor_state& p)
        {
            result_type res = (result_type)p.reg[operation.op.r2].integer / p.reg[operation.op.r3].integer;
            p.reg[operation.op.r1].integer = res;
            set_all_flags(p, res);
        }
    };
} // namespace CMD

#endif // MATH_HH
