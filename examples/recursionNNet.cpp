#include <iostream>
#include <dC.h>

using namespace std;

//y=e^x
double e(double x){
    return exp(x);;
}

//dy/dx=e^x
double de(double x){
    return exp(x);
}

//create a diferentiable mapping
tau eFun=tau(e,de);

void softmaxMapping(var *v, int n){
    var sum=var(0);
    for(int i=0;i<n;i++){
        v[i]=eFun(v[i]);
        sum+=v[i];
    }

    for(int i=0;i<n;i++) v[i]/=sum;
}


//dot product mapping
var dotProd(var *v1,var *v2, int n){
    var out=var(0);
    for(int i=0;i<n;i++)out+=v1[i]*v2[i];
    return out;
}
//computes M*x
void matVecProd(var *out,var mat[][2],var *vec, int size1,int size2){
    for(int i=0;i<size1;i++)out[i]=dotProd(mat[i],vec,size2);
}

//sigmoid map
void sigmoidMapping(var *v,int n){
    for(int i=0;i<n;i++)v[i]=1/(1+eFun(-v[i]));
}

void recursionNet(var *input, var layer1[2][2],var layer2[2][2],var *result, int depth){
    if(depth==0){
        for(int i=0;i<2;i++)result[i]=input[i];
        softmaxMapping(result,2);
    }
    else{
        var firstOut[2];
        //matrix vector multiplication
        matVecProd(firstOut,layer1,input,2,2);
        sigmoidMapping(firstOut,2);
        var secondOut[2];
        matVecProd(secondOut,layer2,firstOut,2,2);
        sigmoidMapping(secondOut,2);
        recursionNet(secondOut,layer1,layer2,result,depth-1);
    }
}

void example5(){
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


