//
//  lexical_symbol.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 08/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "lexical_symbol.h"
#include "constants.h"
#include "error.h"

#pragma mark - LexicalSymbol

LexicalSymbol::LexicalSymbol(){
    this->type = UNKNOWN;
}

LexicalSymbol::LexicalSymbol(LexSymbolType type){
    this->type = type;
}

LexicalSymbol::LexicalSymbol(const char ident[]){
    this->type = IDENT;
    memcpy(this->ident, ident, MAX_IDENT_LEN);
}

LexicalSymbol::LexicalSymbol(int number){
    this->type = NUMBER;
    this->number = number;
}

void LexicalSymbol::appendCharToIdent(char character){
    size_t len = strlen(ident);
    if(len >= MAX_IDENT_LEN){
        error("Out of bounds of LexicalSymbol.ident array.");
    }
    ident[len++] = character;
    ident[len]   = '\0';
}

void LexicalSymbol::appendCharToNumber(char character){
    if(number >= (INT_MAX - 9) / 10){
        error("Number is too big. Would overflow.");
    }
    number = number * 10 + (character - '0');
}

LexicalSymbol & LexicalSymbol::operator=(const LexicalSymbol &toCopy){
    if (this != & toCopy) {
        this->type = toCopy.type;
        this->number = toCopy.number;
        memcpy(this->ident, toCopy.ident, MAX_IDENT_LEN);
    }
    return *this;
}

std::ostream & operator << ( std::ostream & os, const LexicalSymbol & lexSymbol){
    os << LexSymbolNames[lexSymbol.type];
    if(lexSymbol.type == IDENT)
        os << "(" << lexSymbol.ident << ")";
    return os;
}