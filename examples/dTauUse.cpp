#include <iostream>
#include <cmath>
#include<dCpp.h>


namespace dCpp
{
namespace examples
{

//create the derivative contained in dCpp
var log_primitive(const var&v)
{
    return 1/v;
};

void dTauOperatorUse()
{
//  initiaize Virtual memory of second order
    initSpace(2);
//  feed desired double-->double function
//  and its derivative var-->var to tau
    tau log_dCpp(std::log,log_primitive);
//  set variables
    var x(10);
    var y(20);
//  initialize x and y as a differentiable variables
    dCpp::init(x);
    dCpp::init(y);
//  now we use log_dCpp as a differentiable map
    var f=log_dCpp(((x^2)-(y^0.23))^2.1);
//  df/dx
    std::cout<<"df/dx = "<<f.d(&x).id<<std::endl;
//  df/dy
    std::cout<<"df/dy = "<<f.d(&y).id<<std::endl;
//  df/dxdx
    std::cout<<"df/dxdx = "<<f.d(&x).d(&x).id<<std::endl;
//  df/dxdy
    std::cout<<"df/dxdy = "<<f.d(&x).d(&y).id<<std::endl;
//  df/dydx
    std::cout<<"df/dydx = "<<f.d(&y).d(&x).id<<std::endl;
//  df/dydy
    std::cout<<"df/dydy = "<<f.d(&y).d(&y).id<<std::endl;
}
}
}
