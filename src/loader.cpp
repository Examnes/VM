#include "loader.hh"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "types.hh"

using namespace std;

word load_memory(memory& m,std::string filename)
{
    ifstream file = ifstream(filename, std::ios::in | std::ios::binary);
    word start,offset;
    string line; 
    getline(file, line);
    stringstream ss = stringstream(line);
    ss >> start >> offset; //прочитать из первой строки адрес начала программы и смещение загрузки
    word ptr = offset;
    int line_counter = 0;
    while (getline(file, line)) 
    {
        stringstream ss = stringstream(line);
        string type;
        ss >> type;
        if(type == "c") //Первое слово в строке - тип команды в данном случае: операция
        {
            string cmdtype;
            ss >> cmdtype; //у операции есть 2 типа обычная и расширенная
            uint16_t r1,r2,r3,op; 
            operation_type first;
            ss >> op >> r1 >> r2 >> r3; //следующие 4 слова это опкод и операнды 1 2 и 3
            first.op.op = op;
            first.op.r1 = r1;
            first.op.r2 = r2;
            first.op.r3 = r3; 
            m[ptr++]= first.parts[0];
            if (cmdtype == "e")
            {
                ss >> first.op.address; //если операция расширенная то есть еще 5 слово которое означает адрес.
                m[ptr++] = first.parts[1];
            }
        }
        else if(type == "d") //еще есть тип команды: данные
        {
            string datatype;
            ss >> datatype; //у данных есть 3 типа
            regtype d;
            if (datatype == "i") //целое со знаком
            {
                ss >> d.signed_integer;
            }
            else if (datatype == "u") //целое без знака
            {
                ss >> d.integer;
            }
            else if (datatype == "f") //с плавающей точкой
            {
                ss >> d.floating;
            }
            m[ptr++] = d.part[0];
            m[ptr++] = d.part[1];
        }
        if (ss.fail())
        {
            throw logic_error("invalid sintax on line: " + to_string(line_counter));
        }
        line_counter++;
    }
    return start;
}
