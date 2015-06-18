//
//  testing_lexan.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__testing_lexan__
#define __PJP_semestral_work__testing_lexan__

#include <stdio.h>
#include "lexical_symbol.h"
#include "constants.h"
#include "base_lexal.h"

class TestingLexal : public BaseLexal{
public:
    TestingLexal(LexicalSymbol * symbols, int size);
    LexicalSymbol readLexem(void);
private:
    LexicalSymbol * symbols;
    int current_symbol;
    int symbols_count;
};

#endif /* defined(__PJP_semestral_work__testing_lexan__) */
