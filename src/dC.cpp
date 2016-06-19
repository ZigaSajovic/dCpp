#include "dC.h"
#include <cmath>
#include "var.h"
#include "operators.h"
#include "util.h"

int COUNT_OF_VARS=1;
std::map<const var*,int> varMap;


void dC::init(const var& v){v.dual->clear();varMap[&v]=COUNT_OF_VARS;(*v.dual)[COUNT_OF_VARS]=1;COUNT_OF_VARS++;}

var dC::cos(const var& v){
    var out;
    out.real=std::cos(v.real);
    for_each_copy(v.dual->begin(),v.dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<std::pair<int,double> >, -std::sin(v.real));
    return out;
}

var dC::sin(const var& v){
    var out;
    out.real=std::sin(v.real);
    for_each_copy(v.dual->begin(),v.dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<std::pair<int,double> >, std::cos(v.real));
    return out;
}

var dC::tan(const var& v){
    return dC::sin(v)/dC::cos(v);
}

var dC::cot(const var& v){
    return dC::cos(v)/dC::sin(v);
}

var dC::ln(const var& v){
    var out;
    out.real=std::log(v.real);
    for_each_copy(v.dual->begin(),v.dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<std::pair<int,double> >, 1/v.real);
    return out;
}

var dC::log(double base, const var& v){
    return dC::ln(v)/std::log(base);
}

var dC::exp(const var& v){
    var out;
    out.real=std::exp(v.real);
    for_each_copy(v.dual->begin(),v.dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<std::pair<int,double> >, out.real);
    return out;
}

var dC::sigmoid(const var& v){
    return 1/(1+dC::exp(-v));
}

var dC::reLu(const var& v){
    return (v.real>0)?v:0*v;
}

var dC::reLuLeak(const var& v, double leak){
    return (v.real>0)?v:leak*v;
}

void dC::print(const var& v){
    std::cout<<"Image -> "<<v.real<<std::endl<<"Differential:"<<std::endl;;
    for(std::map<int,double>::iterator i=v.dual->begin();i!=v.dual->end();i++){
        std::cout<<"d/dx_"<<i->first<<"  -->  "<<i->second<<" ";
    }
    std::cout<<std::endl;
}
