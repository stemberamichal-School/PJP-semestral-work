//
//  error.cpp
//  PJP-semestral-work
//
//  Created by Michal Štembera on 08/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#include "error.h"
#include <stdlib.h>

void error(const char * text) {
    printf("\nERROR: %s\n", text);
    exit(1);
}
