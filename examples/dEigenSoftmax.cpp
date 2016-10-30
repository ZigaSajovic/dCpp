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
    int n=1;
    //    initialize the space
    dCpp::initSpace(n);
    //    Matrix holding the inputs (imgSizeX1 vector)
    const int inputSize=50;
    Eigen::Matrix<var,1,inputSize>input=Eigen::Matrix<var,1,inputSize>::Random(1,inputSize);
    dCpp::init(input);
    //    number of outputs of the layer
    const int outputSize=7;
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
    //    apply sofmax layer
    softmax(firstLayerOutput);
    //    display the first output layer and its (1-n)-th derivatives
    for (size_t i=0, nRows=firstLayerOutput.rows(), nCols=firstLayerOutput.cols(); i<nCols; ++i){
                for (size_t j=0; j<nRows; ++j) firstLayerOutput(j,i).print();
                cout<<endl;
    }
}
