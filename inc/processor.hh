#if !defined(PROCESSOR_HH)
#define PROCESSOR_HH

#include "types.hh"
#include "memory.hh"
#include "psw.hh"
#include "cmd.gch"
#include <array>

class processor
{
private:
    memory m;
    psw state;
    CMD::command *cmd[46];
    void initalize_commands();
    std::array<regtype,8> reg;
    static word get_opcode(word first)
    {
        return (first >> 9);
    }
public:
    processor(memory m);
    void reset();
    void set_ip(dword address);
    void run();
};

#endif // PROCESSOR_HH
