#include "var.h"
#include <math.h>
#include <util.h>
#include <map>
#include <memory>
#include <iostream>
#include <dCpp.h>


var:: var(){
    this->id=0;
    this->order=dCpp::getSpaceOrder();
    this->dTau=std::make_shared<std::map<var*, var> >();
};

var:: var(double id){
    this->order=dCpp::getSpaceOrder();
    this->id=id;
    this->dTau=std::make_shared<std::map<var*, var> >();
};

var::~var(){}

void var::init(int n){
    this->order=n;
    (*this->dTau.get())[this]=var(1);
    (*this->dTau.get())[this].order=n-1;
}

void var::initPlaceHolder(int order){
    this->order=order;
}

var var::d(var* dvar){
    try{
        return (*this->dTau.get()).at(dvar);
    }
    catch (const std::out_of_range& oor) {
        var out=0;
        out.order=0;
        return out;
    }

}

typedef std::map<var*,var>::iterator it_type;
void var::print()const{
    std::cout<<"id = "<<this->id<<" order = "<<this->order<<"\n";


for(it_type iterator = this->dTau.get()->begin(); iterator != this->dTau.get()->end(); iterator++) {
    std::cout<<"d/d("<<iterator->first<<") = "<<iterator->second.id<<"\n";
}

for(it_type iterator = this->dTau.get()->begin(); iterator != this->dTau.get()->end(); iterator++) {
    std::cout<<"d("<<iterator->first<<") ";
    iterator->second.print();
}
std::cout<<"\n";

}

var::var(const var& other) {
    this->order=other.order;
    this->dTau = std::make_shared<std::map<var*, var> >();
    this->id = other.id;
    this->dTau.get()->insert(other.dTau.get()->begin(),other.dTau.get()->end());
}

var::var(var&& other) = default;

var& var::operator=(const var& v){
    if(this==&v)return *this;
    this->order=v.order;
    this->id=v.id;
    this->dTau=std::make_shared<std::map<var*, var> >();
    this->dTau.get()->insert(v.dTau.get()->begin(),v.dTau.get()->end());
    return *this;
}

var var::reduce()const{
    var out(this->id);
    if(order>0){
        out.dTau=this->dTau;
        out.order=order-1;
    }
        return out;
}

//operations on doubles

var var::operator+(double n)const{
    var out;
    out.order=this->order;
    out.id=this->id+n;
    out.dTau.get()->insert(this->dTau.get()->begin(),this->dTau.get()->end());
    return out;
}

var var::operator-(double n)const{
    var out;
    out.order=this->order;
    out.id=this->id-n;
    out.dTau.get()->insert(this->dTau.get()->begin(),this->dTau.get()->end());
    return out;
}

var var::operator/(double n)const{
    var out;
    out.order=this->order;
    out.id=this->id/n;
    for_each_copy(this->dTau.get()->begin(),this->dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
        mul_make_pair<std::pair<var*,var> ,double >, 1/n);
    return out;
}

var var::operator*(double n)const{
    var out;
    out.id=this->id*n;
    out.order=this->order;
    for_each_copy(this->dTau.get()->begin(),this->dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
        mul_make_pair<std::pair<var*,var> , double>, n);
    return out;
}

var var::operator^(double n) const{
    var out;
    out.order=this->order;
    out.id=std::pow(this->id,n);
    if(n!=0&&this->order>0){
        for_each_copy(this->dTau.get()->begin(),this->dTau.get()->end(),inserter(*(out.dTau.get()),out.dTau.get()->begin()),
            mul_make_pair<std::pair<var*,var> , var>,((this->reduce())^(n-1))*=n);
    }
    return out;
}

var& var::operator+=(double n){
    this->id+=n;
    return *this;
}

var& var::operator-=(double n){
    this->id-=n;
    return *this;
}

var& var::operator*=(double n){
    this->id*=n;
    map_each(this->dTau.get()->begin(),this->dTau.get()->end(),inplace_mul<var, double >,n);
    return *this;
}

var& var::operator/=(double n){
    this->id/=n;
    map_each(this->dTau.get()->begin(),this->dTau.get()->end(),inplace_mul<var, double >,1/n);
    return *this;
}

var& var::operator^=(double n){
    if(n!=0&&this->order>0){
        map_each(this->dTau.get()->begin(),this->dTau.get()->end(),inplace_mul<var, var >,
            (this->reduce()^(n-1))*=n);
    }
    this->id=std::pow(this->id,n);
    return *this;
}

//binary operations on var

var var::operator+(const var& v)const{
    var out;
    out.id=this->id+v.id;
    out.order=this->order<v.order?this->order:v.order;
    if(out.order>0){
        merge_apply(this->dTau.get()->begin(), this->dTau.get()->end(), v.dTau.get()->begin(), v.dTau.get()->end(),
            inserter(*out.dTau.get(), out.dTau.get()->begin()),compare_first<std::pair<var*, var> >,
            sum_pairs<std::pair<var*, var> >);
    }
    return out;
}

