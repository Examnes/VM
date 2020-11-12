#if !defined(FLOAT_MATH_HH)
#define FLOAT_MATH_HH

#include "base_command.hh"

//все арифметические операции над числами с плавающей точкой аналогичны операциям с обычными числами
//только используется другое представление регистров floating
class fadd : public command
{
public:
    void execute(psw &state, memory &m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] + state.reg.floating[operation.op.r3];
        state.IP++;
        //флаги не ставятся, но обычно проверить что одно число больше или меньше другого можно 
        //так же как с обычными числами
        //потому что float сделан так, что если a > b то и float(a) > float(b);
    }
};

class fsub : public command
{
public:
    void execute(psw &state, memory &m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] - state.reg.floating[operation.op.r3];
        state.IP++;
    }
};

class fmul : public command
{
public:
    void execute(psw &state, memory &m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] * state.reg.floating[operation.op.r3];
        state.IP++;
    }
};

class fdiv : public command
{
public:
    void execute(psw &state, memory &m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] / state.reg.floating[operation.op.r3];
        state.IP++;
    }
};

#endif // FLOAT_MATH_HH
