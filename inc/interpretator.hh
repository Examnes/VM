#if !defined(INTERPRETATOR_HH)
#define INTERPRETATOR_HH

#include "processor.hh"

class interpretator
{
private:
    memory m;
    processor p;
public:
    interpretator(std::string input_filename, size_t offset_of_program):m(input_filename, offset_of_program),p(m)
    {
        p.run(offset_of_program);
    }
};

#endif // INTERPRETATOR_HH
