#if !defined(MATH_HH)
#define MATH_HH
#include "base_command.hh"

class add : public command
{
public:
    void execute(psw &state, memory &m)
    {
        //чтобы нормально ставить флаги нужно чтобы в результат поместился результат даже с переполнением.
        result_type res = (result_type)state.reg.integer[operation.op.r2] + state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;
        set_flags(state, res);
        state.IP++;
    }
};

class sub : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        //вычитание это сложение с инверсией, но это будет работать аналогично.
        result_type res = (result_type)state.reg.signed_integer[operation.op.r2] - state.reg.signed_integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;
        set_flags(state, res);
    }
};

class mul : public command
{
public:
    void execute(psw &state, memory &m)
    {
        
        result_type res = (result_type)state.reg.integer[operation.op.r2] * state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;
        set_flags(state, res);
        state.IP++;
    }
};

class _div : public command
{
public:
    void execute(psw &state, memory &m)
    {
        result_type res = (result_type)state.reg.integer[operation.op.r2] / state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;
        set_flags(state, res);
        state.IP++;
    }
};

#endif // MATH_HH
