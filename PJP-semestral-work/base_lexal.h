//
//  base_lexan.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 15/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__base_lexal__
#define __PJP_semestral_work__base_lexal__

#include "lexical_symbol.h"
#include <stdio.h>

class BaseLexal{
public:
    virtual LexicalSymbol readLexem(void) = 0;
};

#endif /* defined(__PJP_semestral_work__base_lexal__) */
