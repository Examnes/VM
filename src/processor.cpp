#include "processor.hh"
#include <memory.h>
#include "loader.hh"

processor::processor(std::string filename):s()
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

    cmd[commands::jmp] = new CMD::jump();

    cmd[commands::ja] = new CMD::conditional_jump([](psw f) { return !f.FLAGS.cf and !f.FLAGS.zf; }); //ja = !cf & !zf

    cmd[commands::jae] = new CMD::conditional_jump([](psw f) { return !f.FLAGS.cf; }); //jae = !cf

    cmd[commands::jb] = new CMD::conditional_jump([](psw f) { return f.FLAGS.cf; }); //jb = cf

    cmd[commands::jbe] = new CMD::conditional_jump([](psw f) { return f.FLAGS.cf and f.FLAGS.zf; }); //jbe = cf & zf

    cmd[commands::je] = new CMD::conditional_jump([](psw f) { return f.FLAGS.zf; }); //je = zf

    cmd[commands::jg] = new CMD::conditional_jump([](psw f) { return !f.FLAGS.zf and (f.FLAGS.sf == f.FLAGS.of); }); //jg = sf == of & !zf
    
    cmd[commands::jge] = new CMD::conditional_jump([](psw f) { return f.FLAGS.sf == f.FLAGS.of; }); //jge = sf == of

    cmd[commands::jl] = new CMD::conditional_jump([](psw f) { return f.FLAGS.sf != f.FLAGS.of; }); //jl = sf != of

    cmd[commands::jle] = new CMD::conditional_jump([](psw f) { return f.FLAGS.zf and f.FLAGS.sf != f.FLAGS.of; });  //jle = sf != of & zf

    cmd[commands::call] = new CMD::call();
    cmd[commands::ret] = new CMD::ret();
    cmd[commands::cmp] = new CMD::cmp();

    cmd[commands::in] = new CMD::in();
    cmd[commands::out] = new CMD::out();
    cmd[commands::movd] = new CMD::movd();
    cmd[commands::halt] = new CMD::halt();
    cmd[commands::fcomp] = new CMD::fcomp();
    cmd[commands::bor] = new CMD::bor();
    cmd[commands::bxor] = new CMD::bxor();
    cmd[commands::band] = new CMD::band();
    cmd[commands::bnot] = new CMD::bnot();
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
