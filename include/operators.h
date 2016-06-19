#ifndef OPERATORS_H
#define OPERATORS_H

#include "var.h"

var operator * (double n, const var& v);
var operator + (double n, const var& v);
var operator - (double n, const var& v);
var operator / (double n, const var& v);
var operator ^ (double n, const var& v);


#endif // OPERATORS_H
