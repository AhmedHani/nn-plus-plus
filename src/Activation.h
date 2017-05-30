#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

class Activation {
public:
	static double sigmoid(double value);
	static Matrix* sigmoid(Matrix* values);
	static double relu(double value);
	static double tanh(double value);
	static double signum(double value);
	static Matrix* softmax(Matrix* a);
};

#endif