//
//  AST_exprsession.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "AST_expression.h"
#include "error.h"

LexSymbolType LexicalSymbolTypeValues[] = {PLUS, MINUS, TIMES, DIVIDE, EQ, NEQ, LT, GT, LTE, GTE};

const int_undefined INT_UNDEFINED_TRUE {.undefined = true, .value = 0};
int_undefined INT_UNDEFINED_VALUE(int value)
{
    return int_undefined {.undefined = false, .value = value};
}

#pragma mark - AST_expression
AST_expression_type AST_expression::expression_type(){
    return AST_NONE;
}

void AST_expression::print(std::ostream& os){
    os << "(AST_expression)";
}

void AST_expression::print_operation(LexSymbolType operation, std::ostream& os){
    switch (operation) {
        case PLUS:
            os << "+";
            break;
        case MINUS:
            os << "-";
            break;
        case TIMES:
            os << "*";
            break;
        case DIVIDE:
            os << "/";
            break;
        default:
            TODO_WORK;
            break;
    }
}


#pragma mark - AST_binop

AST_binop::AST_binop(AST_expression * left_op, AST_expression * right_op, LexSymbolType operation){
    this->left_op = left_op;
    this->right_op = right_op;
    this->operation = operation;
}

AST_binop::~AST_binop(){
    delete this->left_op;
    delete this->right_op;
}

AST_expression_type AST_binop::expression_type(){
    return AST_BINARY_OP;
}

void * AST_binop::translate_to_generic(){
    TODO_WORK
    return NULL;
}

void AST_binop::print(std::ostream& os){
    os << "(";
    if(this->left_op)
        this->left_op->print(os);
    else
        os << "NULL";
    print_operation(this->operation, os);
    if(this->right_op)
        this->right_op->print(os);
    else
        os << "NULL";
    os << ")";
}

int_undefined AST_binop::value(){
    int_undefined left_value = this->left_op->value();
    int_undefined right_value = this->right_op->value();
    
    if(left_value.undefined || right_value.undefined)
        return INT_UNDEFINED_TRUE;
    
    switch (this->operation) {
        case PLUS:{
            return INT_UNDEFINED_VALUE(this->left_op->value().value + this->right_op->value().value);
        }
        case MINUS:{
            return INT_UNDEFINED_VALUE(this->left_op->value().value - this->right_op->value().value);
        }
        case TIMES:{
            return INT_UNDEFINED_VALUE(this->left_op->value().value * this->right_op->value().value);
        }
        case DIVIDE:{
            if(this->right_op->value().value == 0)
                return INT_UNDEFINED_TRUE;
            return INT_UNDEFINED_VALUE(this->left_op->value().value / this->right_op->value().value);
        }
        default:
            return INT_UNDEFINED_TRUE;
            break;
    }
}

#pragma mark - AST_unop

AST_unop::AST_unop(AST_expression * operand, LexSymbolType operation){
    this->operand = operand;
    this->operation = operation;
}

AST_unop::~AST_unop(){
    delete this->operand;
}

AST_expression_type AST_unop::expression_type(){
    return AST_UNARY_OP;
}

void * AST_unop::translate_to_generic(){
    TODO_WORK
    return NULL;
}

void AST_unop::print(std::ostream& os){
    os << "(";
    print_operation(this->operation, os);
    if(this->operand)
        this->operand->print(os);
    else
        os << "NULL";
    os << ")";
}

int_undefined AST_unop::value(){
    int_undefined val = this->operand->value();
    if(operation == MINUS){
        val.value = -val.value;
    }
    return val;
}


#pragma mark - AST_constant

AST_constant::AST_constant(int value_int){
    this->value_int = value_int;
}

AST_expression_type AST_constant::expression_type(){
    return AST_CONSTANT;
}

void * AST_constant::translate_to_generic(){
    TODO_WORK
    return this;
}

void AST_constant::print(std::ostream& os){
    os << "(CON:" << this->value_int << ")";
}

int_undefined AST_constant::value(){
    return INT_UNDEFINED_VALUE(this->value_int);
}


#pragma mark - AST_var

AST_var::AST_var(char * ident){
    this->ident = ident;
}
    
AST_var::AST_var(char * ident, AST_expression * index)
    :AST_var(ident){
    this->index = index;
}

AST_var::~AST_var(){
    delete this->ident;
}

void AST_var::print(std::ostream& os){
    os << "(VAR:" << this->ident << ")";
}

int_undefined AST_var::value(){
    return INT_UNDEFINED_TRUE;
}

void * AST_var::translate_to_generic(){
    TODO_WORK
    return NULL;
}

