#include "../inc/types.hpp"
extern Declarations* declarations;
extern Registers* registers;
extern Output* output;

#define INC_COMMAND 1
#define SHIFT_COMMAND 2

void idValue::load(){
    ident->loadAddr();
    if (!ident->isIterator && !declarations->context_check(ident->getName())->isInitialized)
        declarations->throwErr(ident->getName() + " is uninitialized");
    output->load(registers->addr);
}

void numValue::load(){
    output->reset(registers->acc);
    if (std::llabs(value) > 10){
        output->reset('b');
        output->inc('b');
        std::stack<int> commands;
        while (std::llabs(value) != 1){
            if (std::llabs(value % 2) == 1)
                commands.push(INC_COMMAND);
            commands.push(SHIFT_COMMAND);
            value /= 2;
        }
        output->reset('a');
        if (value > 0){
            output->inc('a');
            while (!commands.empty()){
                if (commands.top() == INC_COMMAND)
                    output->inc('a');
                else
                    output->shift('b');
                commands.pop();
            }
        }
        else {
            output->dec('a');
            while (!commands.empty()){
                if (commands.top() == INC_COMMAND)
                    output->dec('a');
                else
                    output->shift('b');
                commands.pop();
            }
        }
    }
    else {
        if (value > 0) {
            for (long long i = 0; i < value; i++) {
                output->inc(registers->acc);
            }
        } 
        else {
            for (long long i = value; i < 0; i++) {
                output->dec(registers->acc);
            }
        }
    }
}

void idValue::remove(){
    ident->remove();
    delete this;
}

void numValue::remove(){
    delete this;
}