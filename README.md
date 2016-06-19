# dCpp
differentiable C++; conditionals, loops, recursion and all things C++

###Abstract
Algorithms were defined as a non-Abelian subgroup (or more generally a submonoid) of operators acting on a virtual space. By defining a norm on this space, and the notion of a limit, we show the operators to be differentiable through τ − calculus developed by the author. Thus all techniques of Functional analysis may be applied to any algorithm. 

Library dC++ implements the theory of τ − calculus in a natural way, needing only replacement of the type double with a differentiable variable var. Thus all C++ written code is compliable with the library. dC++ supports all external C++ libraries written in generic programming paradigm.

This is the openSource version.

###Usage
As algorithms become differentiable, so does a whole new set of procedures. Algorithms involving solving equations, approximating models, SVD decomposition, etc. as one of their steps, Runge-Kutta and other approximation methods, all become differentiable and can be subjected to standard methods of Functional analysis, thus providing exact solutions to analyticaly non-computable expressions.

###Tutorial
As most programmers face the need of differentiability through machine learning, we use the concept of a recursive neural network as a vessel for this tutorial.

We will create a simple 2-layer deep Neural Network with 5 recursive layers. 10 layers all together. Each layer will have sigmoid activation functions, ending with a softmax layer, producing a distribution. We will code all the functions as we go (even though much of such functionality comes with the library), for educational purposes.

First we include the necessities

```c++
#include <iostream>
#include <dC.h>
```
We will need the folowing functions
* e(x)
* sigmoid(x)
* softmax(vec)
* dotProduct(vec1,vec2)
* matVecProduct(mat,vec)

By coding e(x), we will learn about the class tau, which allows one to create it's own differentiable maps, returning a differentiable variable var.
First we create maps double->double, for e(x) and its' derivative.
```c++
//y=e^x
double eMap(double x){
    return std::exp(x);;
}

//dy/dx=e^x
double deMap(double x){
    return std::exp(x);
}
```
We create a differentiable map e(x), by providing tau with the above functions.
```c++
//create a differentiable mapping
tau e=tau(eMap,deMap);
```
Using this, we may code the sigmoid map.
```c++
//sigmoid map
void sigmoid(var *v,int n){
    for(int i=0;i<n;i++)v[i]=1/(1+e(-v[i]));
}
```
Now the softmax map.
```c++
void softmax(var *v, int n){
    var sum=var(0);
    for(int i=0;i<n;i++){
        v[i]=e(v[i]);
        sum+=v[i];
    }
    for(int i=0;i<n;i++) v[i]/=sum;
}
```
Next, we code the dot product and the matrix vector multiplication. For simplicity dimensions are specific to the example.
```c++
//dot product mapping
var dotProduct(var *v1,var *v2, int n){
    var out=var(0);
    for(int i=0;i<n;i++)out+=v1[i]*v2[i];
    return out;
}
//computes M*x
void matVecProduct(var *out,var mat[][2],var *vec, int size1,int size2){
    for(int i=0;i<size1;i++)out[i]=dotProd(mat[i],vec,size2);
}
```
We have all the tools needed to build a recursive layer. It will consist of two layers, mapping a 2-vector to a 2-vector. Output of the second layer will be recursively connected to the input of the next recursive layer.

```c++
void recursionNet(var *input, var layer1[2][2],var layer2[2][2],var *result, int depth){
    if(depth==0){
        for(int i=0;i<2;i++)result[i]=input[i];
        softmax(result,2);
    }
    else{
        var firstOut[2];
        //matrix vector multiplication
        matVecProduct(firstOut,layer1,input,2,2);
        sigmoid(firstOut,2);
        var secondOut[2];
        matVecProduct(secondOut,layer2,firstOut,2,2);
        sigmoid(secondOut,2);
        recursionNet(secondOut,layer1,layer2,result,depth-1);
    }
}
```
All that is left, is the main function in which we will learn about the initialization of differentiable variables. Note, how we do not initialize the input vector, but we do initialize the weight matricies, as only their derivatives are of interest.
Finally, we call recursionNet, for a depth of 10 layers and display its' gradient and image.
```c++
int main(){
    //create input vector
    var input[2];
    for(int i=0;i<2;i++)input[i]=var(i+1);
    //create initial matrix
    var firstMat[2][2];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)firstMat[i][j]=var((i+1)*(j+1));
    }
    //initialize all elements
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)dC::init(firstMat[i][j]);
    }
    //create inital matrix for second layer
    var secondMat[2][2];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)secondMat[i][j]=var((j+1)*(i+1));
    }
    //initialize all elements
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)dC::init(secondMat[i][j]);
    }
    var out[2];
    //run for 10 recursive steps
    recursionNet(input,firstMat,secondMat,out,10);
    //display the image and the gradient
    for(int i=0;i<2;i++)dC::print(out[i]);
}
```

###External libraries

Usage with external libraries written in generic paradigm is demonstrated on the example of [Eigen](http://eigen.tuxfamily.org/). 
We will code a perceptron with sigmoid activations, following by softmax normalization, taking 24x24 image as an input and outputting a 10 class classifier. We will use dC++ provided mappings.

```c++
#include <iostream>
#include <dC.h>

using namespace std;
using namespace dC;

//create a softmax function
template <typename Derived>
    void softmax(Eigen::MatrixBase<Derived>& matrix){
            //maps each element of the matrix by y=e^x;
            dC::map_by_element(matrix,&dC::exp);
            //sums the elements of the matrix using Eigens function
            var tmp=matrix.sum();
            //divides each element by the sum
            for (size_t i=0, nRows=matrix.rows(), nCols=matrix.cols(); i<nCols; ++i)
                for (size_t j=0; j<nRows; ++j)matrix(j,i)/=tmp;
}

int main(){
    //    Matrix holding the inputs (imgSizeX1 vector)
    const int imgSize=28*28;
    const Eigen::Matrix<var,1,imgSize>input=Eigen::Matrix<var,1,imgSize>::Random(1,imgSize);
    //    number of outputs of the layer
    const int numOfOutOnFirstLevel=1;
    //    matrix of weights on the first level (imgSizeXnumOfOutOnFirstLevel)
    Eigen::Matrix<var,imgSize,numOfOutOnFirstLevel>firstLayerVars=Eigen::Matrix<var,imgSize,numOfOutOnFirstLevel>::Random(imgSize,numOfOutOnFirstLevel);
    //    initializing weights
    dC::init(firstLayerVars);
    //    mapping of the first layer --> resulting in 10x1 vector
    Eigen::Matrix<var,numOfOutOnFirstLevel,1>firstLayerOutput=input*firstLayerVars;
    //    apply reLu layer --> resulting in 10x1 vector
    dC::map_by_element(firstLayerOutput,&dC::sigmoid);
    //    apply sofmax layer --> resulting in 10x1 vector
    softmax(firstLayerOutput);
    //    display the first output layer and its Jaccobian
    //    Jacobian is a 10x7840 matrix of derivatives
    for (size_t i=0, nRows=firstLayerOutput.rows(), nCols=firstLayerOutput.cols(); i<nCols; ++i){
                for (size_t j=0; j<nRows; ++j) dC::print(firstLayerOutput(j,i));
                cout<<endl;
    }
}

```
