#include "processor.hh"
#include "command.hh"

processor::processor(memory &m) : m(m)
{
    state.IP = 0;
    state.FLAGS = 0;
}

void processor::initalize_commands()
{
    cmd[0] = 
}

bool processor::process()
{
    word op = command::get_opcode(m[state.IP]);
    cmd[op]->init(m[state.IP], m[state.IP + 1]);
    return (*cmd[op])(state,m);
}

void processor::run(dword start_address)
{
    state.IP = start_address;
    while (process());
}