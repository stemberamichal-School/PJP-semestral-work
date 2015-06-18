//
//  lexical_analyzer.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 26/05/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__lexical_analyzer__
#define __PJP_semestral_work__lexical_analyzer__

#include "constants.h"
#include "lexical_symbol.h"
#include "base_lexal.h"
#include <fstream>
#include <iostream>
#include <string>

class LexicalAnalyzer : public BaseLexal{
    char character;
    CharType characterType;
    AutomatState actualState;
    LexicalSymbol outputSymbol;
    std::istream & input_stream;
public:
    LexicalAnalyzer(std::istream & is);
    ~LexicalAnalyzer(void);
    LexicalSymbol readLexem(void);
private:
    void readInput(void);
    
    void checkIdentKeyword(void);
    
    void applyStateStart(void);
    void applyStateIdenKeyword(void);
    void applyStateIden(void);
    void applyStateNumber(void);
    void applyStateLT(void);
    void applyStateGT(void);
    void applyStateDot(void);
    void applyStateColon(void);
    void applyStateComment(void);
};


#endif /* defined(__PJP_semestral_work__lexical_analyzer__) */
