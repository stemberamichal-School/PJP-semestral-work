//
//  AST_statement.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 18/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__AST_statement__
#define __PJP_semestral_work__AST_statement__

#include "AST_tree.h"
#include "constants.h"

#include <stdio.h>
#include <vector>

class AST_expression;
class AST_var;

#pragma mark - AST_statement
class AST_statement : public AST_node{
public:
    virtual ~AST_statement(){};
};

#pragma mark - AST_statement_list
class AST_statement_list : public AST_statement{
public:
    AST_statement_list(AST_statement * statement = NULL);
    ~AST_statement_list();
    void add_statement(AST_statement * statement);
    void add_statements(AST_statement_list * statement_list);
    void clear_list();
    void * translate_to_generic();
    
    //properties
private:
    std::vector<AST_statement *> statements;
};

#pragma mark - AST_compound
class AST_compound : public AST_statement{
public:
    AST_compound(AST_statement_list * statement_list = NULL);
    ~AST_compound();
    void * translate_to_generic();
    
    //properties
    AST_statement_list * statement_list;
};

#pragma mark - AST_assign
class AST_assign : public AST_statement{
public:
    AST_assign(AST_var * variable, int value = 0);
    AST_assign(AST_var * variable, AST_expression * to_assign);
    ~AST_assign();
    void * translate_to_generic();
    
    //properties
    AST_var * variable;
    AST_expression * to_assign;
};

#pragma mark - AST_if
class AST_if : public AST_statement{
public:
    AST_if(AST_expression * condition, AST_statement * if_block, AST_statement * else_block = NULL);
    ~AST_if();
    void * translate_to_generic();
    
    //properties
    AST_expression * condition;
    AST_statement  * if_block;
    AST_statement  * else_block;
};


#pragma mark - AST_while

class AST_while : public AST_statement{
    AST_expression * condition;
    AST_statement  * loop_content;
public:
    AST_while();
    AST_while(AST_expression * condition, AST_statement * loop_content);
    ~AST_while();
    void * translate_to_generic();
};


#pragma mark - AST_for

typedef enum{
    FOR_DIRECTION_TO,
    FOR_DIRECTION_DOWNTO
}AST_for_direction;

class AST_for : public AST_statement{
    AST_assign * assign;
    AST_expression * to;
    AST_statement  * loop_content;
    AST_for_direction direction;
public:
    AST_for(AST_assign * assign, AST_expression * to, AST_statement * loop_content, AST_for_direction direction);
    ~AST_for();
    void * translate_to_generic();
};



#endif /* defined(__PJP_semestral_work__AST_statement__) */
