#include "operators.h"
#include "util.h"

namespace dCpp
{
var operator*(double n, const var& v)
{
    return v*n;
}

var operator * (double n, var&& v)
{
    return std::move(v*=n);
}

var operator+(double n, const var& v)
{
    return v+n;
}

var operator + (double n, var&& v)
{
    return std::move(v+=n);
}

var operator-(double n, const var& v)
{
    return std::move((v-n)*=-1);
}

var operator-(double n, var&& v)
{
    return std::move((v-=n)*=-1);
}

var operator/(double n, const var& v)
{
    return std::move((v^-1)*=n);
}

var operator/(double n, var&& v)
{
    return std::move((v^=(-1))*=n);
}

var operator^(double n, const var& v)
{
    var out;
    out.id=std::pow(n,v.id);
    out.order=v.order;
    if(v.order>0)
    {
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
                      mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator,var >, (n^(v.reduce()))*=std::log(n));
    }
    return out;
}
}
