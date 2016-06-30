//
//  parser.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "parser.h"
#include "AST_expression.h"
#include "AST_statement.h"
#include "error.h"
#include "lexical_symbol.h"
#include "constants.h"
#include "AST_program.h"
#include "AST_declaration.h"
#include "AST_procedure_call.h"

Parser::Parser(BaseLexal * lexal){
    this->lexal = lexal;
    this->currentSymbol = lexal->readLexem();
}

//Srovnani
void Parser::Consumption(LexSymbolType symbolType){
    if(currentSymbol.type == symbolType){
        currentSymbol = lexal->readLexem();
    }else{
        char buffer[256];
        const char * mess = "Consumption failed: ";
        const char * current = LexSymbolNames[currentSymbol.type];
        const char * instead = " instead of ";
        const char * expected = LexSymbolNames[symbolType];
        strncpy(buffer, mess, sizeof(buffer));
        strncat(buffer, current, sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, instead, sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, expected, sizeof(buffer) - strlen(buffer) - 1);
        error(buffer);
    }
}


#pragma mark - Program 

AST_program * Parser::Program(){
    vector<AST_declaration *> * declarations = new vector<AST_declaration *>();
    Consumption(kwPROGRAM);
    char * ident = (char *)malloc(strlen(currentSymbol.ident) + 1);
    strcpy(ident, currentSymbol.ident);
    Consumption(IDENT);
    Consumption(SEMICOLON);
    Consts(declarations);
    Declarations(declarations);
    AST_compound * compound = CompoundStatement();
    Consumption(DOT);
    AST_program * program = new AST_program(ident, declarations, compound);
    return program;
}

void Parser::Consts(vector<AST_declaration *> *declarations){
    while(currentSymbol.type == kwCONST){
        Consumption(kwCONST);
        AST_const_declaration * decl = NULL;
        
        while(currentSymbol.type == IDENT){
            decl = ConstDeclaration();
            declarations->push_back(decl);
            
            while (currentSymbol.type == COMMA) {
                Consumption(COMMA);
                decl = ConstDeclaration();
                declarations->push_back(decl);
            }
            Consumption(SEMICOLON);
        }
    }
}

AST_const_declaration * Parser::ConstDeclaration(){
    char * ident = currentSymbol.ident;
    Consumption(IDENT);
    Consumption(EQ);
    int number = Number();
    return new AST_const_declaration(ident, number);
}

void Parser::Declarations(vector<AST_declaration *> * declarations){
    while(currentSymbol.type == kwVAR){
        Consumption(kwVAR);
        while(currentSymbol.type == IDENT){
            vector<char *> * identifiers = new vector<char *>();
            IdentifierList(identifiers);
            Consumption(COLON);
            AST_type * type = Type();
            for (int i = 0; i < identifiers->size(); i++) {
                AST_declaration * declaration = new AST_declaration(type, (*identifiers)[i]);
                declarations->push_back(declaration);
            }
            Consumption(SEMICOLON);
            delete identifiers;
        }
    }
}

void Parser::IdentifierList(vector<char *> * identifiers){
    char * ident = (char *)malloc(MAX_IDENT_LEN);
    strncpy(ident, currentSymbol.ident, MAX_IDENT_LEN);
    identifiers->push_back(ident);
    Consumption(IDENT);
    if(currentSymbol.type == COMMA){
        Consumption(COMMA);
        IdentifierList(identifiers);
    }
}

AST_type * Parser::Type(){
    switch(currentSymbol.type){
        case kwARRAY:{
            Consumption(kwARRAY);
            Consumption(LBRACK);
            int from = Number();
            Consumption(DDOT);
            int to = Number();
            Consumption(RBRACK);
            Consumption(kwOF);
            AST_standard_type * st_type = StandardType();
            return new AST_array(st_type, from, to);
        }
        default:{
            return StandardType();
        }
    }
}

AST_standard_type * Parser::StandardType(){
    switch(currentSymbol.type){
        case kwINTEGER:{
            Consumption(kwINTEGER);
            return new AST_standard_type(kwINTEGER);
        }
        default:{
            error("Unknown data type");
            return NULL;
        }
    }
}


#pragma mark - Dimension
//AST_Dimension


#pragma mark - Expression

