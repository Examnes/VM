#if !defined(COMMAND_HH)
#define COMMAND_HH

#include <stdint.h>
#include <memory.h>
#include "interpretator.hh"
#include "psw.hh"

class command
{
protected:
    union COP
    {
        struct
        {
            word op : 7;
            word r1 : 3;
            word r2 : 3;
            word r3 : 3;
            word constant; 
        } op;
        word parts[2];
    } operation;
public:
    void init(word first, word second = 0)
    {
        operation.parts[0] = first;
        operation.parts[1] = second;
    }
    static word get_opcode(word first)
    {
        return (first >> 9);
    }
    command();
    virtual void operator()(psw& state,memory& m) = 0;
};

class mov : command
{
private:
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
public:
    void operator()(psw& state,memory& m)
    {
        bool extended = true;
        switch (operation.op.r2)
        {
        case dir::rr:
            state.registers[operation.op.r1] = state.registers[operation.op.r3];
            extended = false;
            break;
        case dir::rm:
            m[operation.op.constant] = state.registers[operation.op.r1];
            break;
        case dir::mr:
            state.registers[operation.op.r1] = m[operation.op.constant];
            break;
        case dir::bmr:
            state.registers[operation.op.r1] = m[ state.registers[operation.op.r3] + operation.op.constant ];
            break;
        case dir::rbm:
            m[ state.registers[operation.op.r3] + operation.op.constant ] = state.registers[operation.op.r1];
            break;
        case dir::la:
            state.registers[operation.op.r1] = operation.op.constant;
            break;
        case dir::lba:
            state.registers[operation.op.r1] = state.registers[operation.op.r3] + operation.op.constant;
            break;
        default:
            break;
        }

        if (extended)
        {
            state.IP += 2;
        }else
        {
            state.IP++;
        }
    }
};

class add : command
{
public:
    void operator()(psw& state,memory& m)
    {
        state.registers[operation.op.r1]
    }
};

#endif // COMMAND_HH
