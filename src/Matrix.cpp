#include "Matrix.h"

Matrix::Matrix(int n, int m){block= new double[n*m];}

Matrix::~Matrix(){delete block;}
