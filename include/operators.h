#ifndef OPERATORS_H
#define OPERATORS_H

#include "tau.h"

namespace dCpp
{
var operator * (double n, const var& v);
var operator * (double n, var&& v);
var operator + (double n, const var& v);
var operator + (double n, var&& v);
var operator - (double n, const var& v);
var operator - (double n, var&& v);
var operator / (double n, const var& v);
var operator / (double n, var&& v);
var operator ^ (double n, const var& v);
}

#endif // OPERATORS_H
