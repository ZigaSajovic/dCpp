#include "dCpp.h"
#include <util.h>
#include <cmath>

int orderOfSpace=1;

void dCpp::initSpace(int order){orderOfSpace=order;}

void dCpp::init(var &v){v.dTau.get()->clear();v.init(orderOfSpace);}

var dCpp::ln(const var& v){
    var out;
    out.id=std::log(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),mul_make_pair<std::pair<var*,var> ,var >, 1/v.reduce());
    }
    return out;
}

var dCpp::cos(const var& v){
    var out;
    out.id=std::cos(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),mul_make_pair<std::pair<var*,var> , var >, -1*dCpp::sin(v.reduce()));
    }
    return out;
}

var dCpp::sin(const var& v){
    var out;
    out.id=std::sin(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),mul_make_pair<std::pair<var*,var> , var >, dCpp::cos(v.reduce()));
    }
    return out;
}

var dCpp::tan(const var& v){
    return dCpp::sin(v.reduce())/dCpp::cos(v.reduce());
}

var dCpp::cot(const var& v){
    return dCpp::cos(v.reduce())/dCpp::sin(v.reduce());
}

var dCpp::log(double base, const var& v){
    return dCpp::ln(v.reduce())/std::log(base);
}

var dCpp::exp(const var& v){
    var out;
    out.id=std::exp(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),mul_make_pair<std::pair<var*,var> , var >, dCpp::exp(v.reduce()));
    }
    return out;
}
