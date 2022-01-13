#include "../inc/types.hpp"
extern Output* output;

void SingleExpression::load(){
    val->load();
}

void BinaryExpression::load(){
    switch (type){
        case Operations::ADD:
            val2->load();
            output->swap('d');
            val1->load();
            output->add('d');
            break;
        case Operations::SUBTRACT:
            val2->load();
            output->swap('d');
            val1->load();
            output->sub('d');
            break;
        case Operations::MULTIPLY:
            /*  x * y:    
                    'c'= x  'd'= y  'e'= wynik  'f'= 1 (shift) 'g'= -1 (shift)
            */
            val2->load();
            output->swap('d');
            val1->load();
            output->swap('c');
            // zerowanie e, ustawianie f i g pod shifty
            output->reset('e');
            output->reset('f');
            output->inc('f');
            output->reset('g');
            output->dec('g');
            // sprawdzamy czy y%2 == 1, jeśli tak to trzeba dodać x do wyniku
            output->reset('a');
            output->add('d');
            output->shift('g');
            output->add('a');
            output->sub('d');
            output->jzero(5);
            output->reset('a');
            output->add('c');
            output->add('e');
            output->swap('e');
            // x = x*2  y = y/2     jeśli y == 0 to kończymy, jak nie to jeszcze raz
            output->swap('d');
            output->shift('g');
            output->jzero(7);
            output->swap('d');
            output->reset('a');
            output->swap('c');
            output->shift('f');
            output->swap('c');
            output->jump(-18);
            output->swap('e');
            break;
        case Operations::DIVIDE:
        case Operations::MOD:
                // x/y:  
                //  'c'- dzielnik  'd'- dzielna  'e'- tempRes  'f' - result  'g'-flagaD  'h'-flagaC
                output->reset('g');
                output->reset('h');
                output->reset('f');
                output->reset('c');
                
                val2->load();
                output->jzero(85);
                output->jpos(5);
                output->inc('h');
                output->swap('c');
                output->reset('a');
                output->sub('c');
                output->swap('c');
                val1->load();
                output->sub('c');
                output->jneg(76);
                output->add('c');
                output->jzero(6);
                output->jpos(5);
                output->inc('g');
                output->swap('d');
                output->reset('a');
                output->sub('d');
                output->swap('d');
                output->reset('e'); // LOOP START
                output->reset('a');
                output->add('c');
                output->shift('e');
                output->sub('d');
                output->jpos(3);
                output->inc('e');
                output->jump(-6);
                output->dec('e');
                output->reset('a');
                output->add('c');
                output->shift('e');
                output->swap('b');
                output->swap('d');
                output->sub('b');
                output->sub('c');
                output->swap('b');
                output->reset('a');
                output->add('b');
                output->add('c');
                output->swap('d');
                output->reset('a');
                output->inc('a');
                output->shift('e');
                output->add('f');
                output->swap('f');
                output->swap('b');
                output->jneg(2);
                output->jump(-28);
                output->reset('a');
                output->add('g');      // dzielna ?
                output->jpos(15);
                output->reset('a');
                output->add('h');      // dzielnik ?
                output->jpos(2);
                output->jump(30);     // oba dodatnie 
                output->reset('a');       // dzielna dodatnia dzielnik ujemny
                output->add('d');
                output->jzero(4);
                output->sub('c');
                output->swap('d');
                output->inc('f');
                output->reset('a');
                output->sub('f');
                output->swap('f');
                output->jump(20);
                output->reset('a');
                output->add('h');      // dzielna ujemna dzielnik ?
                output->jpos(14);
                output->reset('a');           // dzielna ujemna dzielnik dodatni
                output->add('d');
                output->jzero(7);
                output->sub('c');
                output->swap('d');
                output->reset('a');
                output->sub('d');
                output->swap('d');
                output->inc('f');
                output->reset('a');
                output->sub('f');
                output->swap('f');
                output->jump(4);
                output->reset('a');               // obie ujemne
                output->sub('d');
                output->swap('d');

                if (type == Operations::DIVIDE)
                    output->swap('f');
                else
                    output->swap('d');      
                output->jump(7);

                output->swap('h');
                output->jzero(4);
                output->reset('a');
                output->sub('c');
                output->swap('c');
                if (type == Operations::DIVIDE){
                    output->reset('a');
                }
                else{               
                    output->swap('c');    
                }

            break;
        default:
            break;
    }
    
}