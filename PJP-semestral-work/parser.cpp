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

Parser::Parser(BaseLexal * lexal){
    this->lexal = lexal;
    this->currentSymbol = lexal->readLexem();
}

//Srovnani
void Parser::Consumption(LexSymbolType symbolType){
    if(currentSymbol.type == symbolType){
        currentSymbol = lexal->readLexem();
    }else{
        error("Consumption failed: %i");
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
            result = new AST_var(currentSymbol.ident);
            Consumption(IDENT);
            break;
        case NUMBER:
            result = new AST_constant(symbol.number);
            Consumption(NUMBER);
            break;
        case LPAR:
            Consumption(LPAR);
            result = SimpleExpression();
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

#pragma mark - Statement
AST_statement * Parser::Statement(){
    switch(currentSymbol.type){
        case kwBEGIN:
    }
}
AST_statement * Parser::CompoundStatement(){
    TODO_WORK
    return NULL;
}
AST_statement * Parser::StatementList(){
    TODO_WORK
    return NULL;
}
AST_statement * Parser::AssignmentStatement(){
    TODO_WORK
    return NULL;
}
AST_statement * Parser::ProcedureCall(){
    TODO_WORK
    return NULL;
}
AST_statement * Parser::ForStatement(){
    TODO_WORK
    return NULL;
}
AST_statement * Parser::IfStatement(){
    TODO_WORK
    return NULL;
}
AST_statement * Parser::CaseStatement(){
    TODO_WORK
    return NULL;
}