AST_expression * Parser::StartWithExpression(){
    return Expression();
}

AST_expression * Parser::Expression(){
    AST_expression * left_op = SimpleExpression();
    AST_expression * right_op = NULL;
    LexSymbolType operation = currentSymbol.type;
    switch(operation){
        case EQ:
        case NEQ:
        case GT:
        case GTE:
        case LT:
        case LTE:
            Consumption(operation);
            right_op = SimpleExpression();
            return new AST_binop(left_op, right_op, operation);
            break;
        default:
            return left_op;
            break;
    }
}

AST_expression * Parser::SimpleExpression(){
    AST_expression * left_op = Term();
    AST_binop * full_op = (AST_binop *)SimpleExpressionRR();
    if(full_op){
        full_op->left_op = left_op;
        return full_op;
    }else
        return left_op;
    return NULL;
}

AST_expression * Parser::SimpleExpressionRR(){
    LexSymbolType operation = currentSymbol.type;
    AST_expression * result = NULL;
    switch(operation){
        case PLUS:
        case MINUS:
        {
            //case OR:
            Consumption(operation);
            AST_expression * term_op = Term();
            AST_binop * simp_expr_op = (AST_binop *)SimpleExpressionRR();
            if(simp_expr_op && term_op){
                simp_expr_op->left_op = term_op;
                result =  new AST_binop(NULL, simp_expr_op, operation);
            }else if(simp_expr_op){
                result = new AST_binop(NULL, simp_expr_op, operation);
            }else if(term_op){
                result =  new AST_binop(NULL, term_op, operation);
            }else{
                result =  NULL;
            }
            break;
        }
        default:
        {
            result =  NULL;
            break;
        }
    }
    return result;
}

AST_expression * Parser::Term(){
    AST_expression * factor_op = Factor();
    AST_binop * term_rr_op = (AST_binop *)TermRR();
    if(term_rr_op){
        term_rr_op->left_op = factor_op;
        return term_rr_op;
    }else
        return factor_op;
    return NULL;
}

AST_expression * Parser::TermRR(){
    LexSymbolType operation = currentSymbol.type;
    AST_expression * result = NULL;
    switch(operation){
        case TIMES:
        case DIVIDE:
        case kwDIV:
        case kwMOD:
        {
            //case OR:
            Consumption(operation);
            AST_expression * factor_op = Factor();
            AST_binop * term_rr_op = (AST_binop *)TermRR();
            if(term_rr_op && factor_op){
                term_rr_op->left_op = factor_op;
                result =  new AST_binop(NULL, term_rr_op, operation);
            }else if(term_rr_op){
                result = new AST_binop(NULL, term_rr_op, operation);
            }else if(factor_op){
                result =  new AST_binop(NULL, factor_op, operation);
            }else{
                result =  NULL;
                error("TermRR: Operator has no right side.");
            }
            break;
        }
        default:{
            result =  NULL;
            break;
        }
    }
    return result;
}

AST_expression * Parser::Factor(){
    AST_expression * result = NULL;
    LexicalSymbol symbol = currentSymbol;
    switch (symbol.type) {
        case IDENT:
            result = Variable();
            break;
        case NUMBER:
            result = new AST_constant(symbol.number);
            Consumption(NUMBER);
            break;
        case LPAR:
            Consumption(LPAR);
            result = Expression();
            Consumption(RPAR);
            break;
        case MINUS:{
            Consumption(symbol.type);
            AST_expression * op = Factor();
            result = new AST_unop(op, symbol.type);
            break;
        }
        default:
            error("Factor: Unexpected lexical symbol.");
            break;
    }
    return result;
}

AST_var * Parser::Variable(){
    AST_expression * index = NULL;
    char * ident = (char *)malloc(MAX_IDENT_LEN);
    ident = strncpy(ident, currentSymbol.ident, MAX_IDENT_LEN);
    Consumption(IDENT);
    if(currentSymbol.type == LBRACK){
        Consumption(LBRACK);
        index = Expression();
        Consumption(RBRACK);
    }
    return new AST_var(ident, index);
}

int Parser::Number(){
    int multiplier = 1;
    int number = 0;
    if(currentSymbol.type == MINUS){
        Consumption(MINUS);
        multiplier = -1;
    }
    number = multiplier * currentSymbol.number;
    Consumption(NUMBER);
    return number;
}


