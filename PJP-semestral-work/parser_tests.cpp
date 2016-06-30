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
#include "AST_statement.h"
#include "AST_program.h"

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
    printf("4 + 6 - 7\n");
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
    const char * expr_str = "(-a + -b * -c * -48)";
    std::istringstream * str_stream = new std::istringstream(expr_str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_expression * result_expr = parser->StartWithExpression();
    printf("%s\n%s\n",__PRETTY_FUNCTION__, expr_str);
    result_expr->print(std::cout);
    printf("\n");
}


void test_expression_parentheses(){
    const char * expr_str = "-(a + b)*-b ----- c";
    std::istringstream * str_stream = new std::istringstream(expr_str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_expression * result_expr = parser->StartWithExpression();
    printf("%s\n%s\n",__PRETTY_FUNCTION__, expr_str);
    result_expr->print(std::cout);
    printf("\n");
}

void test_assign_statement(){
    const char * assign_str = "propertyA := -a";
    std::istringstream * str_stream = new std::istringstream(assign_str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_statement * assign_statement = parser->Statement();
    delete lexal;
    delete parser;
    delete assign_statement;
}


void test_assign_statement_2(){
    const char * assign_str = "propertyA := --5 + 27 / 3";
    std::istringstream * str_stream = new std::istringstream(assign_str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_statement * assign_statement = parser->Statement();
    delete lexal;
    delete parser;
    delete assign_statement;
}

void test_compound_statement(){
    const char * str = "begin end";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_statement * statement = parser->Statement();
    delete lexal;
    delete parser;
    delete statement;
}

void test_compound_statement_2(){
    const char * str = "begin a := 5; b := 27  ; c := 2*a+b end";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_statement * statement = parser->Statement();
    delete lexal;
    delete parser;
    delete statement;
}

void test_compound_statement_3(){
    const char * str = "begin a := 5; b := 27  ; c := 2*a+b; if a > 3 then begin a := 6; b := 7 + a; end; end";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_statement * statement = parser->Statement();
    delete lexal;
    delete parser;
    delete statement;
}

void test_declaration(){
    const char * str = "";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    vector<AST_declaration *> *declarations = new vector<AST_declaration *>;
    parser->Declarations(declarations);
    delete lexal;
    delete parser;
    delete declarations;
}

void test_declaration_2(){
    const char * str = "var a : integer;";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    vector<AST_declaration *> *declarations = new vector<AST_declaration *>;
    parser->Declarations(declarations);
    delete lexal;
    delete parser;
    delete declarations;
}

void test_declaration_3(){
    const char * str = "var a,b,c :integer; var i : integer; var ahoj : array [-5 .. 10] of integer;";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    vector<AST_declaration *> *declarations = new vector<AST_declaration *>;
    parser->Declarations(declarations);
    delete lexal;
    delete parser;
    delete declarations;
}

void test_declaration_4(){
    const char * str = "var a : array [0 .. 2] of integer;";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    vector<AST_declaration *> *declarations = new vector<AST_declaration *>;
    parser->Declarations(declarations);
    delete lexal;
    delete parser;
    delete declarations;
}

void test_program(){
    const char * str = "program arrayAverage;const a = 5; b = 7; c = 8; const z = -25; var I, TEMP, NUM, SUM : integer; var X : array [-20 .. 20] of integer; begin SUM := $10; end.";
    std::istringstream * str_stream = new std::istringstream(str);
    LexicalAnalyzer * lexal = new LexicalAnalyzer(*str_stream);
    Parser * parser = new Parser(lexal);
    AST_program * program = parser->Program();
    delete lexal;
    delete parser;
    delete program;
}

void test_files(){
    const char * filenames[5] = {
        "/Users/Michal/Dropbox/My_CVUT/6_semestr/BI-PJP/PJP-semestral-work/PJP-semestral-work/samples/arrayAverage.p",
        "/Users/Michal/Dropbox/My_CVUT/6_semestr/BI-PJP/PJP-semestral-work/PJP-semestral-work/samples/arrayMax.p",
        "/Users/Michal/Dropbox/My_CVUT/6_semestr/BI-PJP/PJP-semestral-work/PJP-semestral-work/samples/consts.p",
        "/Users/Michal/Dropbox/My_CVUT/6_semestr/BI-PJP/PJP-semestral-work/PJP-semestral-work/samples/expressions.p",
        "/Users/Michal/Dropbox/My_CVUT/6_semestr/BI-PJP/PJP-semestral-work/PJP-semestral-work/samples/expressions2.p",
    };
    for (int i = 0; i < sizeof(filenames)/sizeof(filenames[0]); i++) {
        const char * filename = filenames[i];
        cout << filename << endl;
        test_input_file(filename);
    };
    
}

void test_input_file(const char * filepath){
    std::ifstream file(filepath, std::ifstream::in);
    if(file.is_open()){
        std::stringstream str_stream;
        str_stream << file.rdbuf();
        file.close();
        LexicalAnalyzer * lexal = new LexicalAnalyzer(str_stream);
        Parser * parser = new Parser(lexal);
        AST_program * program = parser->Program();
        delete lexal;
        delete parser;
        delete program;
    }
}