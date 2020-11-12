#if !defined(IO_HH)
#define IO_HH

#include "base_command.hh"
#include <iostream>

class out : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        std::string out_string = std::to_string(state.reg.integer[operation.op.r1]);
        std::cout << out_string << std::endl;
        state.IP++;
    }
};

class in : public command
{
public:
    virtual void execute(psw &state, memory &m)
    {
        std::cin >> state.reg.integer[operation.op.r1];
        state.IP++;
    }
};

#endif // IO_HH
