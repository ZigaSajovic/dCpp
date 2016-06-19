#include <iostream>
#include <dC.h>

using namespace std;

void softmax(var *v, int n){
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


void example3(){
    int n=3;
    var a[n];
    //create initial vector
    for(int i=0;i<n;i++)a[i]=var(i+1);
    //initialize all elements
    for(int i=0;i<n;i++)dC::init(a[i]);
    //apply the function
    softmax(a,n);
    //display the image and the gradient
    for(int i=0;i<n;i++)dC::print(a[i]);
}


