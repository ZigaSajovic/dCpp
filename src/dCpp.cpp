#include "dCpp.h"
#include <util.h>

namespace dCpp
{
int orderOfSpace=0;

void initSpace(int order)
{
    orderOfSpace=order;
}
int getSpaceOrder()
{
    return orderOfSpace;
}

void init(var &v)
{
    v.dTau.get()->clear();
    v.init(orderOfSpace);
}

var ln(const var& v)
{
    var out;
    out.id=std::log(v.id);
    out.order=v.order;
    if(v.order>0)
    {
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
                      mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator,var >, (v.reduce().to_lvalue())^(-1));
    }
    return out;
}

var cos(const var& v)
{
    var out;
    out.id=std::cos(v.id);
    out.order=v.order;
    if(v.order>0)
    {
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
                      mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator, var >, sin(v.reduce())*=-1);
    }
    return out;
}

var sin(const var& v)
{
    var out;
    out.id=std::sin(v.id);
    out.order=v.order;
    if(v.order>0)
    {
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
                      mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator, var >, cos(v.reduce()));
    }
    return out;
}

var tan(const var& v)
{
    return sin(v)/=cos(v);
}

var cot(const var& v)
{
    return cos(v)/=sin(v);
}

var log(double base, const var& v)
{
    return ln(v)/=std::log(base);
}

var exp(const var& v)
{
    var out;
    out.id=std::exp(v.id);
    out.order=v.order;
    if(v.order>0)
    {
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
                      mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator, var >, exp(v.reduce()));
    }
    return out;
}

var sqrt(const var& v)
{
    return v^0.5;
}

var sqrt(var&& v)
{
    return std::move(v^=0.5);
}
}
