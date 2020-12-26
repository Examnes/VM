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
        virtual void execute(processor_state& p)
        {
            std::string out_string = std::to_string(p.reg[operation.op.r1].integer);
            std::cout << out_string << std::endl;
        }
    };

    class in : public common_command
    {
    public:
        virtual void execute(processor_state& p)
        {
            std::cin >> p.reg[operation.op.r1].integer;
        }
    };
} // namespace CMD

#endif // IO_HH
