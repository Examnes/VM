#if !defined(JUMP_HH)
#define JUMP_HH

#include "base_command.hh"
#include <functional>

namespace CMD
{
    class jmpd : public extended_command
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
            p.state.FLAGS.ipcf = true;
        }
    };

    class jmpr : public common_command
    {
    public:
        virtual void execute(processor_state& p)
        {
            p.state.IP +=  (int8_t)(operation.parts[0] & 0xFF) + this->get_size();
            p.state.FLAGS.ipcf = true;
        }
    };

    class jmpi : public common_command
    {
    public:
        virtual void execute(processor_state& p)
        {
            p.state.IP = p.reg[operation.op.r1].integer;
            p.state.FLAGS.ipcf = true;
        }
    };

    class conditional_jmpi : public jmpi
    {
    private:
        //в psw есть флаги - этот предикат определяет нужно совершать прыжок или нет на основании этих флагов.
        std::function<bool(psw)> pred;
    public:
        conditional_jmpi(std::function<bool(psw)> pred)
        {
            this->pred = pred;
        }
        virtual void execute(processor_state& p)
        {
            if (pred(p.state))
                jmpi::execute(p);
        }
    };

    class conditional_jmpr : public jmpr
    {
    private:
        std::function<bool(psw)> pred;

    public:
        conditional_jmpr(std::function<bool(psw)> pred)
        {
            this->pred = pred;
        }
        virtual void execute(processor_state& p)
        {
            if (pred(p.state))
                jmpr::execute(p);
        }
    };

    class conditional_jmpd : public jmpd
    {
    private:
        std::function<bool(psw)> pred;

    public:
        conditional_jmpd(std::function<bool(psw)> pred)
        {
            this->pred = pred;
        }
        virtual void execute(processor_state& p)
        {
            if (pred(p.state))
                jmpd::execute(p);
        }
    };
} // namespace CMD

#endif // JUMP_HH
