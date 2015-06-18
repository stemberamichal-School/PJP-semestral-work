//
//  testing_lexan.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "testing_lexal.h"

TestingLexal::TestingLexal(LexicalSymbol * symbols, int size){
    this->symbols = symbols;
    this->symbols_count = size;
    this->current_symbol = 0;
}

LexicalSymbol TestingLexal::readLexem(void){
    if(current_symbol >= symbols_count){
        return LexicalSymbol(EOI);
    }
    return symbols[current_symbol++];
}