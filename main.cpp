#include <iostream>

using namespace std;
#include "interpretator.hh"

int main(int argc,char** argv)
{
    interpretator i(argv[1],stol(argv[2]));
    return 0;
}