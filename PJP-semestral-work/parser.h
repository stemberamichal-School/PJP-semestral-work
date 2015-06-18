//
//  parser.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__parser__
#define __PJP_semestral_work__parser__

#include <stdio.h>
#include "lexical_symbol.h"
#include "constants.h"


class BaseLexal;
class AST_expression;
class AST_statement;

class Parser{
public:
    Parser(BaseLexal * lexal);
    AST_expression * StartWithExpression();
    
private:
    BaseLexal * lexal;
    LexicalSymbol currentSymbol;
    
    void Consumption(LexSymbolType symbol);
    
#pragma mark - Expression
    AST_expression * Expression();
    AST_expression * SimpleExpression();
    AST_expression * SimpleExpressionRR(); // right recursive
    AST_expression * Term();
    AST_expression * TermRR();              // right recursive
    AST_expression * Factor();
    
#pragma mark - Statement
    AST_statement * Statement();
    AST_statement * CompoundStatement();
    AST_statement * StatementList();
    AST_statement * AssignmentStatement();
    AST_statement * ProcedureCall();
    AST_statement * ForStatement();
    AST_statement * IfStatement();
    AST_statement * CaseStatement();
};

#endif /* defined(__PJP_semestral_work__parser__) */
