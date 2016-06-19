#include <cmath>
#include "operators.h"
#include "var.h"
#include "util.h"

var operator*(double n, const var& v){
            return v*n;
}

var operator+(double n, const var& v){
            return v+n;
}

var operator-(double n, const var& v){
            return v-n;
}

var operator/(double n, const var& v){
            return (v^-1)*n;
}

var operator^(double n, const var& v){
            var out;
            out.real=std::pow(n,v.real);
            for_each_copy(v.dual->begin(),v.dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<std::pair<int,double> >, std::log(n)*out.real);
            return out;
}
