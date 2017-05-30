#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H

#include "Matrix.h"
#include "CostFunction.h"

class LogisticRegression {
public:
	LogisticRegression(double n_features, int batch_size, double learning_rate, double momentum, std::string loss_type);
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
	Matrix* weights;
	Matrix* bias;

	bool validate_fit(Matrix* features, Matrix* labels);
	bool validate_predict(Matrix* features);
	bool validate_save(std::string dir);
	void serialize();
	void update(Matrix* gradients);
};

#endif