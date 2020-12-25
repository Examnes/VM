#include <iostream>
#include "processor.hh"
#include "loader.hh"

using namespace std;
//первый аргумент - имя входного файла
int main(int argc, char ** argv)
{
    std::string filename = argv[1]; 
    memory m;
    size_t offset = load_memory(m,filename);
    processor p = processor(m);
    p.set_ip(offset);
    p.run();
    cout << "Iterpretation end" << endl;
    return 0;
}
