#include "loader.hh"
#include <fstream>
#include <string>
#include <sstream>
#include "types.hh"

using namespace std;

word load_memory(memory& m,std::string filename)
{
    ifstream file = ifstream(filename, std::ios::in | std::ios::binary);
    word start;
    string line; 
    getline(file, line);
    start = stoi(line);
    word ptr = 0;
    int line_counter = 0;
    while (getline(file, line)) 
    {
        stringstream ss = stringstream(line);
        string type;
        ss >> type;
        if(type == "cmd")
        {
            string cmdtype;
            ss >> cmdtype;
            uint16_t r1,r2,r3,op;
            word extend;
            ss >> op >> r1 >> r2 >> r3;
            word first = r3;
            first |= r2 << 3;
            first |= r1 << 6;
            first |= op << 9;
            m[ptr++]= first;
            if (cmdtype == "extended")
            {
                ss >> extend;
                m[ptr++] = extend;
            }
        }
        else if(type == "data")
        {
            string datatype;
            ss >> datatype;
            regtype d;
            if (datatype == "int")
            {
                ss >> d.signed_integer;
            }
            else if (datatype == "uint")
            {
                ss >> d.integer;
            }
            else if (datatype == "float")
            {
                ss >> d.floating;
            }
            m[ptr++] = d.part[0];
            m[ptr++] = d.part[1];
        }
        if (ss.fail())
        {
            throw "invalid sintax on line: " + to_string(line_counter);
        }
        line_counter++;
    }
    return start;
}
