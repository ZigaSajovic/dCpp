#include <iostream>
#include <dC.h>

using namespace std;

void softmaxMap(var *v, int n){
    //initialize the sum variable
    var sum=var(0);
    for(int i=0;i<n;i++){
        //map element by y=e^x
        v[i]=dC::exp(v[i]);
        //add to sum
        sum+=v[i];
    }
    //divide each element by the sum
    for(int i=0;i<n;i++) v[i]/=sum;
}

//dot product mapping
var dot(var *v1,var *v2, int n){
    var out=var(0);
    for(int i=0;i<n;i++)out+=v1[i]*v2[i];
    return out;
}
//computes M*x
void matMul(var *out,var mat[][2],var *vec, int size1,int size2){
    for(int i=0;i<size1;i++)out[i]=dot(mat[i],vec,size2);
}

//sigmoid map
void sigmoidMap(var *v,int n){
    for(int i=0;i<n;i++)v[i]=1/(1+dC::exp(-v[i]));
}

void example4(){
    int m=2;
    int n=2;
    var input[n];
    var firstMat[2][2];
    //create input vector
    for(int i=0;i<n;i++)input[i]=var(i+1);
    //create initial matrix for first layer
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)firstMat[i][j]=var((i+1)*(j+1));
    }
    //initialize all elements
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)dC::init(firstMat[i][j]);
    }
    //output of the first layer
    var firstOut[2];
    //matrix vector multiplication
    matMul(firstOut,firstMat,input,m,n);
    //apply the softmax function
    sigmoidMap(firstOut,m);
    //create inital matrix for second layer
    var secondMat[2][2];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)secondMat[i][j]=var((j+1)*(i+1));
    }
    //initialize all elements
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)dC::init(secondMat[i][j]);
    }
    //output of the second layer
    var secondOut[2];
    //matrix vector multiplication
    matMul(secondOut,secondMat,firstOut,m,n);
    //apply the softmax mapping
    softmaxMap(secondOut,m);
    //display the image and the gradient
    for(int i=0;i<m;i++)dC::print(secondOut[i]);
}
