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
#include <vector>
#include "lexical_symbol.h"
#include "constants.h"

using namespace std;

class BaseLexal;

class AST_expression;

class AST_statement;
class AST_compound;
class AST_loop;
class AST_if;
class AST_assign;
class AST_statement_list;
class AST_program;
class AST_declaration;
class AST_type;
class AST_standard_type;
class AST_while;
class AST_for;
class AST_const_declaration;
class AST_var;
class AST_procedure_call;
class AST_readln;
class AST_writeln;

class Parser{
public:
    Parser(BaseLexal * lexal);
    AST_expression * StartWithExpression();
    
private:
    BaseLexal * lexal;
    LexicalSymbol currentSymbol;
    
    void Consumption(LexSymbolType symbol);
    
public:
    
#pragma mark - Program 
    AST_program * Program();
    void Consts(vector<AST_declaration *> *declarations);
    AST_const_declaration * ConstDeclaration();
    void Declarations(vector<AST_declaration *> * declarations);
    void IdentifierList(vector<char *> * identifiers);
    AST_type * Type();
    AST_standard_type * StandardType();
    
#pragma mark - Expression
    AST_expression * Expression();
    AST_expression * SimpleExpression();
    AST_expression * SimpleExpressionRR(); // right recursive
    AST_expression * Term();
    AST_expression * TermRR();             // right recursive
    AST_expression * Factor();
    AST_var        * Variable();
    int              Number();
    
#pragma mark - Statement
    AST_statement       * Statement();
    AST_compound        * CompoundStatement();
    AST_statement_list  * StatementList();
    AST_statement_list  * StatementListRR();
    AST_statement       * AssignmentOrProcedureCall();
    AST_assign          * AssignmentStatement();
    AST_statement       * ProcedureCall(LexicalSymbol ident);
    AST_if              * IfStatement();
    AST_while           * WhileStatement();
    AST_for             * ForStatement();

#pragma mark - IO
    AST_readln  * ReadLN();
    AST_writeln * WriteLN();
    vector<AST_expression *> *  ParameterList();
};




#endif /* defined(__PJP_semestral_work__parser__) */
