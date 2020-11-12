#if !defined(JUMP_HH)
#define JUMP_HH

#include "base_command.hh"

class jmpd : public command
{
private:
    enum based : word
    {
        yes = 1,
        no = 3
    };
    //r2 определяет будет ли использоваться базовый регистр или нет
public:
    virtual void execute(psw &state, memory &m)
    {
        switch (operation.op.r2)
        {
        case based::no:
            state.IP = operation.op.constant;
            break;
        //если да, то этим регистром будет r3
        case based::yes:
            state.IP = operation.op.constant + state.reg.integer[operation.op.r3];
            break;
        default:
            break;
        }
    }
    //чтобы при наследовании можно было писать base:: и операции базового класса
    //и не запоминать его название.
    DEF_AS_BASE(jmpd);
};

class jmpr : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        //чтобы пригнуть относительно нужно трактовать r1 r2 r3 \
        //как одно знаковое число длиной 1 байт
        state.IP += (int8_t)(operation.parts[0] & 0xFF);
    }
    DEF_AS_BASE(jmpr);
};

//прыжок по адресу, который лежит в регистре r1
class jmpi : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        state.IP = state.reg.integer[operation.op.r1];
    }
    DEF_AS_BASE(jmpi);
};

//кажется так нельзя делать, но так проще
#define DEF_ALL_JMP_USING_PRED(pred, jumpname)          \
    class jumpname##d : public jmpd                     \
    {                                                   \
    public:                                             \
        void execute(psw &state, memory &m)             \
        {                                               \
            bool zf = state.FLAGS & psw::flag_bits::zf; \
            bool sf = state.FLAGS & psw::flag_bits::sf; \
            bool of = state.FLAGS & psw::flag_bits::of; \
            bool cf = state.FLAGS & psw::flag_bits::cf; \
            if (pred)                                   \
            {                                           \
                base::execute(state, m);                \
            }                                           \
        }                                               \
    };                                                  \
                                                        \
    class jumpname##r : public jmpr                     \
    {                                                   \
    public:                                             \
        void execute(psw &state, memory &m)             \
        {                                               \
            bool zf = state.FLAGS & psw::flag_bits::zf; \
            bool sf = state.FLAGS & psw::flag_bits::sf; \
            bool of = state.FLAGS & psw::flag_bits::of; \
            bool cf = state.FLAGS & psw::flag_bits::cf; \
            if (pred)                                   \
            {                                           \
                base::execute(state, m);                \
            }                                           \
        }                                               \
    };                                                  \
                                                        \
    class jumpname##i : public jmpi                     \
    {                                                   \
    public:                                             \
        void execute(psw &state, memory &m)             \
        {                                               \
            bool zf = state.FLAGS & psw::flag_bits::zf; \
            bool sf = state.FLAGS & psw::flag_bits::sf; \
            bool of = state.FLAGS & psw::flag_bits::of; \
            bool cf = state.FLAGS & psw::flag_bits::cf; \
            if (pred)                                   \
            {                                           \
                base::execute(state, m);                \
            }                                           \
        }                                               \
    };

//так можно одной строчкой обявить условный прыжок, который проверяет
//нужные флаги, и сразу будут обьявлены все возможные прыжки.
DEF_ALL_JMP_USING_PRED(!cf and !zf, ja);
DEF_ALL_JMP_USING_PRED(!cf, jae);
DEF_ALL_JMP_USING_PRED(cf, jb);
DEF_ALL_JMP_USING_PRED(cf and zf, jbe);
DEF_ALL_JMP_USING_PRED(zf, je);
DEF_ALL_JMP_USING_PRED(!zf and sf == of, jg);
DEF_ALL_JMP_USING_PRED(sf == of, jge);
DEF_ALL_JMP_USING_PRED(sf != of, jl);
DEF_ALL_JMP_USING_PRED(sf != of and zf, jle);

#endif // JUMP_HH
