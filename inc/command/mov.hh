#if !defined(MOV_HH)
#define MOV_HH

#include "base_command.hh"

namespace CMD
{
    //это направление операции mov
    enum dir : word
    {
        rr = 0, //регистр - регистр
        rm = 1, //регистр - память
        rbm = 3,
        mr = 5, // память - регистр
        bmr = 7,//базовый адрес + адрес = пямять - регистр
        la = 2,//загрузить адрес
        lba = 6//загрузить адрес + базовый адрес
    };

    //это мув сразу двух слов, потому что регистры занимают 2 слова
    class movd : public command
    {
    public:
        void execute(processor_state& p)
        {
            switch (operation.op.r2)
            {
            case dir::rr:
                p.reg[operation.op.r1].integer = p.reg[operation.op.r3].integer;
                break;
            case dir::rm:
                p.m[operation.op.address] = p.reg[operation.op.r1].part[0];
                p.m[operation.op.address + 1] = p.reg[operation.op.r1].part[1];
                break;
            case dir::mr:
                p.reg[operation.op.r1].part[0] = p.m[operation.op.address];
                p.reg[operation.op.r1].part[1] = p.m[operation.op.address + 1];
                break;
            case dir::bmr:
                p.reg[operation.op.r1].part[0] = p.m[p.reg[operation.op.r3].signed_integer + operation.op.address];
                p.reg[operation.op.r1].part[1] = p.m[p.reg[operation.op.r3].signed_integer + operation.op.address + 1];
                break;
            case dir::rbm:
                p.m[p.reg[operation.op.r3].signed_integer + operation.op.address] = p.reg[operation.op.r1].part[0];
                p.m[p.reg[operation.op.r3].signed_integer + operation.op.address + 1] = p.reg[operation.op.r1].part[1];
                break;
            case dir::la:
                p.reg[operation.op.r1].integer = operation.op.address;
                break;
            case dir::lba:
                p.reg[operation.op.r1].integer = p.reg[operation.op.r3].signed_integer + operation.op.address;
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
