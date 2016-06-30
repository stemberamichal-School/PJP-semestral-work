//
//  AST_declaration.hpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 09/06/16.
//  Copyright © 2016 Michal Štembera. All rights reserved.
//

#ifndef AST_declaration_h
#define AST_declaration_h

#include <stdio.h>

#include "AST_tree.h"
#include "AST_expression.h"


#pragma mark - AST_type
class AST_type{
public:
    virtual ~AST_type(){};
};

#pragma mark - AST_standard_type
class AST_standard_type : public AST_type{
    LexSymbolType typeByLexSymbol;
public:
    AST_standard_type(LexSymbolType typeByLexSymbol);
    void * translate_to_generic();
};

#pragma mark - AST_array
class AST_array : public AST_type{
    AST_standard_type * standard_type;
    int from;
    int to;
public:
    AST_array(AST_standard_type * type, int from, int to);
    ~AST_array();
    void * translate_to_generic();
};

#pragma mark - AST_declaration
class AST_declaration : public AST_node{
    AST_type * type;
    const char * iden;
public:
    AST_declaration(AST_type * type, const char * ident);
    ~AST_declaration();
    void * translate_to_generic();
};

#pragma mark - AST_const_declaration
class AST_const_declaration : public AST_declaration{
    int value;
public:
    AST_const_declaration(char * ident, int value);
    ~AST_const_declaration();
    void * translate_to_generic();
};

#pragma mark - AST_variable
class AST_variable : public AST_node{
    char * ident;
    int  * index; // index is NULL if no index should be applied
public:
    AST_variable(char * ident);
    AST_variable(char * ident, int * index);
};
#endif /* AST_declaration_h */
