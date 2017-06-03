#ifndef COSTFUNCTION_H
#define COSTFUNCTION_H

#include "Matrix.h"

class CostFunction {
public:
	CostFunction() {}
	virtual double get_error(double a, double b) = 0;
	virtual double* get_error(int size, double* a, double* b) = 0;
	virtual Matrix* get_error(Matrix* a, Matrix* b) = 0;
};

#endif