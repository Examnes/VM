#if !defined(IO_HH)
#define IO_HH

#include "base_command.hh"
#include <iostream>

namespace CMD
{
    //ввод и вывод работают через стандартные операции cin cout
    class out : public common_command
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            //а без этого почему то не работает, хотя должно
            std::string out_string = std::to_string(reg[operation.op.r1].integer);
            std::cout << out_string << std::endl;
        }
    };

    class in : public common_command
    {
    public:
        virtual void execute(psw &state, std::array<regtype,8> &reg, memory &m)
        {
            std::cin >> reg[operation.op.r1].integer;
        }
    };
} // namespace CMD

#endif // IO_HH
