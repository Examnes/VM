#if !defined(JUMP_HH)
#define JUMP_HH

#include "base_command.hh"
#include <functional>
namespace CMD
{
    class jmpd : public extended_command
    {
    private:
        enum based : word
        {
            yes = 1,
            no = 3
        };

    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            switch (operation.op.r2)
            {
            case based::no:
                state.IP = operation.op.address;
                break;
            case based::yes:
                state.IP = operation.op.address + reg[operation.op.r3].integer;
                break;
            default:
                break;
            }
            state.FLAGS.ipcf = true;
        }
        DEF_AS_BASE(jmpd);
    };

    class jmpr : public common_command
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            state.IP +=  (int8_t)(operation.parts[0] & 0xFF) + this->get_size();
            state.FLAGS.ipcf = true;
        }
        DEF_AS_BASE(jmpr);
    };

    class jmpi : public common_command
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            state.IP = reg[operation.op.r1].integer;
            state.FLAGS.ipcf = true;
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
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
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
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
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
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            if (pred(state))
                base::execute(state, reg, m);
        }
    };
} // namespace CMD

#endif // JUMP_HH
