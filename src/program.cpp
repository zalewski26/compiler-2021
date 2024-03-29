#include <iostream>
#include "../inc/types.hpp"
extern Registers* registers;
extern Output* output;
extern Declarations* declarations;

void Program::compile(){
    output->reset(registers->addr);
    registers->addrVal = 0;

    for (const auto &command : *this->commands) {
        command->run();
    }
    output->halt();
    for (const auto &command : *this->commands) {
        command->remove();
    }
    delete commands;
    // declarations->print();
}

void Program::remove(){
    for (const auto &command : *this->commands) {
        command->remove();
    }
    delete commands;
}

