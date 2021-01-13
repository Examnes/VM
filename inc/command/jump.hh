#if !defined(JUMP_HH)
#define JUMP_HH

#include "base_command.hh"
#include <functional>

namespace CMD
{
    class jump : public command
    {
    private:
        enum based : word //используется ли базовый адрес
        {
            yes = 1,
            no = 3
        };
    public:
        virtual void execute(processor_state& p)
        {
            if (~operation.op.r1 & 0b100) // relative
            {
                p.state.IP +=  (int8_t)(operation.parts[0] & 0x1FF) + this->get_size();
            }else if (operation.op.r1 & 0b100) // indirect
            {
                switch (operation.op.r2)
                {
                case based::no:
                    p.state.IP = operation.op.address;
                    break;
                case based::yes:
                    p.state.IP = operation.op.address + p.reg[operation.op.r3].integer;
                    break;
                default:
                    break;
                }
            }else if (operation.op.r1 & 0b101) //direct
            {
                p.state.IP = p.reg[operation.op.r3].integer;
            }
            p.state.FLAGS.ipcf = true;
        }
        word get_size()
        {
            if (operation.op.r1 == 0b100)
            {
                return 2;
            }
            return 1;
        }
    };

    class conditional_jump : public jump
    {
    private:
        std::function<bool(psw)> pred;
    public:
        conditional_jump(std::function<bool(psw)> pred)
        {
            this->pred = pred;
        }
        //в psw есть флаги - этот предикат определяет нужно совершать прыжок или нет на основании этих флагов.
        virtual void execute(processor_state& p)
        {
            if (pred(p.state))
                jump::execute(p);
        }
    };
} // namespace CMD

#endif // JUMP_HH
