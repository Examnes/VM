#if !defined(COMPARASION_HH)
#define COMPARASION_HH

#include "base_command.hh"
#include "math.hh"
#include "jump.hh"

//call это прямой прыжок, только перед прыжком сохраняется адрес возврата
class call : public jmpd
{
public:
    virtual void execute(psw &state, memory &m)
    {
        state.reg.integer[operation.op.r1] = state.IP + 1;
        base::execute(state, m);
    }
};
//потом этот адрес возврата нужно использовать в команде ret
class ret : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        state.IP = state.reg.integer[operation.op.r1];
    }
};
//cmp делает то же самое что и вычитание, только не сохраняет рпезультат, только флаги ставит.
class cmp : public sub
{
public:
    virtual void execute(psw &state, memory &m)
    {
        //так как sub все таки сохраняет результат,
        //желательно чтобы он всегда сохранялся в одно место.
        operation.op.r1 = 0b010;
        dword temp = state.reg.integer[operation.op.r1];
        sub::execute(state, m);
        //но после выполненния нужно вернуть назад прошлое значение этого регистра
        state.reg.integer[operation.op.r1] = temp;
        state.IP++;
    }
};
//эта команда должна быть в конце программы, она устанавливает флаг остановки
//когда он будет установлен интерпретация закончится.
class halt : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        state.stop = true;
        state.IP++;
    }
};

#endif // COMPARASION_HH
