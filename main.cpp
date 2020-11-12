#include <iostream>
#include "processor.hh"
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
    std::string filename = argv[1];
    size_t offset = stoi(argv[2]);
    memory m = memory(filename);
    processor p = processor(m);
    p.run(offset);
    cout << "Iterpretation end" << endl;
    return 0;
}
