#include "processor.hh"
#include <memory.h>

processor::processor(memory m)
{
    state.IP = 0;
    this->m = m;
    initalize_commands();
    memset(&state,0,sizeof(state));
}

void processor::initalize_commands()
{
    cmd[commands::add] = new CMD::add();
    cmd[commands::sub] = new CMD::sub();
    cmd[commands::_div] = new CMD::_div();
    cmd[commands::mul] = new CMD::mul();

    cmd[commands::fadd] = new CMD::fadd();
    cmd[commands::fsub] = new CMD::fsub();
    cmd[commands::fdiv] = new CMD::fdiv();
    cmd[commands::fmul] = new CMD::fmul();

    cmd[commands::jmpd] = new CMD::jmpd();
    cmd[commands::jmpr] = new CMD::jmpr();
    cmd[commands::jmpi] = new CMD::jmpi();

    //ад дальше
    cmd[commands::jad] = new CMD::conditional_jmpd([](psw f) { return !f.FLAGS.cf and !f.FLAGS.zf; });
    cmd[commands::jar] = new CMD::conditional_jmpr([](psw f) { return !f.FLAGS.cf and !f.FLAGS.zf; });
    cmd[commands::jai] = new CMD::conditional_jmpi([](psw f) { return !f.FLAGS.cf and !f.FLAGS.zf; });

    cmd[commands::jaed] = new CMD::conditional_jmpd([](psw f) { return !f.FLAGS.cf; });
    cmd[commands::jaer] = new CMD::conditional_jmpr([](psw f) { return !f.FLAGS.cf; });
    cmd[commands::jaei] = new CMD::conditional_jmpi([](psw f) { return !f.FLAGS.cf; });

    cmd[commands::jbd] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.cf; });
    cmd[commands::jbr] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.cf; });
    cmd[commands::jbi] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.cf; });

    cmd[commands::jbed] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.cf and f.FLAGS.zf; });
    cmd[commands::jber] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.cf and f.FLAGS.zf; });
    cmd[commands::jbei] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.cf and f.FLAGS.zf; });

    cmd[commands::jed] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.zf; });
    cmd[commands::jer] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.zf; });
    cmd[commands::jei] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.zf; });

    cmd[commands::jgd] = new CMD::conditional_jmpd([](psw f) { return !f.FLAGS.zf and (f.FLAGS.sf == f.FLAGS.of); });
    cmd[commands::jgr] = new CMD::conditional_jmpr([](psw f) { return !f.FLAGS.zf and (f.FLAGS.sf == f.FLAGS.of); });
    cmd[commands::jgi] = new CMD::conditional_jmpi([](psw f) { return !f.FLAGS.zf and (f.FLAGS.sf == f.FLAGS.of); });

    cmd[commands::jged] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.sf == f.FLAGS.of; });
    cmd[commands::jger] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.sf == f.FLAGS.of; });
    cmd[commands::jgei] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.sf == f.FLAGS.of; });

    cmd[commands::jld] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.sf != f.FLAGS.of; });
    cmd[commands::jlr] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.sf != f.FLAGS.of; });
    cmd[commands::jli] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.sf != f.FLAGS.of; });

    cmd[commands::jled] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.zf and f.FLAGS.sf != f.FLAGS.of; });
    cmd[commands::jler] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.zf and f.FLAGS.sf != f.FLAGS.of; });
    cmd[commands::jlei] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.zf and f.FLAGS.sf != f.FLAGS.of; });

    cmd[commands::call] = new CMD::call();
    cmd[commands::ret] = new CMD::ret();
    cmd[commands::cmp] = new CMD::cmp();

    cmd[commands::in] = new CMD::in();
    cmd[commands::out] = new CMD::out();
    cmd[commands::movd] = new CMD::movd();
    cmd[commands::halt] = new CMD::halt();
}

void processor::set_ip(dword address)
{
    state.IP = address;
}

void processor::reset()
{
    memset(&state,0,sizeof(state));
    state.IP = 0;
}

void processor::run()
{
    while (true)
    {
        word op = get_opcode(m[state.IP]);
        if(op == halt)
            break;
        CMD::command *curcommand = cmd[op];
        curcommand->init(m[state.IP], m[state.IP + 1]);
        curcommand->execute(state, reg, m);
        if(!state.FLAGS.ipcf)
            state.IP += curcommand->get_size();
        state.FLAGS.ipcf = false;
    }
}
