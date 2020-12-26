#include <iostream>
#include "processor.hh"


using namespace std;
//первый аргумент - имя входного файла
int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    processor p = processor(filename);
    p.run();
    cout << "Iterpretation end" << endl;
    return 0;
}
