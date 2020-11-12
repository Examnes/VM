#include <iostream>
#include "processor.hh"

using namespace std;
//первый аргумент - имя входного файла, второй - адрес начала программы
int main(int argc, char ** argv)
{
    std::string filename = argv[1]; 
    size_t offset = stoi(argv[2]);
    memory m = memory(filename);
    processor p = processor(m);
    p.run(offset);
    cout << "Iterpretation end" << endl;
    return 0;
}
