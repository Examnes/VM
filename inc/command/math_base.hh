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

        void set_of(const registers &reg, psw &state, result_type res)
        {
            bool op1sign = SIGN_BIT(reg.integer[operation.op.r2]);
            bool op2sign = SIGN_BIT(reg.integer[operation.op.r3]);
            bool ressign = SIGN_BIT(reg.integer[operation.op.r1]);
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

        void set_sf(const registers &reg, psw &state, result_type res)
        {
            if (SIGN_BIT(reg.integer[operation.op.r1]))
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

        void set_all_flags(const registers &reg, psw &state, result_type res)
        {
            set_cf(state, res);
            set_of(reg, state, res);
            set_sf(reg, state, res);
            set_zf(state, res);
        }
    };
} // namespace CMD

#endif // MATH_BASE_HH
