#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

#include<dCpp.h>

using namespace dCpp;

//simply code the map existing in the programming space dCpp
//and the belonging algebra
var sigmoidMap(const var&v){return 1/(1+exp(-1*v));};

void mapsInAlgebra()
{
//  initiaize Virtual memory of fourth order
    initSpace(2);
//  set inputs
    double x=4;
    double y=2;
//  set weights
    var w_1(0.4);
    var w_2(0.6);
//  initialize weights as twice differentiable variables
    dCpp::init(w_1);
    dCpp::init(w_2);
//  now we use sigmoid map as a differentiable map
    var f=sigmoidMap(w_1*x+w_2*y);
//  df/dx
    std::cout<<"df/dw_1 = "<<f.d(&w_1).id<<std::endl;
//  df/dw_2
    std::cout<<"df/dw_2 = "<<f.d(&w_2).id<<std::endl;
//  df/dw_1dw_1
    std::cout<<"df/dw_1dw_1 = "<<f.d(&w_1).d(&w_1).id<<std::endl;
//  df/dw_1dw_2
    std::cout<<"df/dw_1dw_2 = "<<f.d(&w_1).d(&w_2).id<<std::endl;
//  df/dw_2dw_1
    std::cout<<"df/dw_2dw_1 = "<<f.d(&w_2).d(&w_1).id<<std::endl;
//  df/dw_2dw_2
    std::cout<<"df/dw_2dw_2 = "<<f.d(&w_2).d(&w_2).id<<std::endl;
}
