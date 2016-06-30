//
//  lexical_symbol.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 08/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__lexical_symbol__
#define __PJP_semestral_work__lexical_symbol__

#include "constants.h"
#include <stdio.h>
#include <iostream>

struct LexicalSymbol {
    LexSymbolType type;
    char      ident[MAX_IDENT_LEN];   /* atribut symbolu IDENT */
    int       number;                 /* atribut symbolu NUMB */
    
    LexicalSymbol();
    LexicalSymbol(LexSymbolType type);
    LexicalSymbol(const char ident[]);
    LexicalSymbol(int number);
    
    void appendCharToIdent(char character);
    void appendCharToDecimal(char character);
    void appendCharToOctal(char character);
    void appendCharToHexa(char character);
    LexicalSymbol & operator=(const LexicalSymbol & toCopy);
    friend std::ostream & operator << ( std::ostream & os, const LexicalSymbol & lexSymbol);
};
#endif /* defined(__PJP_semestral_work__lexical_symbol__) */
