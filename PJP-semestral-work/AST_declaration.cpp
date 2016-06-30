//
//  AST_declaration.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 09/06/16.
//  Copyright © 2016 Michal Štembera. All rights reserved.
//

#include "AST_declaration.h"
#include "error.h"

#pragma mark - AST_standard_type
AST_standard_type::AST_standard_type(LexSymbolType typeByLexSymbol){
    this->typeByLexSymbol = typeByLexSymbol;
}

void * AST_standard_type::translate_to_generic(){
    TODO_WORK
    return NULL;
}

#pragma mark - AST_array

AST_array::AST_array(AST_standard_type * type, int from, int to){
    this->standard_type = type;
    this->from = from;
    this->to = to;
}

AST_array::~AST_array(){
    delete standard_type;
}

void * AST_array::translate_to_generic(){
    TODO_WORK
    return NULL;
}

#pragma mark - AST_declaration

AST_declaration::AST_declaration(AST_type * type, const char * ident){
    this->type = type;
    this->iden = ident;
}

AST_declaration::~AST_declaration(){
    delete this->type;
    delete this->iden;
}

void * AST_declaration::translate_to_generic(){
    TODO_WORK
    return NULL;
}

#pragma mark - AST_const_declaration

AST_const_declaration::AST_const_declaration(char * ident, int value)
:AST_declaration(new AST_standard_type(kwINTEGER), ident){
    this->value = value;
}

AST_const_declaration::~AST_const_declaration(){
}

void * AST_const_declaration::translate_to_generic(){
    TODO_WORK
    return NULL;
}

#pragma mark - AST_variable

AST_variable::AST_variable(char * ident){
    this->ident = ident;
}

AST_variable::AST_variable(char * ident, int * index){
    this->ident = ident;
    this->index = index;
}
