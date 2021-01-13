#if !defined(PROC_STATE_HH)
#define PROC_STATE_HH

#include "types.hh"
#include "memory.hh"
//чтобы избежать циклических зависимостей 
//выделили общую для processor и command часть в отдельный класс
struct processor_state 
{
    bool stop;
    memory m;
    psw state;
    std::array<regtype,8> reg;
};


#endif // PROC_STATE_HH
