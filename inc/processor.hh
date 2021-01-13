#if !defined(PROCESSOR_HH)
#define PROCESSOR_HH
#include <array>
#include <map>
#include <string>
#include "processor_state.hh"
#include "cmd.gch"

class processor
{
private:
    enum commands
    {
        add = 44,sub = 1,mul = 2,_div = 3,
        fadd = 4,fsub = 5,fdiv = 6,fmul = 7,
        jmp = 8,
        ja = 11,
        jae = 16,
        jb = 19,
        jbe = 22,
        je = 25,
        jg = 28,
        jge = 31,
        jl = 34,
        jle = 37,
        call = 38,ret = 39,
        cmp = 40,
        in = 41,out = 42,
        movd = 43,
        halt = 0,
        fcomp = 45,
        bor = 46, bxor = 47, band = 48, bnot = 49
    };
    std::map<commands,CMD::command *> cmd; //ассоциативный массив с обработчиками команд
    void initalize_commands();
    operation_type current;
public:
    processor_state s;//доступ к состоянию процессора
    processor(std::string filename);
    void reset();
    void set_ip(word address);
    void run();
};

#endif // PROCESSOR_HH
