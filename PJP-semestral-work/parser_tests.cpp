//
//  parser_tests.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 16/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "parser_tests.h"
#include "testing_lexal.h"
#include "lexical_analyzer.h"
#include "constants.h"
#include "lexical_symbol.h"
#include "parser.h"
#include "AST_expression.h"

#include <sstream>

#pragma mark - AST_expression

void test_expression_plus_minus_constants(){
    int symbols_size = 5;
    LexicalSymbol * symbols = (LexicalSymbol *) malloc(symbols_size * sizeof(LexicalSymbol));
    symbols[0] = LexicalSymbol(4);
    symbols[1] = LexicalSymbol(PLUS);
    symbols[2] = LexicalSymbol(6);
    symbols[3] = LexicalSymbol(MINUS);
    symbols[4] = LexicalSymbol(7);
    TestingLexal * lexal = new TestingLexal(symbols, symbols_size);
    Parser * parser = new Parser(lexal);
    AST_expression * result_expr = parser->StartWithExpression();
    printf("%s\n", __PRETTY_FUNCTION__);
    printf("5 + 6 - 7\n");
    result_expr->print(std::cout);
    printf("\n");
    delete parser;
    delete lexal;
    delete result_expr;
}

void test_expression_plus_times_vars(){
    int symbols_size = 7;
    LexicalSymbol * symbols = (LexicalSymbol *) malloc(symbols_size * sizeof(LexicalSymbol));
    symbols[0] = LexicalSymbol("a");
    symbols[1] = LexicalSymbol(PLUS);
    symbols[2] = LexicalSymbol("b");
    symbols[3] = LexicalSymbol(TIMES);
    symbols[4] = LexicalSymbol("c");
    symbols[5] = LexicalSymbol(TIMES);
    symbols[6] = LexicalSymbol("d");
    TestingLexal * lexal = new TestingLexal(symbols, symbols_size);
    Parser * parser = new Parser(lexal);
    AST_expression * result_expr = parser->StartWithExpression();
    printf("%s\n", __PRETTY_FUNCTION__);
    printf("a + b * c * d\n");
    result_expr->print(std::cout);
    printf("\n");
    delete parser;
    delete lexal;
    delete result_expr;
}

void test_expression_plus_vars_unary_minus(){
    int symbols_size = 5;
    LexicalSymbol * symbols = (LexicalSymbol *) malloc(symbols_size * sizeof(LexicalSymbol));
    int i = 0;
    symbols[i++] = LexicalSymbol(MINUS);
    symbols[i++] = LexicalSymbol("a");
    symbols[i++] = LexicalSymbol(PLUS);
    symbols[i++] = LexicalSymbol(MINUS);
    symbols[i++] = LexicalSymbol("b");
    TestingLexal * lexal = new TestingLexal(symbols, symbols_size);
    Parser * parser = new Parser(lexal);
    AST_expression * result_expr = parser->StartWithExpression();
    printf("%s\n", __PRETTY_FUNCTION__);
    printf("- a + - b\n");
    result_expr->print(std::cout);
    printf("\n");
    delete parser;
    delete lexal;
    delete result_expr;
}

void test_expression_times_vars_unary_minus(){
    int symbols_size = 5;
    LexicalSymbol * symbols = (LexicalSymbol *) malloc(symbols_size * sizeof(LexicalSymbol));
    int i = 0;
    symbols[i++] = LexicalSymbol(MINUS);
    symbols[i++] = LexicalSymbol("a");
    symbols[i++] = LexicalSymbol(TIMES);
    symbols[i++] = LexicalSymbol(MINUS);
    symbols[i++] = LexicalSymbol("b");
    TestingLexal * lexal = new TestingLexal(symbols, symbols_size);
    Parser * parser = new Parser(lexal);
    AST_expression * result_expr = parser->StartWithExpression();
    printf("%s\n", __PRETTY_FUNCTION__);
    printf("- a * - b\n");
    result_expr->print(std::cout);
    printf("\n");
    delete parser;
    delete lexal;
    delete result_expr;
}


void test_expression_unary_complicated(){
    const char * expr_str = "-a + -b * -c * -d";
    std::istringstream * str_stream = new std::istringstream(expr_str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_expression * result_expr = parser->StartWithExpression();
    printf("%s\n%s\n",__PRETTY_FUNCTION__, expr_str);
    result_expr->print(std::cout);
    printf("\n");
}
