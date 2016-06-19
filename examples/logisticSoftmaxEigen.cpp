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

void example2(){
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
