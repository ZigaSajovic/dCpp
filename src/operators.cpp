#include "operators.h"
#include "util.h"

var operator*(double n, const var& v){
            return v*n;
}

var operator+(double n, const var& v){
            return v+n;
}

var operator-(double n, const var& v){
            return (v-n)*=-1;
}

var operator/(double n, const var& v){
            return (v^-1)*=n;
}

var operator^(double n, const var& v){
    var out;
    out.id=std::pow(n,v.id);
    out.order=v.order;
    if(v.order>0){
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
            mul_make_pair<std::pair<var*,var> ,var >, (n^(v.reduce()))*=std::log(n));
    }
    return out;
}
