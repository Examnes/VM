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
        jmpd = 8,jmpr = 9,jmpi = 10,
        jad = 11,jar = 12,jai = 13,
        jaed = 14,jaer = 15,jaei = 16,
        jbd = 17,jbr = 18,jbi = 19,
        jbed = 20,jber = 21,jbei = 22,
        jed = 23,jer = 24,jei = 25,
        jgd = 26,jgr = 27,jgi = 28,
        jged = 29,jger = 30,jgei = 31,
        jld = 32,jlr = 33,jli = 34,
        jled = 35,jler = 36,jlei = 37,
        call = 38,ret = 39,
        cmp = 40,
        in = 41,out = 42,
        movd = 43,
        halt = 0
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
