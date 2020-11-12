#if !defined(PROCESSOR_HH)
#define PROCESSOR_HH

#include "cmd.gch"
#include "word.hh"
#include "memory.hh"
#include "psw.hh"

class processor
{
private:
    memory m;
    psw state;
    command *cmd[44];
    void process();
    void initalize_commands();

public:
    processor(memory m);
    void run(dword start_address);
};

#endif // PROCESSOR_HH
