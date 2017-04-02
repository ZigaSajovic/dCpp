#include "dCpp.h"
#include <util.h>
#include <cmath>

int orderOfSpace=0;

void dCpp::initSpace(int order){orderOfSpace=order;}
int dCpp::getSpaceOrder(){return orderOfSpace;}


void dCpp::init(var &v){v.dTau.get()->clear();v.init(orderOfSpace);}

void dCpp::initPlaceHolder(var &v){v.dTau.get()->clear();v.initPlaceHolder(orderOfSpace);}

var dCpp::ln(const var& v){
    var out;
    out.id=std::log(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
            mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator,var >, (v.reduce().to_lvalue())^(-1));
    }
    return out;
}

var dCpp::cos(const var& v){
    var out;
    out.id=std::cos(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
            mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator, var >, dCpp::sin(v.reduce())*=-1);
    }
    return out;
}

var dCpp::sin(const var& v){
    var out;
    out.id=std::sin(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
            mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator, var >, dCpp::cos(v.reduce()));
    }
    return out;
}

var dCpp::tan(const var& v){
    return dCpp::sin(v)/=dCpp::cos(v);
}

var dCpp::cot(const var& v){
    return dCpp::cos(v)/=dCpp::sin(v);
}

var dCpp::log(double base, const var& v){
    return dCpp::ln(v)/=std::log(base);
}

var dCpp::exp(const var& v){
    var out;
    out.id=std::exp(v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
        mul_make_pair<std::pair<var*,var> , std::map<var*,var>::iterator, var >, dCpp::exp(v.reduce()));
    }
    return out;
}
