#ifndef MEANABSOLUTEERROR_H
#define MEANABSOLUTEERROR_H

#include "CostFunction.h"

class MeanAbsoluteError : public CostFunction {
public:
	double get_error(double a, double b);
	double* get_error(int size, double* a, double* b);
	Matrix* get_error(Matrix* a, Matrix* b);
};

#endif