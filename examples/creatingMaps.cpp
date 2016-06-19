#include <iostream>
#include <dC.h>

using namespace std;

//create a simple mapping y=x^2
double square(double x){
    return x*x;
}

//create a mapping dy/dx=2*x;
double dSquare(double x){
    return x*2;
}

void example1(){
    //define a variable
    var x=var(3);
    //initialize x, as a differential variable
    dC:init(x);
    //create a differentiable map
    tau t=tau(square, dSquare);
    //map x
    var y=t(x);
    //display the maps image and its gradient
    dC::print(y);
}
