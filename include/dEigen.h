#ifndef DEIGEN_H
#define DEIGEN_H

#include <eigen3/Eigen/Core>

namespace dCpp{
    template <typename Derived>
    void init(Eigen::MatrixBase<Derived>& matrix){
            for (size_t i=0, nRows=matrix.rows(), nCols=matrix.cols(); i<nCols; ++i)
                for (size_t j=0; j<nRows; ++j) dCpp::init(matrix(j,i));
        }
    template <typename Derived, class Func>
    void map_by_element(Eigen::MatrixBase<Derived>& matrix, Func fun){
            for (size_t i=0, nRows=matrix.rows(), nCols=matrix.cols(); i<nCols; ++i)
                for (size_t j=0; j<nRows; ++j)matrix(j,i)=fun(matrix(j,i));
    }
}

#endif // DEIGEN_H
