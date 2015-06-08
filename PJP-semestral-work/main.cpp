//
//  main.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 26/05/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include <iostream>
#include "lexical_analyzer.h"

int main(int argc, const char * argv[]) {
    
    const char * filename = "/Users/Michal/Dropbox/My_CVUT/6_semestr/BI-PJP/PJP-semestral-work/PJP-semestral-work/arrayAverage.p";
    LexicalAnalyzer lexer(filename);
    LexicalSymbol symbol;
    while ((symbol = lexer.readLexem()).type != EOI ) {
        std::cout << symbol << " ";
    }
    
    return 0;
}
