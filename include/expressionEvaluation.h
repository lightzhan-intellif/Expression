#ifndef _EXPRESSION_EVALUATION_
#define _EXPRESSION_EVALUATION_ 
#include "common.h"
#include "../include/sequentialStack.h"
#include "../include/check.h"
int infixToPostfix(char *infixExpression, char postfixExpression[]);
int computeValueFromPostfix(char *postfixExpression, double *value);
#endif 