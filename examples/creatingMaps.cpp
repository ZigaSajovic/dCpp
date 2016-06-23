#include <iostream>
#include <dC.h>

using namespace std;

//create a simple mapping y=ln(x)
double naturalLog(double x){
    return std::log(x);
}

//create a mapping dy/dx=1/x;
double dNaturalLog(double x){
    return 1/x;
}

void example1(){
    //define a variable
    var x=var(3);
    //initialize x, as a differential variable
    dC:init(x);
    //create a differentiable map
    tau ln=tau(naturalLog, dNaturalLog);
    //map x
    var y=ln(x);
    //display the maps image and its gradient
    dC::print(y);
}
