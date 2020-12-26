#if !defined(COMMAND_HH)
#define COMMAND_HH

#include <cstdint>
#include <limits>
#include "processor_state.hh"

using result_type = uint64_t;
#define SIGN_BIT(x) (x >> (sizeof(x) * 8 - 1))
#define DEF_AS_BASE(x) typedef x base


namespace CMD
{
    class command
    {
    protected:
        operation_type operation;
    public:
        void init(operation_type op)
        {
            operation = op;
        }
        command() = default;
        virtual void execute(processor_state& p) = 0;
        virtual word get_size() = 0;
    };

    class common_command : public command
    {
    public:
        word get_size()
        {
            return 1;
        }
    };

    class extended_command : public command
    {
    public:
        word get_size()
        {
            return 2;
        }
    };
} // namespace CMD

#endif // COMMAND_HH
