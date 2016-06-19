#include <math.h>
#include "var.h"
#include <util.h>
#include <map>
#include <iostream>

using namespace std;

var::var(){real=0;dual=new std::map<int,double>;}

var::~var(){delete dual;}

var::var(double n){real=n;dual=new std::map<int,double>;}

var::var(const var& other) {
    this->dual = new map<int, double>;
    dual->insert(other.dual->begin(), other.dual->end());
    this->real = other.real;
}

var var::operator*(double n)const{
            var out;
            out.real=this->real*n;
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<pair<int,double> >, n);
            return out;
}

var var::operator+(double n)const{
            var out;
            out.real=this->real+n;
            out.dual->insert(this->dual->begin(),this->dual->end());
            return out;
}

var var::operator-(double n)const{
            var out;
            out.real=this->real-n;
            out.dual->insert(this->dual->begin(),this->dual->end());
            return out;
}

var var::operator/(double n)const{
            var out;
            out.real=this->real/n;
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<pair<int,double> >, 1/n);
            return out;
}

var var::operator*(const var& v)const{
            var out;
            out.real=this->real*v.real;
            map<int,double> tmp1;
            map<int,double> tmp2;
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(tmp1,tmp1.begin()),mul_make_pair<pair<int,double> >, v.real);
            for_each_copy(v.dual->begin(),v.dual->end(),inserter(tmp2,tmp2.begin()),mul_make_pair<pair<int,double> >, this->real);
            merge_apply(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), inserter(*out.dual, out.dual->begin()),
            compare_first<pair<int, double> >, sum_pairs<pair<int, double> >);
            return out;
}

var var::operator/(const var& v)const{
            return *this*(v^-1);
}

var var::operator+(const var& v)const{
            var out;
            out.real=this->real+v.real;
            merge_apply(this->dual->begin(), this->dual->end(), v.dual->begin(), v.dual->end(), inserter(*out.dual, out.dual->begin()),
            compare_first<pair<int, double> >, sum_pairs<pair<int, double> >);
            return out;
}

var var::operator-(const var& v)const{
            return *this+(-v);
}

var var::operator^(double n) const{
            var out;
            out.real=std::pow(this->real,n);
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(*(out.dual),out.dual->begin()),powTimes<pair<int,double> >, this->real,n-1);
            return out;
}

var var::operator-()const{
            var out;
            out.real=-this->real;
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(*(out.dual),out.dual->begin()),mul_make_pair<pair<int,double> >, -1);
            return out;
}

var& var::operator=(const var& v){
            if(this==&v)return *this;
            this->real=v.real;
            delete this->dual;
            this->dual=new map<int,double>;
            this->dual->insert(v.dual->begin(),v.dual->end());
            return *this;
}

var& var::operator=(double n){
            this->real=n;
            dual->clear();
            return *this;
}

var& var::operator+=(const var& v){
            this->real+=v.real;
            map<int,double>* newDual= new map<int,double>;
            merge_apply(v.dual->begin(), v.dual->end(), this->dual->begin(), this->dual->end(), inserter(*newDual, newDual->begin()),
            compare_first<pair<int, double> >, sum_pairs<pair<int, double> >);
            delete this->dual;
            this->dual=newDual;
            return *this;
}

var& var::operator-=(const var& v){
            this->real-=v.real;
            map<int,double>* newDual= new map<int,double>;
            merge_apply(v.dual->begin(), v.dual->end(), this->dual->begin(), this->dual->end(), inserter(*newDual, newDual->begin()),
            compare_first<pair<int, double> >, sub_pairs<pair<int, double> >);
            delete this->dual;
            this->dual=newDual;
            return *this;
}

var& var::operator*=(double n){
            this->real*=n;
            map<int,double>* newDual= new map<int,double>;
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(*(newDual),newDual->begin()),mul_make_pair<pair<int,double> >, n);
            delete this->dual;
            this->dual=newDual;
            return *this;
}

var& var::operator/=(double n){
            this->real/=n;
            map<int,double>* newDual= new map<int,double>;
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(*(newDual),newDual->begin()),mul_make_pair<pair<int,double> >, 1/n);
            delete this->dual;
            this->dual=newDual;
            return *this;
}

var& var::operator+=(double n){
            this->real+=n;
            return *this;
}

var& var::operator-=(double n){
            this->real-=n;
            return *this;
}

var& var::operator*=(const var& v){
            map<int,double> tmp1;
            map<int,double> tmp2;
            for_each_copy(this->dual->begin(),this->dual->end(),inserter(tmp1,tmp1.begin()),mul_make_pair<pair<int,double> >, v.real);
            for_each_copy(v.dual->begin(),v.dual->end(),inserter(tmp2,tmp2.begin()),mul_make_pair<pair<int,double> >, this->real);
            map<int,double>* newDual=new map<int,double>;
            delete this->dual;
            merge_apply(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), inserter(*newDual, newDual->begin()),
            compare_first<pair<int, double> >, sum_pairs<pair<int, double> >);
            this->real=this->real*v.real;
            this->dual=newDual;
            return *this;
}

var& var::operator/=(const var& v){
    return *this*=(v^-1);
}
