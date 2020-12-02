#if !defined(COMPARASION_HH)
#define COMPARASION_HH

#include "base_command.hh"
#include "math.hh"
#include "jump.hh"

namespace CMD
{
    class call : public jmpd
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            reg[operation.op.r1].integer = state.IP + 1;
            base::execute(state, reg, m);
        }
    };
    //потом этот адрес возврата нужно использовать в команде ret
    class ret : public common_command
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            state.IP = reg[operation.op.r1].integer;
            state.FLAGS.ipcf = true;
        }
    };
    //cmp делает то же самое что и вычитание, только не сохраняет рпезультат, только флаги ставит.
    class cmp : public sub
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            //так как sub все таки сохраняет результат,
            //желательно чтобы он всегда сохранялся в одно место.
            operation.op.r1 = 0b010;
            dword temp = reg[operation.op.r1].integer;
            sub::execute(state, reg, m);
            //но после выполненния нужно вернуть назад прошлое значение этого регистра
            reg[operation.op.r1].integer = temp;
        }
    };
    //эта команда должна быть в конце программы
    //интерпретация закончится.
    class halt : public common_command
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            //ничего не нужно делать
        }
    };
} // namespace CMD

#endif // COMPARASION_HH
