//
//  Constants.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 28/05/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef PJP_semestral_work_Constants_h
#define PJP_semestral_work_Constants_h

#include <string>
#include <map>

#define MAX_IDENT_LEN 32
typedef enum {
    TYPE_LETTER,
    TYPE_NUMBER,
    TYPE_WHITE_SPACE,
    TYPE_END,
    NO_TYPE
} CharType;

typedef enum {
    STATE_START,
    STATE_FINISHED,
    
    STATE_IDEN_KW,
    STATE_IDEN,
    STATE_NUMBER,
    STATE_LT,
    STATE_GT,
    STATE_DOT,
    STATE_COLON,
    STATE_COMMENT
} AutomatState;

typedef enum {
    UNKNOWN,
    IDENT, NUMBER, PLUS, MINUS, TIMES, DIVIDE,
    EQ, NEQ, LT, GT, LTE, GTE, LPAR, RPAR, LBRACK, RBRACK, ASSIGN,
    DOT, DDOT, COMMA, COLON, SEMICOLON,
    kwPROGRAM, kwINTEGER, kwDIV, kwDOWNTO, kwTO,
    kwVAR, kwCONST, kwBEGIN, kwEND, kwIF, kwTHEN, kwELSE, kwFOR,
    kwWHILE, kwDO, kwWRITE, kwREAD,
    EOI, ERR
} LexSymbolType;

static const char * LexSymbolNames[] = {
    "UNKNOWN",
    "IDENT", "NUMBER", "PLUS", "MINUS", "TIMES", "DIVIDE",
    "EQ", "NEQ", "LT", "GT", "LTE", "GTE", "LPAR", "RPAR", "LBRACK", "RBRACK", "ASSIGN",
    "DOT", "DDOT", "COMMA", "COLON", "SEMICOLON",
    "kwPROGRAM", "kwINTEGER", "kwDIV", "kwDOWNTO", "kwTO",
    "kwVAR", "kwCONST", "kwBEGIN", "kwEND", "kwIF", "kwTHEN", "kwELSE", "kwFOR",
    "kwWHILE", "kwDO", "kwWRITE", "kwREAD",
    "EOI", "ERR"
};

static std::map<std::string, LexSymbolType> & createKeywordLexSymbolMap(void){
    std::map<std::string, LexSymbolType>& map = *(new std::map<std::string, LexSymbolType>());
    map["var"]     = kwVAR;
    map["program"] = kwPROGRAM;
    map["integer"] = kwINTEGER;
    map["begin"]   = kwBEGIN;
    map["end"]     = kwEND;
    map["do"]      = kwDO;
    map["to"]      = kwTO;
    map["if"]      = kwIF;
    map["then"]    = kwTHEN;
    map["div"]     = kwDIV;
    map["downto"]  = kwDOWNTO;
    map["for"]     = kwFOR;
    return map;
}

static std::map<LexSymbolType, std::string> &  inversedKeywordLexSymbolMap(std::map<std::string, LexSymbolType> & keywordLexSymbolMap){
    std::map<LexSymbolType, std::string> & map = *(new std::map<LexSymbolType, std::string>());
    for (std::map<std::string,LexSymbolType>::iterator it = keywordLexSymbolMap.begin(); it != keywordLexSymbolMap.end(); it++) {
        map[(*it).second] = (*it).first;
    }
    return map;
}

static std::map<std::string, LexSymbolType> & KeywordLexSymbolMap = createKeywordLexSymbolMap();
static std::map<LexSymbolType, std::string> & LexSymbolKeywordMap = inversedKeywordLexSymbolMap(KeywordLexSymbolMap);

static size_t LexSymbolNamesSize = sizeof(LexSymbolNames) / sizeof(LexSymbolNames[0]);

#endif
