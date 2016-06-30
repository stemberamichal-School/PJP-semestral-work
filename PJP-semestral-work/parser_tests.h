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
void test_expression_parentheses();

void test_assign_statement();
void test_assign_statement_2();

void test_compound_statement();
void test_compound_statement_2();
void test_compound_statement_3();


void test_declaration();
void test_declaration_2();
void test_declaration_3();
void test_declaration_4();

void test_files();
void test_input_file(const char * filepath);

void test_program();

#endif /* defined(__PJP_semestral_work__parser_tests__) */
