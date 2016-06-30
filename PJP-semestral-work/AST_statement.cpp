//
//  AST_statement.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 18/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "error.h"
#include "AST_statement.h"
#include "AST_expression.h"

#pragma mark - AST_statement_list
AST_statement_list::AST_statement_list(AST_statement * statement){
    this->add_statement(statement);
}

AST_statement_list::~AST_statement_list(){
    for (int i = 0; i < statements.size(); i++) {
        delete statements[i];
    }
}

void * AST_statement_list::translate_to_generic(){
    TODO_WORK
    return this;
}

void AST_statement_list::add_statement(AST_statement * statement){
    if(statement){
        statements.push_back(statement);
    }
}

void AST_statement_list::add_statements(AST_statement_list * statement_list){
    this->statements.insert(this->statements.end(), statement_list->statements.begin(), statement_list->statements.end());
}

void AST_statement_list::clear_list(){
    this->statements.clear();
}

#pragma mark - AST_compound

AST_compound::AST_compound(AST_statement_list * statement_list){
    this->statement_list = statement_list;
}

AST_compound::~AST_compound(){
    delete statement_list;
}

void * AST_compound::translate_to_generic(){
    TODO_WORK
    return this;
}

#pragma mark - AST_assign

AST_assign::AST_assign(AST_var * variable, int value){
    this->variable = variable;
    this->to_assign = new AST_constant(value);
}

AST_assign::AST_assign(AST_var * variable, AST_expression * to_assign){
    this->variable = variable;
    this->to_assign = to_assign;
}

AST_assign::~AST_assign(){
    delete variable;
    delete to_assign;
}

void * AST_assign::translate_to_generic(){
    TODO_WORK
    return this;
}


#pragma mark - AST_if

AST_if::AST_if(AST_expression * condition, AST_statement * if_block, AST_statement * else_block){
    this->condition = condition;
    this->if_block = if_block;
    this->else_block = else_block;
}
AST_if::~AST_if(){
    delete this->condition;
    delete this->if_block;
    delete this->else_block;
}

void * AST_if::translate_to_generic(){
    TODO_WORK
    return this;
}

#pragma mark - AST_while

AST_while::AST_while(){
    condition = NULL;
    loop_content = NULL;
}

AST_while::AST_while(AST_expression * condition, AST_statement * loop_content){
    this->condition = condition;
    this->loop_content = loop_content;
}

AST_while::~AST_while(){
    delete condition;
    delete loop_content;
}

void * AST_while::translate_to_generic(){
    TODO_WORK
    return NULL;
}


#pragma mark - AST_for

AST_for::AST_for(AST_assign * assign, AST_expression * to, AST_statement * loop_content, AST_for_direction direction){
    this->assign = assign;
    this->to = to;
    this-> loop_content = loop_content;
    this->direction = direction;
}

AST_for::~AST_for(){
    delete assign;
    delete loop_content;
}

void * AST_for::translate_to_generic(){
    TODO_WORK
    return NULL;
}




