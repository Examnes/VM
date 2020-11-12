#include "processor.hh"

processor::processor(memory m)
{
    state.IP = 0;
    state.FLAGS = 0;
    this->m = m;
    initalize_commands();
}

void processor::initalize_commands()
{
    cmd[cmov] = new mov();

    cmd[cadd] = new add();
    cmd[csub] = new sub();
    cmd[cdiv] = new _div();
    cmd[cmul] = new mul();

    cmd[cfadd] = new fadd();
    cmd[cfsub] = new fsub();
    cmd[cfdiv] = new fdiv();
    cmd[cfmul] = new fmul();

    cmd[cjmpd] = new jmpd();
    cmd[cjmpr] = new jmpr();
    cmd[cjmpi] = new jmpi();

    //ад дальше
    cmd[cjad] = new jad();
    cmd[cjar] = new jar();
    cmd[cjai] = new jai();

    cmd[cjaed] = new jaed();
    cmd[cjaer] = new jaer();
    cmd[cjaei] = new jaei();

    cmd[cjbd] = new jbd();
    cmd[cjbr] = new jbr();
    cmd[cjbi] = new jbi();

    cmd[cjbed] = new jbed();
    cmd[cjber] = new jber();
    cmd[cjbei] = new jbei();

    cmd[cjed] = new jed();
    cmd[cjer] = new jer();
    cmd[cjei] = new jei();

    cmd[cjgd] = new jgd();
    cmd[cjgr] = new jgr();
    cmd[cjgi] = new jgi();

    cmd[cjged] = new jged();
    cmd[cjger] = new jger();
    cmd[cjgei] = new jgei();

    cmd[cjld] = new jld();
    cmd[cjlr] = new jlr();
    cmd[cjli] = new jli();

    cmd[cjled] = new jled();
    cmd[cjler] = new jler();
    cmd[cjlei] = new jlei();

    cmd[ccall] = new call();
    cmd[cret] = new ret();
    cmd[ccmp] = new cmp();

    cmd[c_in] = new in();
    cmd[c_out] = new out();
    cmd[c_movd] = new movd();
    cmd[chalt] = new halt();
}

void processor::process()
{
    word op = command::get_opcode(m[state.IP]);
    command *curcommand = cmd[op];
    curcommand->init(m[state.IP], m[state.IP + 1]);
    curcommand->execute(state, m);
}

void processor::run(dword start_address)
{
    state.IP = start_address;
    while (!state.stop)
    {
        process();
    }
}
