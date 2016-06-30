//
//  AST_procedure_call.hpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 27/06/16.
//  Copyright © 2016 Michal Štembera. All rights reserved.
//

#ifndef AST_procedure_call_h
#define AST_procedure_call_h

#include <stdio.h>
#include <vector>
#include "AST_statement.h"

using namespace std;

class AST_statement;


#pragma mark - AST_procedure_call

class AST_procedure_call : public AST_statement{
    char * ident;
    vector<AST_expression *> * parameter_list;
public:
    AST_procedure_call(char * ident, vector<AST_expression *> * parameters);
    ~AST_procedure_call();
};


#pragma mark - AST_readln

class AST_readln  : public AST_procedure_call{
public:
    AST_readln(vector<AST_expression *> * parameters);
    ~AST_readln();
    void * translate_to_generic();
};


#pragma mark - AST_writeln

class AST_writeln : public AST_procedure_call{
public:
    AST_writeln(vector<AST_expression *> * parameters);
    ~AST_writeln();
    void * translate_to_generic();
};



#endif /* AST_procedure_call_h */
