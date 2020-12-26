#if !defined(MATH_BASE_HH)
#define MATH_BASE_HH

#include "base_command.hh"

namespace CMD
{
    class arithmetic_command : public common_command
    {
    protected:
        void set_cf(psw &state, result_type res)
        {
            if (res > std::numeric_limits<dword>::max())
            {
                state.FLAGS.cf = true;
            }
            else
            {
                state.FLAGS.cf = false;
            }
        }

        void set_of(const std::array<regtype,8> &reg, psw &state, result_type res)
        {
            bool op1sign = SIGN_BIT(reg[operation.op.r2].integer);
            bool op2sign = SIGN_BIT(reg[operation.op.r3].integer);
            bool ressign = SIGN_BIT(reg[operation.op.r1].integer);
            if ((op1sign and op2sign and not ressign) or
                (not op1sign and not op2sign and ressign))
            {
                state.FLAGS.of = true;
            }
            else
            {
                state.FLAGS.of = false;
            }
        }

        void set_sf(const std::array<regtype,8> &reg, psw &state, result_type res)
        {
            if (SIGN_BIT(reg[operation.op.r1].integer))
            {
                state.FLAGS.sf = true;
            }
            else
            {
                state.FLAGS.sf = false;
            }
        }

        void set_zf(psw &state, result_type res)
        {
            if (res == 0)
            {
                state.FLAGS.zf = true;
            }
            else
            {
                state.FLAGS.zf = false;
            }
        }

        void set_all_flags(processor_state& p, result_type res)
        {
            set_cf(p.state, res);
            set_of(p.reg, p.state, res);
            set_sf(p.reg, p.state, res);
            set_zf(p.state, res);
        }
    };
} // namespace CMD

#endif // MATH_BASE_HH
