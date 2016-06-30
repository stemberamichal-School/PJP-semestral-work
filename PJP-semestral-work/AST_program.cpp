//
//  AST_program.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 09/06/16.
//  Copyright © 2016 Michal Štembera. All rights reserved.
//

#include "AST_program.h"
#include "error.h"
#include "AST_statement.h"
#include "AST_declaration.h"

AST_program::AST_program(const char * iden, vector<AST_declaration *> * declarations, AST_compound * compound){
    this->declarations = declarations;
    this->compound = compound;
    this->iden = iden;
}

void * AST_program::translate_to_generic(){
    TODO_WORK
    return NULL;
}
