#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include "Matrix.h"
#include "CostFunction.h"
#include "MiniBatchStochasticGradientDescent.h"

class LogisticRegression {
public:
	LogisticRegression(
		double n_features, 
		int batch_size, 
		double learning_rate, 
		double momentum, 
		std::string loss_type, 
		std::string optimizer);

	~LogisticRegression();
	void fit(Matrix* features, Matrix* labels);
	Matrix* predict(Matrix* features);
	void save(std::string dir);

private:
	double n_features;
	double learning_rate;
	double momentum;
	int batch_size;
	std::string loss_type;
	std::string optimizer;
	Matrix* weights;
	Matrix* bias;
	CostFunction* cost_function;
	MiniBatchStochasticGradientDescent* mini_batch_stochastic_gradient_descent;

	bool validate_fit(Matrix* features, Matrix* labels);
	bool validate_predict(Matrix* features);
	bool validate_save(std::string dir);
	void serialize();
};

#endif