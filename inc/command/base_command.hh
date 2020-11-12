#if !defined(COMMAND_HH)
#define COMMAND_HH

#include <stdint.h>
#include <limits>
#include "word.hh"
#include "psw.hh"
#include "memory.hh"

typedef uint64_t result_type;

//получить бит знака - он последний
#define SIGN_BIT(x) (x >> (sizeof(x) * 8 - 1))

//добавить base к классу, чтобы работали базовые классы при наследовании
//у MS есть __super но он не стандартный да и работает только у них
#define DEF_AS_BASE(x) typedef x base

class command
{
protected:
    union COP
    {
        struct
        {
            word r3 : 3;
            word r2 : 3;
            word r1 : 3;
            word op : 7;
            word constant;
        } op; 
        //такой порядок у операндов, потому что little edian
        word parts[2];
        //COP можно инициализировать двумя словами
    } operation;
    void set_flags(psw &state, result_type res)
    {
        //cf ставится если результат вышел за пределы размера слова
        if (res > std::numeric_limits<dword>::max())
        {
            state.FLAGS |= psw::flag_bits::cf;
        }
        else
        {
            state.FLAGS &= ~psw::flag_bits::cf;
        }
        //of ставится если у результата бит знака не совпадает со знаками операндов
        bool op1sign = SIGN_BIT(state.reg.integer[operation.op.r2]);
        bool op2sign = SIGN_BIT(state.reg.integer[operation.op.r3]);
        bool ressign = SIGN_BIT(state.reg.integer[operation.op.r1]);
        if ((op1sign and op2sign and not ressign) or
            (not op1sign and not op2sign and ressign))
        {
            state.FLAGS |= psw::flag_bits::of;
        }
        else
        {
            state.FLAGS &= ~psw::flag_bits::of;
        }
        //флаг sf равен знаку результата
        if (ressign)
        {
            state.FLAGS |= psw::flag_bits::sf;
        }
        else
        {
            state.FLAGS &= ~psw::flag_bits::sf;
        }

        //zf ставится если результат нулевой
        if (res == 0)
        {
            state.FLAGS |= psw::flag_bits::zf;
        }
        else
        {
            state.FLAGS &= ~psw::flag_bits::zf;
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
    //функция должна быть реализована у всех наследников
    virtual void execute(psw &state, memory &m) = 0;
};

#endif // COMMAND_HH
