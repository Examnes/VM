#include <iostream>
#include "processor.hh"


using namespace std;
//первый аргумент - имя входного файла
int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    try
    {
        processor p(filename);
        p.run();
        cout << "Iterpretation end" << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
