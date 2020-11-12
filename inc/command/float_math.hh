#if !defined(FLOAT_MATH_HH)
#define FLOAT_MATH_HH

#include "base_command.hh"

class fadd : public command
{
public:
    void execute(psw &state, memory &m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] + state.reg.floating[operation.op.r3];
        state.IP++;
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
