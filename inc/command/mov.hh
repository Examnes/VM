#if !defined(MOV_HH)
#define MOV_HH

#include "base_command.hh"

enum dir : word
{
    rr = 0,
    rm = 1,
    rbm = 3,
    mr = 5,
    bmr = 7,
    la = 2,
    lba = 6
};

class mov : public command
{
public:
    void execute(psw &state, memory &m) override
    {
        bool extended = true;
        switch (operation.op.r2)
        {
        case dir::rr:
            state.reg.integer[operation.op.r1] = state.reg.integer[operation.op.r3];
            extended = false;
            break;
        case dir::rm:
            m[operation.op.constant] = state.reg.integer[operation.op.r1];
            break;
        case dir::mr:
            state.reg.integer[operation.op.r1] = m[operation.op.constant];
            break;
        case dir::bmr:
            state.reg.integer[operation.op.r1] = m[state.reg.integer[operation.op.r3] + operation.op.constant];
            break;
        case dir::rbm:
            m[state.reg.integer[operation.op.r3] + operation.op.constant] = state.reg.integer[operation.op.r1];
            break;
        case dir::la:
            state.reg.integer[operation.op.r1] = operation.op.constant;
            break;
        case dir::lba:
            state.reg.integer[operation.op.r1] = state.reg.integer[operation.op.r3] + operation.op.constant;
            break;
        default:
            break;
        }

        if (extended)
        {
            state.IP += 2;
        }
        else
        {
            state.IP++;
        }
    }
};

class movd : public command
{
public:
    void execute(psw &state, memory &m)
    {
        bool extended = true;
        switch (operation.op.r2)
        {
        case dir::rr:
            state.reg.integer[operation.op.r1] = state.reg.integer[operation.op.r3];
            extended = false;
            break;
        case dir::rm:
            m[operation.op.constant] = state.reg.splited[operation.op.r1].up;
            m[operation.op.constant + 1] = state.reg.splited[operation.op.r1].low;
            break;
        case dir::mr:
            state.reg.splited[operation.op.r1].up = m[operation.op.constant];
            state.reg.splited[operation.op.r1].low = m[operation.op.constant + 1];
            break;
        case dir::bmr:
            state.reg.splited[operation.op.r1].up = m[state.reg.integer[operation.op.r3] + operation.op.constant];
            state.reg.splited[operation.op.r1].low = m[state.reg.integer[operation.op.r3] + operation.op.constant + 1];
            break;
        case dir::rbm:
            m[state.reg.integer[operation.op.r3] + operation.op.constant] = state.reg.splited[operation.op.r1].up;
            m[state.reg.integer[operation.op.r3] + operation.op.constant + 1] = state.reg.splited[operation.op.r1].low;
            break;
        case dir::la:
            state.reg.integer[operation.op.r1] = operation.op.constant;
            break;
        case dir::lba:
            state.reg.integer[operation.op.r1] = state.reg.integer[operation.op.r3] + operation.op.constant;
            break;
        default:
            break;
        }

        if (extended)
        {
            state.IP += 2;
        }
        else
        {
            state.IP++;
        }
    }
};

#endif // MOV_HH
