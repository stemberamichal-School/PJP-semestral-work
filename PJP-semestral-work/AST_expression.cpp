//
//  AST_exprsession.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "AST_expression.h"
#include "error.h"

#pragma markk - AST_expression
AST_expression_type AST_expression::expressiont_type(){
    return AST_NONE;
}

void AST_expression::print(std::ostream& os){
    os << "{AST_expression}";
}

#pragma mark - AST_binop
LexSymbolType LexicalSymbolTypeValues[] = {PLUS, MINUS, TIMES, DIVIDE, EQ, NEQ, LT, GT, LTE, GTE};


AST_binop::AST_binop(AST_expression * left_op, AST_expression * right_op, LexSymbolType operation){
    this->left_op = left_op;
    this->right_op = right_op;
    this->operation = operation;
}

AST_binop::~AST_binop(){
    delete this->left_op;
    delete this->right_op;
}


AST_expression_type AST_binop::expressiont_type(){
    return AST_BINARY_OP;
}

void * AST_binop::translate_to_generic(){
    TODO_WORK
    return NULL;
}

void AST_binop::print(std::ostream& os){
    os << "{";
if(this->left_op) this->left_op->print(os);
    else              os << "NULL";
    os << this->operation;
    if(this->right_op) this->right_op->print(os);
    else               os << "NULL";
    os << "}";
}

#pragma mark - AST_unop

AST_unop::AST_unop(AST_expression * operand, LexSymbolType operation){
    this->operand = operand;
    this->operation = operation;
}

AST_unop::~AST_unop(){
    delete this->operand;
}

AST_expression_type AST_unop::expressiont_type(){
    return AST_UNARY_OP;
}

void * AST_unop::translate_to_generic(){
    TODO_WORK
    return NULL;
}

void AST_unop::print(std::ostream& os){
    os << "{";
    os << this->operation;
    if(this->operand) this->operand->print(os);
    else             os << "NULL";
    os << "}";
}


#pragma mark - AST_constant

AST_constant::AST_constant(int value_int){
    this->value_int = value_int;
}

AST_expression_type AST_constant::expressiont_type(){
    return AST_CONSTANT;
}

void * AST_constant::translate_to_generic(){
    TODO_WORK
    return this;
}

void AST_constant::print(std::ostream& os){
    os << "{";
    os << this->value_int;
    os << "}";
}

#pragma mark - AST_var

AST_var::AST_var(const char ident[]){
    strcpy(this->ident, ident);
}

AST_expression_type AST_var::expressiont_type(){
    return AST_VARIABLE;
}

void * AST_var::translate_to_generic(){
    TODO_WORK
    return this;
}

void AST_var::print(std::ostream& os){
    os << "{";
    os << this->ident;
    os << "}";
}