#ifndef MEANSQUAREDERROR_H
#define MEANSQUAREDERROR_H

#include "CostFunction.h"

class MeanSquaredError : public CostFunction {
public:
	double get_error(double a, double b);
	double* get_error(int size, double* a, double* b);
	Matrix* get_error(Matrix* a, Matrix* b);
};

#endif