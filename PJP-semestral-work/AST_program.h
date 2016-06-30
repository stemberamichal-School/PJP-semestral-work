//
//  AST_program.hpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 09/06/16.
//  Copyright © 2016 Michal Štembera. All rights reserved.
//

#ifndef AST_program_h
#define AST_program_h

#include <stdio.h>
#include <vector>
#include "AST_tree.h"
#include "AST_declaration.h"

using namespace std;

class AST_compound;

class AST_program : public AST_node{
    vector<AST_declaration *> * declarations;
    AST_compound * compound;
    const char * iden;
public:
    AST_program(const char * iden, vector<AST_declaration *> * declarations, AST_compound * compound);
    void * translate_to_generic();
};

#endif /* AST_program_h */
