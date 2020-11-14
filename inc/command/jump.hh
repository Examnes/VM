#if !defined(JUMP_HH)
#define JUMP_HH

#include "base_command.hh"
#include <functional>
namespace CMD
{
    class jmpd : public changing_ip_command
    {
    private:
        enum based : word
        {
            yes = 1,
            no = 3
        };

    public:
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            switch (operation.op.r2)
            {
            case based::no:
                state.IP = operation.op.address;
                break;
            case based::yes:
                state.IP = operation.op.address + reg.integer[operation.op.r3];
                break;
            default:
                break;
            }
        }
        DEF_AS_BASE(jmpd);
    };

    class jmpr : public changing_ip_command
    {
    public:
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            state.IP += (int8_t)(operation.parts[0] & 0xFF);
        }
        DEF_AS_BASE(jmpr);
    };

    class jmpi : public changing_ip_command
    {
    public:
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            state.IP = reg.integer[operation.op.r1];
        }
        DEF_AS_BASE(jmpi);
    };

    class conditional_jmpi : public jmpi
    {
    private:
        std::function<bool(psw)> pred;

    public:
        conditional_jmpi(std::function<bool(psw)> pred)
        {
            this->pred = pred;
        }
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            if (pred(state))
                base::execute(state, reg, m);
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
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            if (pred(state))
                base::execute(state, reg, m);
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
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            if (pred(state))
                base::execute(state, reg, m);
        }
    };
} // namespace CMD

#endif // JUMP_HH
