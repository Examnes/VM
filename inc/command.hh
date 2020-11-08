#if !defined(COMMAND_HH)
#define COMMAND_HH

#include <stdint.h>
#include <memory.h>
#include "word.hh"
#include "psw.hh"
#include <limits>

typedef uint64_t result_type;

#define SIGN_BIT(x) (x >> (sizeof(x) * 8 - 1))

#define DEF_AS_BASE(x) typedef x base

#define DEF_ALL_JMP_USING_PRED(pred,jumpname) class jumpname ## d : public jmpd \
{\
    public:\
    void operator()(psw& state,memory& m)\
    {\
        bool zf = state.FLAGS & psw::flag_bits::zf;\
        bool sf = state.FLAGS & psw::flag_bits::sf;\
        bool of = state.FLAGS & psw::flag_bits::of;\
        bool cf = state.FLAGS & psw::flag_bits::cf;\
        if (pred)\
        {\
            base::operator()(state,m);\
        }\
    }\
};\
\
class jumpname ## r : public jmpr\
{\
    public:\
    void operator()(psw& state,memory& m)\
    {\
        bool zf = state.FLAGS & psw::flag_bits::zf;\
        bool sf = state.FLAGS & psw::flag_bits::sf;\
        bool of = state.FLAGS & psw::flag_bits::of;\
        bool cf = state.FLAGS & psw::flag_bits::cf;\
        if (pred)\
        {\
            base::operator()(state,m);\
        }\
    }\
};\
\
class jumpname ## i : public jmpi\
{\
    public:\
    void operator()(psw& state,memory& m)\
    {\
        bool zf = state.FLAGS & psw::flag_bits::zf;\
        bool sf = state.FLAGS & psw::flag_bits::sf;\
        bool of = state.FLAGS & psw::flag_bits::of;\
        bool cf = state.FLAGS & psw::flag_bits::cf;\
        if (pred)\
        {\
            base::operator()(state,m);\
        }\
    }\
};\


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
    void set_flags(psw& state,result_type res)
    {
        if (res > std::numeric_limits<dword>::max())
        {
            state.FLAGS |= state.cf;
        }else
        {
            state.FLAGS &= ~state.cf;
        }

        if  ((SIGN_BIT(state.reg.integer[operation.op.r2]) and 
             SIGN_BIT(state.reg.integer[operation.op.r3]) and not
             SIGN_BIT(state.reg.integer[operation.op.r1])) 
            or 
            (not SIGN_BIT(state.reg.integer[operation.op.r2]) and 
             not SIGN_BIT(state.reg.integer[operation.op.r3]) and 
             SIGN_BIT(state.reg.integer[operation.op.r1])))
        {
            state.FLAGS |= state.of;
        }else
        {
            state.FLAGS &= ~state.of;
        }

        if (res == 0)
        {
            state.FLAGS |= state.zf;
        }else
        {
            state.FLAGS &= ~state.zf;
        }
    }
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

    command()
    {

    };

    virtual void operator()(psw& state,memory& m) = 0;
};

class mov : public command
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
            state.reg.integer[operation.op.r1] = m[ state.reg.integer[operation.op.r3] + operation.op.constant ];
            break;
        case dir::rbm:
            m[ state.reg.integer[operation.op.r3] + operation.op.constant ] = state.reg.integer[operation.op.r1];
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
        }else
        {
            state.IP++;
        }
    }
};

class add : public command
{
public:
    void operator()(psw& state,memory& m)
    {
        result_type res = (result_type)state.reg.integer[operation.op.r2] + state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;
        set_flags(state,res);
        state.IP++;
    }
};

class sub : public command
{
public:
    virtual void operator()(psw& state,memory& m)
    {
        dword temp = state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r3] = ~state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r3]++;

        result_type res = (result_type)state.reg.integer[operation.op.r2] + state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;

        state.reg.integer[operation.op.r3] = temp;
        set_flags(state,res);
    }
};

class mul : public command
{
public:
    void operator()(psw& state,memory& m)
    {
        result_type res = (result_type)state.reg.integer[operation.op.r2] * state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;
        set_flags(state,res);
        state.IP++;
    }
};

class _div : public command
{
public:
    void operator()(psw& state,memory& m)
    {
        result_type res = (result_type)state.reg.integer[operation.op.r2] / state.reg.integer[operation.op.r3];
        state.reg.integer[operation.op.r1] = res;
        set_flags(state,res);
        state.IP++;
    }
};


class fadd : public command
{
public:
    void operator()(psw& state,memory& m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] + state.reg.floating[operation.op.r3];
        state.IP++;
    }
};

class fsub : public command
{
public:
    void operator()(psw& state,memory& m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] - state.reg.floating[operation.op.r3];
        state.IP++;
    }   
};

class fmul : public command
{
public:
    void operator()(psw& state,memory& m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] * state.reg.floating[operation.op.r3];
        state.IP++;
    }
};

class fdiv : public command
{
public:
    void operator()(psw& state,memory& m)
    {
        state.reg.floating[operation.op.r1] = state.reg.floating[operation.op.r2] / state.reg.floating[operation.op.r3];
        state.IP++;
    }
};

class jmpd : public command
{
private:
    enum based : word
    {
        yes = 1,
        no = 3
    };

public:
    virtual void operator()(psw& state,memory& m)
    {
        switch (operation.op.r2)
        {
        case based::yes:
            state.IP = operation.op.constant;
            break;
        case based::no:
            state.IP = operation.op.constant + state.reg.integer[operation.op.r3];
            break;
        default:
            break;
        }
    }
    DEF_AS_BASE(jmpd);
};

class jmpr : public command
{
public:
    virtual void operator()(psw& state,memory& m)
    {
        state.IP += (int8_t)(operation.parts[0] & 0b11111111);
    }
    DEF_AS_BASE(jmpr);
};

class jmpi : public command
{
public:
    virtual void operator()(psw& state,memory& m)
    {
        state.IP = state.reg.integer[operation.op.r1];
    }
    DEF_AS_BASE(jmpi);
};

DEF_ALL_JMP_USING_PRED(!cf and !zf,ja);
DEF_ALL_JMP_USING_PRED(!cf,jae);
DEF_ALL_JMP_USING_PRED(cf,jb);
DEF_ALL_JMP_USING_PRED(cf and zf,jbe);
DEF_ALL_JMP_USING_PRED(zf,je);
DEF_ALL_JMP_USING_PRED(!zf and sf == of,jg);
DEF_ALL_JMP_USING_PRED(sf == of,jge);
DEF_ALL_JMP_USING_PRED(sf != of,jl);
DEF_ALL_JMP_USING_PRED(sf != of and zf,jle);

class call : public jmpd
{
public:
    virtual void operator()(psw& state,memory& m)
    {
        state.reg.integer[operation.op.r1] = state.IP + 1;
        base::operator()(state,m);
    }
};

class ret : public command
{
public:
    virtual void operator()(psw& state,memory& m)
    {
        state.IP = state.reg.integer[operation.op.r1];
    }
};

class cmp : public  sub
{
    public:
    virtual void operator()(psw& state,memory& m)
    {
        dword temp = state.reg.integer[operation.op.r1];
        sub::operator()(state,m);
        state.reg.integer[operation.op.r1] = temp;
    }
};

#endif // COMMAND_HH
