#if !defined(MOV_HH)
#define MOV_HH

#include "base_command.hh"

namespace CMD
{
    //это аналог rm
    enum dir : word
    {
        rr = 0,
        rm = 1,
        rbm = 3,
        mr = 5,
        bmr = 7,
        la = 2,
        lba = 6
    };

    union splited
    {
        dword res;
        word part[2];
    };

    //это мув сразу двух слов, потому что регистры занимают 2 слова
    class movd : public command
    {
    public:
        void execute(psw &state, registers &reg, memory &m)
        {
            splited r;
            switch (operation.op.r2)
            {
            case dir::rr:
                reg.integer[operation.op.r1] = reg.integer[operation.op.r3];
                break;
            case dir::rm:
                r.res = reg.integer[operation.op.r1];
                m[operation.op.address] = r.part[0];
                m[operation.op.address + 1] = r.part[1];
                break;
            case dir::mr:
                r.part[0] = m[operation.op.address];
                r.part[1] = m[operation.op.address + 1];
                reg.integer[operation.op.r1] = r.res;
                break;
            case dir::bmr:
                r.part[0] = m[reg.integer[operation.op.r3] + operation.op.address];
                r.part[1] = m[reg.integer[operation.op.r3] + operation.op.address + 1];
                reg.integer[operation.op.r1] = r.res;
                break;
            case dir::rbm:
                r.res = reg.integer[operation.op.r1];
                m[reg.integer[operation.op.r3] + operation.op.address] = r.part[0];
                m[reg.integer[operation.op.r3] + operation.op.address + 1] = r.part[1];
                break;
            case dir::la:
                reg.integer[operation.op.r1] = operation.op.address;
                break;
            case dir::lba:
                reg.integer[operation.op.r1] = reg.integer[operation.op.r3] + operation.op.address;
                break;
            default:
                break;
            }
        }

        word get_size()
        {
            if (operation.op.r2 == dir::rr)
                return 1;
            return 2;
        }
    };
} // namespace CMD

#endif // MOV_HH
