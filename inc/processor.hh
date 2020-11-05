#if !defined(PROCESSOR_HH)
#define PROCESSOR_HH

#include "interpretator.hh"
#include "memory.hh"
#include "command.hh"
#include "psw.hh"
#include <string>
#include <map>

class processor
{
private:
    memory& m;
    psw state;
    std::map<word,command*> cmd;
    bool process();
    void initalize_commands();
public:
    processor(memory& m);
    void run(dword start_address);
};




#endif // PROCESSOR_HH
