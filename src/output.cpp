#include "../inc/types.hpp"
#include <iostream>

void Output::printCode(){
    for (long long i = 0; i < programCode.size(); i++){
        // std::cout << "\033[1;34m " << i << "\033[0m " << programCode[i] << "\n";
        std::cerr << programCode[i] << "\n";
    }
}

void Output::updateCondJump(int result){
    for (int j = 0; j < result; j++){
        int temp = counter - condJumpCount.top();
        condJumpCount.pop();
        for (long long i = programCode.size() - 1; i >= 0; i--){
            if (programCode[i] == std::string("JZERO") || programCode[i] == std::string("JPOS") || programCode[i] == std::string("JNEG")){
                programCode[i] = programCode[i] + " "  + std::to_string(temp);
                break;
            }
        }
    }
}

void Output::updateJump(){
    long long temp = counter - jumpCount.top();
    jumpCount.pop();
    for (long long i = programCode.size() - 1; i >= 0; i--){
        if (programCode[i] == std::string("JUMP")){
            programCode[i] = programCode[i] + " "  + std::to_string(temp);
            break;
        }
    }
}

void Output::updateRepeat(int result){
    long long temp = repeatCount.top();
    repeatCount.pop();
    for (int j = 0; j < result; j++){
        for (long long i = programCode.size() - 1; i >= 0; i--){
            if (programCode[i] == std::string("JZERO") || programCode[i] == std::string("JPOS") || programCode[i] == std::string("JNEG")){
                programCode[i] = programCode[i] + " "  + std::to_string(temp - i);
                break;
            }
        }
    }
}

void Output::updateWhile(){
    long long temp = repeatCount.top();
    repeatCount.pop();
    programCode.push_back(std::string("JUMP ") + std::to_string(temp - counter));
    counter++;
}

void Output::get(){programCode.push_back("GET"); counter++;}
void Output::put(){programCode.push_back("PUT"); counter++;}
void Output::load(char c){programCode.push_back(std::string("LOAD ") + c); counter++;}  
void Output::store(char c){programCode.push_back(std::string("STORE ") + c); counter++;}  
void Output::add(char c){programCode.push_back(std::string("ADD ") + c); counter++;}  
void Output::sub(char c){programCode.push_back(std::string("SUB ") + c); counter++;}  
void Output::shift(char c){programCode.push_back(std::string("SHIFT ") + c); counter++;}  
void Output::swap(char c){programCode.push_back(std::string("SWAP ") + c); counter++;}  
void Output::reset(char c){programCode.push_back(std::string("RESET ") + c); counter++;}  
void Output::inc(char c){programCode.push_back(std::string("INC ") + c); counter++;}  
void Output::dec(char c){programCode.push_back(std::string("DEC ") + c); counter++;}  
void Output::jump(long long a){programCode.push_back(std::string("JUMP ") + std::to_string(a)); counter++;}  
void Output::jpos(long long a){programCode.push_back(std::string("JPOS ") + std::to_string(a)); counter++;}  
void Output::jzero(long long a){programCode.push_back(std::string("JZERO ") + std::to_string(a)); counter++;}  
void Output::jneg(long long a){programCode.push_back(std::string("JNEG ") + std::to_string(a)); counter++;}  
void Output::halt(){
    programCode.push_back("HALT");
    printCode();
}  

void Output::condJumpPlaceholder(std::string name){
    programCode.push_back(name);
    condJumpCount.push(counter);
    counter++;
}

void Output::jumpPlaceholder(){
    programCode.push_back(std::string("JUMP"));
    jumpCount.push(counter);
    counter++;
}

void Output::repeatPlaceholder(){
    repeatCount.push(counter);
}