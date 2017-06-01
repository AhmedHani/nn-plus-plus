#ifndef OPERATION_H
#define OPERATION_H

#include <math.h>
#include "Matrix.h"

class Operation {
public:
	static Matrix* add(Matrix* a, Matrix* b);
	static Matrix* sub(Matrix* a, Matrix* b, bool absolute);
	static Matrix* mul(Matrix* a, double value);
	static Matrix* matmul(Matrix* a, Matrix* b);
	static Matrix* matdot(Matrix* a, Matrix* b);
	static Matrix* normalize(Matrix* a, double value);
	static double sum_squared(Matrix* a);
	static double round(double value, int precision);

private:
	static bool validate_add_sub_dot(Matrix* a, Matrix* b);
	static bool validate_matmul(Matrix* a, Matrix* b);
};

#endif