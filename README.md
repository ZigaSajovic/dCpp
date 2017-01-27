# dCpp
Automatic differentiation in C++; infinite differentiability of conditionals, loops, recursion and all things C++

###Abstract
We provide an illustrative implementation of an analytic, infinitely-differentiable machine, implementing infinitely-differentiable programming spaces and operators acting upon them, as constructed in the paper _[Operational calculus on programming spaces and generalized tensor networks](https://arxiv.org/abs/1610.07690)_. Implementation closely follows theorems and derivations of the paper, intended as an educational guide for those transitioning from automatic differentiation to this general theory.

The paper [Implementation of Operational calculus on programming spaces with Applications](https://arxiv.org/abs/1612.02731) accompaning the implementation is avaliable on arXiv .


The _[dCpp](https://github.com/ZigaSajovic/dCpp)_ project is constantly updated and optimized. This is the openSource version.

###Tutorial
As most programmers face the need of differentiability through machine learning, we use the concept of [logistic regression](https://en.wikipedia.org/wiki/Logistic_regression) with [softmax normalization](https://en.wikipedia.org/wiki/Softmax_function#Softmax_Normalization) as a vessel for this tutorial. We demostrate, how it is simply constructed using algorithmic control flow and reccursion, by employing _dCpp_.

First we include the necessities

```c++
#include <iostream>
#include <dCpp.h>
#include <vector>
```

We initialize a n-differentiable programming space (order is arbitrary here)

```c++
using namespace dCpp;
int n_differentiable=2;
initSpace(n_differentiable);
```

We will need the folowing functions
* [sigmoid(x)](https://en.wikipedia.org/wiki/Sigmoid_function)
* [softmax(vec)](https://en.wikipedia.org/wiki/Softmax_function)
* [dotProduct(vec1,vec2)](https://en.wikipedia.org/wiki/Dot_product)
* [matVecProduct(mat,vec)](https://en.wikipedia.org/wiki/Matrix_multiplication)

####Maps contained in the function algebra over var

By coding sigmoid(x), we will learn about creating differentiable maps, constructable using the differentiable programming space _dCpp_ and the algebra of the virtual memory _var_.
```c++
var sigmoidMap(const var&v){return 1/(1+exp(-1*v));};

```
We test it out and and compute it on a simple example.

```c++
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
```    
Accessing the derivatives is done by calling _d(var* w)_ function of the class _var_. It returns the derivative with respect to the variable _w_, as a _var_ variable.

```c++
//  df/dw_1
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
```

####Operator dTau

 Similarly, we could have used the operator [tau](include/tau.h) by coding , which allows one to create it's own elements of the differentiable programming space _dCpp_, returning a differentiable variable [var](/include/var.h). The operator [tau](include/tau.h) is initialized by a double-->double map representing the desired function, and a var-->var map representing its derivative. Lets take a closer look, by creating a differentiable map log:var-->var.
 
 ```c++
 //coding the derivative
 var log_primitive(const var&v){return 1/v;};
```
The map is created by providing the operator with the two maps
 ```c++
 //operator returning a differentiable map
tau log(std::log,log_primitive);
```
The map is now ready to use
 ```c++
 //  set variables
    var x(10);
    var y(20);
//  initialize x and y as a differentiable variables
    dCpp::init(x);
    dCpp::init(y);
 //  now we use log as a differentiable map
    var f=log(((x^2)-(y^0.23))^2.1);
```
Again, we display all first and second derivatives
 ```c++
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
```
####Integrating control structures

With _dTau_ explained, we turn to coding the softmax normalization, we reveal how analytic virtual machines fully integrate control structures. 

```c++
//simply code the map existing in the programming space dCpp
//and the belonging algebra
std::vector<var> softmax(const std::vector<var>& V){
    std::vector<var> out;
    var sum = 0.0;
    for(var v:V){
        sum+=exp(v);
    }
    for(var v:V){
        out.push_back(exp(v)/sum);
    }
    return out;
}

```
We test it, by inititalizing a four-differentiable programming space and displaying all derivatives.

```c++
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

```

####Integrating external libraries

Usage with external libraries written in generic paradigm is demonstrated on the example of [Eigen](http://eigen.tuxfamily.org/). 
We will code a perceptron with sigmoid activations, followed by softmax normalization. We will use dCpp provided mappings in the [dEigen](/include/dEigen.h) header.

```c++
#include <iostream>
#include <dCpp.h>
#include <dEigen.h>

using namespace std;
using namespace dCpp;

//create a softmax function
template <typename Derived>
void softmax(Eigen::MatrixBase<Derived>& matrix){
        //maps each element of the matrix by y=e^x;
        dCpp::map_by_element(matrix,&dCpp::exp);
        //sums the elements of the matrix using Eigens function
        var tmp=matrix.sum();
        //divides each element by the sum
        for (size_t i=0, nRows=matrix.rows(), nCols=matrix.cols(); i<nCols; ++i)
            for (size_t j=0; j<nRows; ++j)matrix(j,i)=matrix(j,i)/tmp;
}


void dEigenExample(){
    //    space is n-times differentiable
    int n=2;
    //    initialize the space
    dCpp::initSpace(n);
    //    Matrix holding the inputs (imgSizeX1 vector)
    const int inputSize=28;
    Eigen::Matrix<var,1,inputSize>input=Eigen::Matrix<var,1,inputSize>::Random(1,inputSize);
    dCpp::init(input);
    //    number of outputs of the layer
    const int outputSize=1;
    //    matrix of weights on the first level (imgSizeXnumOfOutOnFirstLevel)
    Eigen::Matrix<var,inputSize,outputSize>firstLayerVars=Eigen::Matrix<var,inputSize,outputSize>::Random(inputSize,outputSize);
    //    initializing weights
    dCpp::init(firstLayerVars);
    //    mapping of the first layer
    Eigen::Matrix<var,outputSize,1>firstLayerOutput=input*firstLayerVars;
    //    add bias
    Eigen::Matrix<var,outputSize,1>bias=Eigen::Matrix<var,outputSize,1>::Random(outputSize,1);
    //    initialize bias
    dCpp::init(bias);
    firstLayerOutput=bias+firstLayerOutput;
    //    apply sigmoid we coded earlier
    dCpp::map_by_element(firstLayerOutput,sigmoid);
    //    apply sofmax layer
    softmax(firstLayerOutput);
    //    display the first output layer and its (1-n)-th derivatives
    for (size_t i=0, nRows=firstLayerOutput.rows(), nCols=firstLayerOutput.cols(); i<nCols; ++i){
                for (size_t j=0; j<nRows; ++j) firstLayerOutput(j,i).print();
                cout<<endl;
    }
}
```

###Citation
If you use _[dCpp](https://github.com/ZigaSajovic/dCpp)_ in your work, please cite the following paper

>Žiga Sajovic: [Implementation of Operational calculus on programming spaces with Applications](https://arxiv.org/abs/1612.02731). arXiv e-prints arXiv:1612.0273 (2016)

A _BibTex_ snippet has been provided for your convenience

```
@article{
    Author = {Žiga Sajovic},
    Title = {Implementation of Operational calculus on programming spaces with Applications},
    journal = {arXiv e-prints},
    Year = 2016,
    volume = {arXiv:1612.0273},
    Eprint = {1612.02731},
    Eprinttype = {arXiv},
}
```    

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">dC++</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://si.linkedin.com/in/zigasajovic" property="cc:attributionName" rel="cc:attributionURL">Žiga Sajovic</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