#pragma mark - Statement

AST_statement * Parser::Statement(){
    AST_statement * result = NULL;
    switch(currentSymbol.type){
        case kwBEGIN:
            result = CompoundStatement();
            break;
        case kwIF:
            result = IfStatement();
            break;
        case kwFOR:
            result = ForStatement();
            break;
        /*case kwCASE:
            result = CaseStatement();
            break;*/
        case kwWHILE:
            result = WhileStatement();
            break;
        case IDENT:
            result = AssignmentStatement();
            break;
        case kwREADLN:
            result = ReadLN();
            break;
        case kwWRITELN:
            result = WriteLN();
            break;
        default:
            TODO_WORK
            result = NULL;
            break;
    }
    if(currentSymbol.type == SEMICOLON){
        Consumption(SEMICOLON);
    }
    return result;
}

AST_assign * Parser::AssignmentStatement(){
    AST_var * variable = Variable();
    Consumption(ASSIGN);
    AST_expression * expression = Expression();
    return new AST_assign(variable, expression);
}

AST_compound * Parser::CompoundStatement(){
    AST_statement_list * statement_list = NULL;
    Consumption(kwBEGIN);
    if(currentSymbol.type != kwEND){
        statement_list = StatementList();
    }
    Consumption(kwEND);
    return new AST_compound(statement_list);
}

AST_statement_list * Parser::StatementList(){
    AST_statement_list * result_list = new AST_statement_list();
    while(currentSymbol.type != kwEND){
        AST_statement * statement = Statement();
        result_list->add_statement(statement);
    }
    return result_list;
}

AST_statement_list * Parser::StatementListRR(){
    AST_statement_list * result_list = new AST_statement_list();
    while(currentSymbol.type != kwEND){
            AST_statement * statement     = Statement();
            result_list->add_statement(statement);
    }
    return result_list;
}

AST_if * Parser::IfStatement(){
    Consumption(kwIF);
    AST_expression * condition = Expression();
    Consumption(kwTHEN);
    AST_statement * if_statement = Statement();
    AST_statement * else_statement = NULL;
    if(currentSymbol.type == kwELSE){
        Consumption(kwELSE);
        else_statement = Statement();
    }
    
    return new AST_if(condition, if_statement, else_statement);
}

AST_while * Parser::WhileStatement(){
    AST_expression * condition = NULL;
    AST_compound * compound = NULL;
    
    Consumption(kwWHILE);
    condition = Expression();
    Consumption(kwDO);
    compound = CompoundStatement();
    
    return new AST_while(condition, compound);
}

AST_for * Parser::ForStatement(){
    AST_assign * assign = NULL;
    AST_expression * to   = 0;
    AST_compound * loop = NULL;
    AST_for_direction direction = FOR_DIRECTION_TO;
    
    Consumption(kwFOR);
    assign = AssignmentStatement();
    if(currentSymbol.type == kwTO){
        direction = FOR_DIRECTION_TO;
        Consumption(kwTO);
    }else{
        Consumption(kwDOWNTO);
        direction = FOR_DIRECTION_DOWNTO;
    }
    to = Expression();
    Consumption(kwDO);
    loop = CompoundStatement();
    
    return new AST_for(assign, to, loop, direction);
}


#pragma mark - IO

AST_readln * Parser::ReadLN(){
    vector<AST_expression *> * parameters = NULL;
    Consumption(kwREADLN);
    Consumption(LPAR);
    parameters = ParameterList();
    Consumption(RPAR);
    return new AST_readln(parameters);
    
}

AST_writeln * Parser::WriteLN(){
    vector<AST_expression *> * parameters = NULL;
    Consumption(kwWRITELN);
    Consumption(LPAR);
    parameters = ParameterList();
    Consumption(RPAR);
    return new AST_writeln(parameters);
}

vector<AST_expression *> * Parser::ParameterList(){
    vector<AST_expression *> * parameter_list = new vector<AST_expression *>();
    while(currentSymbol.type != RPAR){
        parameter_list->push_back(Expression());
        if(currentSymbol.type == COMMA)
            Consumption(COMMA);
        else
            break;
    }
    return parameter_list;
}

