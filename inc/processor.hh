#if !defined(PROCESSOR_HH)
#define PROCESSOR_HH
#include <array>
#include "types.hh"
#include "memory.hh"
#include "psw.hh"
#include "cmd.gch"

class processor
{
private:
    
    
    CMD::command *cmd[46];
    void initalize_commands();
    
    static word get_opcode(word first)
    {
        return (first >> 9);
    }
public:
    memory m;
    psw state;
    std::array<regtype,8> reg;
    processor();
    void reset();
    void set_ip(dword address);
    void run();
};

#endif // PROCESSOR_HH
