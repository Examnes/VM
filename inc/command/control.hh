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
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            reg.integer[operation.op.r1] = state.IP + 1;
            base::execute(state, reg, m);
        }
    };
    //потом этот адрес возврата нужно использовать в команде ret
    class ret : public changing_ip_command
    {
    public:
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            state.IP = reg.integer[operation.op.r1];
        }
    };
    //cmp делает то же самое что и вычитание, только не сохраняет рпезультат, только флаги ставит.
    class cmp : public sub
    {
    public:
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            //так как sub все таки сохраняет результат,
            //желательно чтобы он всегда сохранялся в одно место.
            operation.op.r1 = 0b010;
            dword temp = reg.integer[operation.op.r1];
            sub::execute(state, reg, m);
            //но после выполненния нужно вернуть назад прошлое значение этого регистра
            reg.integer[operation.op.r1] = temp;
        }
    };
    //эта команда должна быть в конце программы, она устанавливает флаг остановки
    //когда он будет установлен интерпретация закончится.
    class halt : public common_command
    {
    public:
        virtual void execute(psw &state, registers &reg, memory &m)
        {
            state.FLAGS.stop = true;
        }
    };
} // namespace CMD

#endif // COMPARASION_HH
