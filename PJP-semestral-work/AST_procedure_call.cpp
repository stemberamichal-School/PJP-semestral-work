//
//  AST_procedure_call.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 27/06/16.
//  Copyright © 2016 Michal Štembera. All rights reserved.
//

#include "AST_procedure_call.h"
#include "error.h"


#pragma mark - AST_procedure_call

AST_procedure_call::AST_procedure_call(char * ident, vector<AST_expression *> * parameters){
    this->ident = ident;
    this->parameter_list = parameters;
    
}

AST_procedure_call::~AST_procedure_call(){
    
}


#pragma mark - AST_readln

AST_readln::AST_readln(vector<AST_expression *> * parameters)
:AST_procedure_call(NULL, parameters){
    
}

AST_readln::~AST_readln(){
    
}

void * AST_readln::translate_to_generic(){
    TODO_WORK
    return NULL;
}



#pragma mark - AST_writeln

AST_writeln::AST_writeln(vector<AST_expression *> * parameters)
:AST_procedure_call(NULL, parameters){
    
}

AST_writeln::~AST_writeln(){

}

void * AST_writeln::translate_to_generic(){
    TODO_WORK
    return NULL;
}

