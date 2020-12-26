#include "processor.hh"
#include <memory.h>
#include "loader.hh"

processor::processor(std::string filename)
{
    s.state.IP = 0;
    initalize_commands();
    s.state = psw();
    word offset = load_memory(s.m,filename); //память создается в процессоре
    set_ip(offset);
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

    cmd[commands::jad] = new CMD::conditional_jmpd([](psw f) { return !f.FLAGS.cf and !f.FLAGS.zf; }); //ja = !cf & !zf
    cmd[commands::jar] = new CMD::conditional_jmpr([](psw f) { return !f.FLAGS.cf and !f.FLAGS.zf; });
    cmd[commands::jai] = new CMD::conditional_jmpi([](psw f) { return !f.FLAGS.cf and !f.FLAGS.zf; });

    cmd[commands::jaed] = new CMD::conditional_jmpd([](psw f) { return !f.FLAGS.cf; }); //jae = !cf
    cmd[commands::jaer] = new CMD::conditional_jmpr([](psw f) { return !f.FLAGS.cf; });
    cmd[commands::jaei] = new CMD::conditional_jmpi([](psw f) { return !f.FLAGS.cf; });

    cmd[commands::jbd] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.cf; }); //jb = cf
    cmd[commands::jbr] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.cf; });
    cmd[commands::jbi] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.cf; });

    cmd[commands::jbed] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.cf and f.FLAGS.zf; }); //jbe = cf & zf
    cmd[commands::jber] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.cf and f.FLAGS.zf; });
    cmd[commands::jbei] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.cf and f.FLAGS.zf; });

    cmd[commands::jed] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.zf; }); //je = zf
    cmd[commands::jer] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.zf; });
    cmd[commands::jei] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.zf; });

    cmd[commands::jgd] = new CMD::conditional_jmpd([](psw f) { return !f.FLAGS.zf and (f.FLAGS.sf == f.FLAGS.of); }); //jg = sf == of & !zf
    cmd[commands::jgr] = new CMD::conditional_jmpr([](psw f) { return !f.FLAGS.zf and (f.FLAGS.sf == f.FLAGS.of); });
    cmd[commands::jgi] = new CMD::conditional_jmpi([](psw f) { return !f.FLAGS.zf and (f.FLAGS.sf == f.FLAGS.of); });

    cmd[commands::jged] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.sf == f.FLAGS.of; }); //jge = sf == of
    cmd[commands::jger] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.sf == f.FLAGS.of; });
    cmd[commands::jgei] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.sf == f.FLAGS.of; });

    cmd[commands::jld] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.sf != f.FLAGS.of; }); //jl = sf != of
    cmd[commands::jlr] = new CMD::conditional_jmpr([](psw f) { return f.FLAGS.sf != f.FLAGS.of; });
    cmd[commands::jli] = new CMD::conditional_jmpi([](psw f) { return f.FLAGS.sf != f.FLAGS.of; });

    cmd[commands::jled] = new CMD::conditional_jmpd([](psw f) { return f.FLAGS.zf and f.FLAGS.sf != f.FLAGS.of; });  //jle = sf != of & zf
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

void processor::set_ip(word address)
{
    s.state.IP = address;
}

void processor::reset()
{
    s.state = psw();//обнулить psw
}

void processor::run()
{
    while (!s.stop)
    {
        current.parts[0] = s.m[s.state.IP]; //прочитать слово в команду по адресу IP
        current.parts[1] = s.m[s.state.IP + 1]; //прочитать слово в команду по адресу IP + 1
        CMD::command *curcommand = cmd.at((commands)current.op.op); // получить адрес обработчика с нужным опкодом
        curcommand->init(current); //обновить данные в обработчике прочитанной из памяти командой
        curcommand->execute(s); //выполнить команду передав в нее состояние процессора
        if(!s.state.FLAGS.ipcf)
            s.state.IP += curcommand->get_size(); //если IP не был изменен, то увеличить его на размер команды
        s.state.FLAGS.ipcf = false; // обнулить IPCF в любом случае
    }
}
