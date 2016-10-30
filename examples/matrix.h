#include <iostream>
#include<cmath>
#include<dCpp.h>
#include<vector>
#include<random>

using namespace std;
using namespace dCpp;


template<class v1, class v2>
vector<var> prod(const vector<vector<v1>>&mat,const vector<v2>&vec){
    vector<var> out;
    for(unsigned int i=0;i<mat.size();i++){
        var sum(0);
        initPlaceHolder(sum);
        for(unsigned int j=0;j<vec.size();j++){
            sum+=mat[i][j]*vec[j];
        }
        out.push_back(sum);
    }
    return out;
}

vector<var> sum(const vector<var>&vec1,const vector<var>&vec){
    vector<var> out;
    for(unsigned int j=0;j<vec.size();j++){
        out.push_back(vec1[j]+vec[j]);
    }
    return out;
}

template<class V1,class V2>
var dist(const vector<V1>&vec1,const vector<V2>&vec){
    var out=var(0);
    initPlaceHolder(out);
    for(unsigned int j=0;j<vec.size();j++){
        out+=(vec1[j]-vec[j])^2;
    }
    return out;
}

void sumInplace(vector<var>&vec1,const vector<var>&vec){
    for(unsigned int j=0;j<vec.size();j++){
        vec1[j]+=vec[j];
    }
}

vector<vector<var> > randMat(unsigned int n, unsigned int m){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,1);
    vector<vector<var> > mat;
    for(unsigned int i=0;i<n;i++){
        vector<var> tmp;
        for(unsigned int j=0;j<m;j++){
            var x=var(dist6(rng));
            tmp.push_back(x);
        }
        mat.push_back(tmp);
    }
    return mat;
}

vector<var>randVec(unsigned int n){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,100);
    vector<var> out;
    for(unsigned int i=0;i<n;i++){
        var x=var(((double)dist6(rng))/100);
        init(x);
        out.push_back(x);

    }
    return out;
}

vector<double>randVecDouble(unsigned int n){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,100);
    vector<double> out;
    for(unsigned int i=0;i<n;i++){
        out.push_back(((double)dist6(rng))/100);
    }
    return out;
}

void initMat(vector<vector<var> >&mat){
    for(vector<var>&V: mat){
        for(var& v:V){
            init(v);
        }
    }
}

void initVec(vector<var>&vec){
    for(var& v:vec)init(v);
}

vector<vector<double>>randBatch(int howMany,int size){
    vector<vector<double>>out;
    for(int i=0;i<howMany;i++)out.push_back(randVecDouble(size));
    return out;
}
