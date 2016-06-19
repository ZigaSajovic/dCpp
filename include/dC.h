#ifndef DC_H
#define DC_H
#include "operators.h"
#include "tau.h"
#include <eigen3/Eigen/Core>


namespace dC{
    void init(const var& v);
    var cos(const var& v);
    var sin(const var& v);
    var tan(const var& v);
    var cot(const var& v);
    var ln(const var& v);
    var log(double base, const var& v);
    var exp(const var& v);
    var sigmoid(const var& v);
    var reLu(const var& v);
    var reLuLeak(const var& v, double leak);
    void print(const var& v);
    template <typename Derived>
    void init(Eigen::MatrixBase<Derived>& matrix){
            for (size_t i=0, nRows=matrix.rows(), nCols=matrix.cols(); i<nCols; ++i)
                for (size_t j=0; j<nRows; ++j) dC::init(matrix(j,i));
        }
    template <typename Derived, class Func>
    void map_by_element(Eigen::MatrixBase<Derived>& matrix, Func fun){
            for (size_t i=0, nRows=matrix.rows(), nCols=matrix.cols(); i<nCols; ++i)
                for (size_t j=0; j<nRows; ++j)matrix(j,i)=fun(matrix(j,i));
    }
}
#endif // DC_H
