#ifndef _EXPRESSION_EVALUATION_
#define _EXPRESSION_EVALUATION_ 
#include "common.h"
#include "../include/sequentialStack.h"
#include "../include/check.h"
#include "../include/variableCollection.h"
#include "mystring.h"
int infixToPostfix(char *infixExpression, char postfixExpression[]);
int computeValueFromPostfix(char *postfixExpression, double *value);
void terminal_test();
#endif 