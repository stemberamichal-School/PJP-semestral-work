//
//  parser_tests.h
//  PJP-semestral-work
//
//  Created by Michal Štembera on 16/06/15.
//  Copyright (c) 2015 Michal Štembera. All rights reserved.
//

#ifndef __PJP_semestral_work__parser_tests__
#define __PJP_semestral_work__parser_tests__

#include <stdio.h>

#pragma mark - AST_expression
void test_expression_plus_minus_constants();
void test_expression_plus_times_vars();
void test_expression_plus_vars_unary_minus();
void test_expression_times_vars_unary_minus();
void test_expression_unary_complicated();

#endif /* defined(__PJP_semestral_work__parser_tests__) */
