#if !defined(COMPARASION_HH)
#define COMPARASION_HH

#include "base_command.hh"
#include "math.hh"
#include "jump.hh"

class call : public jmpd
{
public:
    virtual void execute(psw &state, memory &m)
    {
        state.reg.integer[operation.op.r1] = state.IP + 1;
        base::execute(state, m);
    }
};

class ret : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        state.IP = state.reg.integer[operation.op.r1];
    }
};

class cmp : public sub
{
public:
    virtual void execute(psw &state, memory &m)
    {
        operation.op.r1 = 0b010;
        dword temp = state.reg.integer[operation.op.r1];
        sub::execute(state, m);
        state.reg.integer[operation.op.r1] = temp;
        state.IP++;
    }
};

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
