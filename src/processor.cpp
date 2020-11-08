#include "processor.hh"
#include "command.hh"

processor::processor(memory &m) : m(m)
{
    state.IP = 0;
    state.FLAGS = 0;
}

void processor::initalize_commands()
{
    cmd[0] = new mov();

    cmd[1] = new add();
    cmd[2] = new sub();
    cmd[3] = new _div();
    cmd[4] = new mul();

    cmd[5] = new fadd();
    cmd[6] = new fsub();
    cmd[7] = new fdiv();
    cmd[8] = new fmul();

    cmd[9] = new jmpd();
    cmd[10] = new jmpr();
    cmd[11] = new jmpi();

    //ад дальше
    cmd[12] = new jad();
    cmd[13] = new jar();
    cmd[14] = new jai();

    cmd[15] = new jaed();
    cmd[16] = new jaer();
    cmd[17] = new jaei();

    cmd[18] = new jbd();
    cmd[19] = new jbr();
    cmd[20] = new jbi();

    cmd[21] = new jbed();
    cmd[22] = new jber();
    cmd[23] = new jbei();

    cmd[24] = new jed();
    cmd[25] = new jer();
    cmd[26] = new jei();

    cmd[27] = new jgd();
    cmd[28] = new jgr();
    cmd[29] = new jgi();

    cmd[30] = new jged();
    cmd[31] = new jger();
    cmd[32] = new jgei();

    cmd[33] = new jld();
    cmd[34] = new jlr();
    cmd[35] = new jli();

    cmd[36] = new jled();
    cmd[37] = new jler();
    cmd[38] = new jlei();

    cmd[39] = new call();
    cmd[40] = new ret();
    cmd[41] = new cmp();
}

void processor::process()
{
    word op = command::get_opcode(m[state.IP]);
    cmd[op]->init(m[state.IP], m[state.IP + 1]);
    (*cmd[op])(state,m);
}

void processor::run(dword start_address)
{
    state.IP = start_address;
    while (!m.is_out_of_bounds())
    {
        process();
    }
}