var var::operator+(var&& v)const{return v+=*this;}

var var::operator-(const var& v)const{
    return *this+(v*(-1));
}

var var::operator-(var&& v)const{return (v*=(-1))+=*this;}

var var::operator*(const var& v)const{
    var out;
    out.id=this->id*v.id;
    out.order=this->order<v.order?this->order:v.order;
    if(out.order>0){
        std::map<var*,var> tmp1;
        std::map<var*,var> tmp2;
        for_each_copy(this->dTau.get()->begin(),this->dTau.get()->end(),inserter(tmp1,tmp1.begin()),
            mul_make_pair<std::pair<var*,var> ,var >, v.reduce());
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(tmp2,tmp2.begin()),
            mul_make_pair<std::pair<var*,var> ,var>, this->reduce());
        merge_apply(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), inserter(*out.dTau.get(),
            out.dTau.get()->begin()),compare_first<std::pair<var*, var> >, sum_pairs<std::pair<var*, var> >);
    }
    return out;
}

var var::operator*(var&& v)const{return v*=*this;}

var var::operator/(const var& v)const{
    return *this*(v^(-1));
}

var var::operator/(var&& v)const{return (v^=(-1))*=*this;}

var var::operator^(const var& v)const{
    var out;
    out.id=std::pow(this->id,v.id);
    out.order=this->order<v.order?this->order:v.order;
    if(out.order>0){
        std::map<var*,var> tmp1;
        std::map<var*,var> tmp2;
        for_each_copy(this->dTau.get()->begin(),this->dTau.get()->end(),inserter(tmp1,tmp1.begin()),
            mul_make_pair<std::pair<var*,var> ,var >, (this->reduce()^(v.reduce()-1))*=v.reduce());
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(tmp2,tmp2.begin()),
            mul_make_pair<std::pair<var*,var> ,var>, (this->reduce()^v.reduce())*=dCpp::ln(this->reduce()));
        merge_apply(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), inserter(*out.dTau.get(), out.dTau.get()->begin()),
            compare_first<std::pair<var*, var> >, sum_pairs<std::pair<var*, var> >);
    }
    return out;
}

var& var::operator+=(const var& v){

    this->order=this->order<v.order?this->order:v.order;
    if(this->order>0){
        inplace_merge_apply(this->dTau.get()->begin(), this->dTau.get()->end(), v.dTau.get()->begin(), v.dTau.get()->end(),
            inserter(*this->dTau.get(), this->dTau.get()->begin()),compare_first<std::pair<var*, var> >, inplace_sum<var, var>);
    }
    this->id+=v.id;
    return *this;
}

var& var::operator-=(const var& v){
    return ((*this*=-1)+=v)*=-1;
}

var& var::operator*=(const var& v){
    this->order=this->order<v.order?this->order:v.order;
    if(this->order>0){
        std::map<var*,var> tmp2;
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(tmp2,tmp2.begin()),
            mul_make_pair<std::pair<var*,var> ,var>, this->reduce());
        map_each(this->dTau.get()->begin(),this->dTau.get()->end(),inplace_mul<var, var >,v.reduce());
        inplace_merge_apply(this->dTau.get()->begin(), this->dTau.get()->end(), tmp2.begin(), tmp2.end(),
            inserter(*this->dTau.get(), this->dTau.get()->begin()),compare_first<std::pair<var*, var> >,
            inplace_sum<var, var>);
    }
    this->id*=v.id;
    return *this;
}

var& var::operator/=(const var& v){
    return *this*=(v^(-1));
}

var& var::operator^=(const var& v){
    this->order=this->order<v.order?this->order:v.order;
    if(this->order>0){
        std::map<var*,var> tmp2;
        for_each_copy(v.dTau.get()->begin(),v.dTau.get()->end(),inserter(tmp2,tmp2.begin()),
            mul_make_pair<std::pair<var*,var> ,var>,
            (this->reduce()^v.reduce())*=dCpp::ln(this->reduce()));
        map_each(this->dTau.get()->begin(),this->dTau.get()->end(),inplace_mul<var, var >,
            (this->reduce()^(v.reduce()-1)*=v.reduce()));
        inplace_merge_apply(this->dTau.get()->begin(), this->dTau.get()->end(), tmp2.begin(), tmp2.end(),
            inserter(*this->dTau.get(), this->dTau.get()->begin()),compare_first<std::pair<var*, var> >,
            inplace_sum<var, var>);
    }
    this->id=std::pow(this->id,v.id);
    return *this;
}

//order logic

bool var::operator==(const var& v)const{
    return this->id==v.id;
}

bool var::operator!=(const var& v)const{
    return this->id!=v.id;
}

bool var::operator<(const var& v)const{
    return this->id<v.id;
}

bool var::operator<=(const var& v)const{
    return this->id<=v.id;
}

bool var::operator>(const var& v)const{
    return this->id>v.id;
}

bool var::operator>=(const var& v)const{
    return this->id>=v.id;
}
