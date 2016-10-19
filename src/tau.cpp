#include "tau.h"
#include <util.h>

namespace dCpp{
    tau::tau(mapping func, dTau primitive)
    {
        this->primitive=primitive;
        this->func=func;
    }

    tau::~tau(){}

    var tau::operator()(const var& v){
        var out;
        out.id=this->func(v.id);
        out.order=v.order;
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),mul_make_pair<std::pair<var*,var> , var >, this->primitive(v.reduce()));
        return out;
    }
}


