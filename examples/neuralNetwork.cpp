#include <iostream>
#include <matrix.h>

using namespace std;
using namespace dCpp;

void softmaxActivation(std::vector<var>& V){
    var sum(0);
    init(sum);
    for(var v:V){
        sum=sum+exp(v);
    }
    for(unsigned int i=0;i<V.size();i++){
        V[i]=(exp(V[i])/sum);
    }
}

void sigmoidActivation(std::vector<var>& V){
    for(unsigned int i=0;i<V.size();i++){
        V[i]=1/(1+exp(-1*V[i]));
    }
}

void idActivation(std::vector<var>& V){
}

typedef void (*activation)(vector<var>&);

class layer{
public:
    vector<vector<var> > weights;
    vector<var> bias;
    activation act;
    layer(int n, int m,activation a){
        weights=randMat(n,m);
        bias=randVec(n);
        act=a;
    }
    void init(){
        initMat(weights);
        initVec(bias);
    }
    template<class V>
    vector<var> eval(vector<V>&v){
        vector<var>out=prod(weights,v);
        sumInplace(out,bias);
        act(out);
        return out;
    }

    void update(var& dV, double stepSize){
        for(vector<var>&vec:weights){
            for(var &v:vec){
                v.id-=(dV.d(&v).id*stepSize);
            }
        }
        for(var &v:bias){
            v.id-=(dV.d(&v).id)*stepSize;
        }
    }
};

class net{
public:
    vector<layer> layers;
    bool softMax;
    net(bool softM=true){softMax=softM;}
    void add(int n, int m, activation a){
        layers.push_back(layer(n,m,a));
    }
    void init(){
        for(layer &l:layers)l.init();
    }
    template<class V>
    vector<var> eval(vector<V>input){
        vector<var> out;
        for(int i=0;i<layers.size();i++){
            if(i==0)out=layers[i].eval(input);
            else out=layers[i].eval(out);
        }
        if(softMax)softmaxActivation(out);
        return out;
    }

    void train(vector<vector<double> >& inputs, vector<vector<double> >& outputs, int steps, double stepSize, int printRate=100, bool print=true){
        for(int i=0;i<steps;i++){
            update(inputs,outputs,stepSize);
            if(print&&i%printRate==0)cout<<"Completed "<<i<<"-th step"<<endl;;
        }
    }

    void update(vector<vector<double> >& inputs, vector<vector<double> >& outputs, double stepSize){
        var sum=var(0);
        initPlaceHolder(sum);
        for(unsigned int i=0;i<inputs.size();i++){
            sum+=dist(outputs[i],eval(inputs[i]));
        }
        for(layer &l:layers)l.update(sum,stepSize);
    }
};

void nNetExample(){
    initSpace(1);
    net N=net(false);
    N.add(2,5,sigmoidActivation);
    N.add(2,2,sigmoidActivation);

    N.init();

    vector<vector<double>>inputs=randBatch(5,5);
    vector<vector<double>>outputs=randBatch(5,2);

    N.train(inputs,outputs,10000,0.1,1000);

    cout<<"Correct predictions:\n";
    for(vector<double>&vec:outputs){
        for(double d:vec)cout<<d<<", ";
        cout<<endl;
    }

    cout<<"Predictions:\n";
    for(vector<double>&vec:inputs){
        vector<var>tmp=N.eval(vec);
        for(var&v:tmp)cout<<v.id<<", ";
        cout<<endl;
    }
}
