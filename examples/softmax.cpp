#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>

#include<dCpp.h>

using namespace dCpp;

//simply code the map existing in the programming space dCpp
//and the belonging algebra
std::vector<var> softmax(const std::vector<var>& V){
    std::vector<var> out;
    var sum(0);
    init(sum);
    for(var v:V){
        sum=sum+exp(v);
    }
    for(var v:V){
        out.push_back(exp(v)/sum);
    }
    return out;
}

int main(){
//  initiaize Virtual memory of fourth order
    initSpace(4);
//get a vector of variables
    int size=2;
    std::vector<var> vars;
    for(int i=1;i<=size;i++){
        var tmp=var(i);
        init(tmp);
        vars.push_back(tmp);
    }
//  use the softmax function
    std::vector<var> f=softmax(vars);
//  display derivatives of all four orders
//   of one of the components
    f[1].print();
}
