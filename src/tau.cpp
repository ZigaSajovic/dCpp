#include "tau.h"
#include "var.h"
#include "util.h"

tau::tau(){}

tau::~tau(){}

tau::tau(funDouble f1, funDouble f2){mapping=f1; primitive=f2;}

var tau::operator()(const var&v){
    var out;
    out.real=mapping(v.real);
    for_each_copy(v.dual->begin(),v.dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<std::pair<int,double> >, primitive(v.real));
    return out;
}
