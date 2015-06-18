//
//  main.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 26/05/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "lexical_analyzer.h"
#include "parser_tests.h"

int main(int argc, const char * argv[]) {
    
    const char * filename = "/Users/Michal/Dropbox/My_CVUT/6_semestr/BI-PJP/PJP-semestral-work/PJP-semestral-work/arrayAverage.p";
    std::ifstream * fstream = new std::ifstream(filename);
    LexicalAnalyzer lexer(*fstream);
    LexicalSymbol symbol;
    while ((symbol = lexer.readLexem()).type != EOI ) {
        std::cout << symbol << " ";
    }
    delete fstream;
    
    //test expresions
    test_expression_plus_minus_constants();
    test_expression_plus_times_vars();
    test_expression_plus_vars_unary_minus();
    test_expression_times_vars_unary_minus();
    test_expression_unary_complicated();
    return 0;
}
