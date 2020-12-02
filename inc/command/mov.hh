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

    //это мув сразу двух слов, потому что регистры занимают 2 слова
    class movd : public command
    {
    public:
        void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            switch (operation.op.r2)
            {
            case dir::rr:
                reg[operation.op.r1].integer = reg[operation.op.r3].integer;
                break;
            case dir::rm:
                m[operation.op.address] = reg[operation.op.r1].part[0];
                m[operation.op.address + 1] = reg[operation.op.r1].part[1];
                break;
            case dir::mr:
                reg[operation.op.r1].part[0] = m[operation.op.address];
                reg[operation.op.r1].part[1] = m[operation.op.address + 1];
                break;
            case dir::bmr:
                reg[operation.op.r1].part[0] = m[reg[operation.op.r3].signed_integer + operation.op.address];
                reg[operation.op.r1].part[1] = m[reg[operation.op.r3].signed_integer + operation.op.address + 1];
                break;
            case dir::rbm:
                m[reg[operation.op.r3].signed_integer + operation.op.address] = reg[operation.op.r1].part[0];
                m[reg[operation.op.r3].signed_integer + operation.op.address + 1] = reg[operation.op.r1].part[1];
                break;
            case dir::la:
                reg[operation.op.r1].integer = operation.op.address;
                break;
            case dir::lba:
                reg[operation.op.r1].integer = reg[operation.op.r3].signed_integer + operation.op.address;
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
