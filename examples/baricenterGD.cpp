#include <vector>
#include <iostream>
#include <dCpp.h>

//gradient descent aimed at finding the baricenter

namespace dCpp
{
namespace examples
{

var energy(const std::vector<double> &pointsx,
           const std::vector<double> &pointsy,
           const var &x,
           const var &y)
{
    var sum=0.0;
    for (unsigned int i=0; i<pointsx.size(); ++i)
        sum += (pointsx[i] - x)* (pointsx[i] - x) + (pointsy[i] - y)* (pointsy[i] - y);

    return sum;
}

void baricenter()
{
    dCpp::initSpace(1);
    std::vector<double> px = {0.0, 1.0, 1.0, 0.0};
    std::vector<double> py = {0.0, 0.0, 1.0, 1.0};

    var x =50.1;
    var y = 50.1;
    dCpp::init(x);
    dCpp::init(y);

    double lambda=0.1;
    var e;
    double norm = 1.0;
    while (norm > 0.0000000001)
    {

        e = energy(px,py,x,y);
        x += -lambda*e.d(&x).id;
        y += -lambda*e.d(&y).id;

        norm = e.d(&x).id*e.d(&x).id+e.d(&y).id*e.d(&y).id;
    }

    std::cout<<"Minimum found at"<<std::endl;
    std::cout<<"x = "<<x<<std::endl;
    std::cout<<"y = "<<y<<std::endl;
}

}
}
