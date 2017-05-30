#ifndef COSTFUNCTION_H
#define COSTFUNCTION_H

#include "Matrix.h"

class CostFunction {
public:
	static double mean_squared_error(double a, double b);
	static double mean_squared_error(double* a, double* b);
	static Matrix* mean_squared_error(Matrix* a, Matrix* b);
	static double mean_absolute_error(double a, double b);
	static double mean_absolute_error(double* a, double* b);
	static Matrix* mean_absolute_error(Matrix* a, Matrix* b);
	static double cross_entropy(double* a, double* b);
	static Matrix* cross_entropy(Matrix* a, Matrix* b);
};

#endif