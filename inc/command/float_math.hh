#if !defined(FLOAT_MATH_HH)
#define FLOAT_MATH_HH

#include "base_command.hh"

namespace CMD
{
    class fadd : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].floating = p.reg[operation.op.r2].floating + p.reg[operation.op.r3].floating;
        }
    };

    class fsub : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].floating = p.reg[operation.op.r2].floating - p.reg[operation.op.r3].floating;
        }
    };

    class fmul : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].floating = p.reg[operation.op.r2].floating * p.reg[operation.op.r3].floating;
        }
    };

    class fdiv : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            p.reg[operation.op.r1].floating = p.reg[operation.op.r2].floating / p.reg[operation.op.r3].floating;
        }
    };

    class fcomp : public common_command
    {
    public:
        void execute(processor_state& p)
        {
            if (p.reg[operation.op.r1].floating > p.reg[operation.op.r2].floating)
            {
                p.state.FLAGS.cf = 0;
                p.state.FLAGS.zf = 0;
            }else if (p.reg[operation.op.r1].floating < p.reg[operation.op.r2].floating) 
            { 
                p.state.FLAGS.cf = 1;
                p.state.FLAGS.zf = 0; 
            }
            else
            {
                p.state.FLAGS.cf = 0;
                p.state.FLAGS.zf = 1; 
            }
        }
    };
} // namespace CMD

#endif // FLOAT_MATH_HH
