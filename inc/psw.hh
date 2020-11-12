#if !defined(PSW_HH)
#define PSW_HH

#include "word.hh"

struct psw
{
    word IP;
    word FLAGS;
    enum flag_bits
    {
        zf = 1,
        sf = 1 << 1,
        of = 1 << 2,
        cf = 1 << 3
    };
    //регистров 8 они используются для любых операций,
    //но у них есть несколько представлений
    //можно к ним обращаться как к числам с плавающей точкой
    //можно как к целочисленным или беззнаковым
    //а можно получить старшее слово и младшее слово,
    //ведь регистры состоять из двух слов
    union
    {
        dword integer[8] = {0};
        struct
        {
            word low;
            word up;
        } splited[8];
        int32_t signed_integer[8];
        float floating[8];
    } reg;
    //возможно, это тоже должно быть флагом
    bool stop = false;
};

#endif // PSW_HH
