//
//  AST_exprsession.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__AST_exprsession__
#define __PJP_semestral_work__AST_exprsession__

#include <stdio.h>
#include "AST_tree.h"
#include "constants.h"

typedef enum {
    AST_NONE,
    AST_CONSTANT,
    AST_VARIABLE,
    AST_BINARY_OP,
    AST_UNARY_OP
} AST_expression_type;

#pragma mark - AST_expression
class AST_expression : public AST_node{
public:
    AST_expression_type expressiont_type();
    virtual ~AST_expression(){};
    virtual void print(std::ostream& os);
};


#pragma mark - AST_binop
class AST_binop : public AST_expression{
public:
    AST_binop(AST_expression * left_op, AST_expression * right_op, LexSymbolType operation);
    ~AST_binop();
    AST_expression_type expressiont_type();
    void * translate_to_generic();
    void print(std::ostream& os);
    
    //properties
    AST_expression * left_op;
    AST_expression * right_op;
    LexSymbolType operation;
};

#pragma mark - AST_unop
class AST_unop : public AST_expression{
public:
    AST_unop(AST_expression * operand, LexSymbolType operation);
    ~AST_unop();
    AST_expression_type expressiont_type();
    void * translate_to_generic();
    void print(std::ostream& os);
    
    //properties
    AST_expression * operand;
    LexSymbolType operation;
};


#pragma mark - AST_constant
class AST_constant : public AST_expression{
public:
    AST_constant(int value_int);
    ~AST_constant(){};
    AST_expression_type expressiont_type();
    void print(std::ostream& os);
    
    //properties
    void * translate_to_generic();
    int  value_int;
};

class AST_var : public AST_expression{
public:
    AST_var(const char ident [MAX_IDENT_LEN]);
    ~AST_var(){};
    AST_expression_type expressiont_type();
    void * translate_to_generic();
    void print(std::ostream& os);

    //properties
    char ident[MAX_IDENT_LEN];
};


#endif /* defined(__PJP_semestral_work__AST_exprsession__) */
