#include "../inc/types.hpp"
extern Output* output;

int Condition::loadIf(){
    int result;
    val2->load();
    output->swap('h');
    val1->load();
    output->sub('h');
    switch (type){
        case Conditions::EQ:
            output->condJumpPlaceholder("JNEG");
            output->condJumpPlaceholder("JPOS");
            result = 2;
            break;
        case Conditions::NEQ:
            output->condJumpPlaceholder("JZERO");
            result = 1;
            break;
        case Conditions::LE:
            output->condJumpPlaceholder("JZERO");
            output->condJumpPlaceholder("JPOS");
            result = 2;
            break;
        case Conditions::GE:
            output->condJumpPlaceholder("JZERO");
            output->condJumpPlaceholder("JNEG");
            result = 2;
            break;
        case Conditions::LEQ:
            output->condJumpPlaceholder("JPOS");
            result = 1;
            break;
        case Conditions::GEQ:
            output->condJumpPlaceholder("JNEG");
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

void Condition::remove(){
    val1->remove();
    val2->remove();
    delete this;
}