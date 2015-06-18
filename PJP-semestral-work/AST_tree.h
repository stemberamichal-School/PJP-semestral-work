//
//  AST_tree.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 08/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__AST_tree__
#define __PJP_semestral_work__AST_tree__

#include <stdio.h>
#include "base_lexal.h"

class AST_node{
public:
    virtual void * translate_to_generic() = 0;
    static AST_node * parse_from_input(BaseLexal * lexan);
    
};

#endif /* defined(__PJP_semestral_work__AST_tree__) */
