//
//  error.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 08/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__error__
#define __PJP_semestral_work__error__

#include <stdio.h>

#define TODO_WORK printf("%s: not finoshed yet", __PRETTY_FUNCTION__);
void error(const char * text);

#endif /* defined(__PJP_semestral_work__error__) */
