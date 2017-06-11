#ifndef MULTI_LAYER_PERCEPTRON_H
#define MULTI_LAYER_PERCEPTRON_H

#include "Matrix.h"
#include "Layer.h"
#include "CostFunction.h"
#include "MiniBatchStochasticGradientDescent.h"

class MultiLayerPerceptron {
public:
	MultiLayerPerceptron(
		double n_features,
		double n_labels,
		std::vector<Layer*> layers,
		double learning_rate,
		double momentum,
		int batch_size,
		std::string loss_type,
		std::string optimizer);

	~MultiLayerPerceptron();

	void fit(Matrix* features, Matrix* labels);
	Matrix* predict(Matrix* features);
	void save(std::string dir);
	void load(std::string dir);

private:
	double n_features;
	double n_labels;
	std::vector<Layer*> layers;
	double learning_rate;
	double momentum;
	int batch_size;
	std::string loss_type;
	std::string optimizer;
	std::vector<Matrix*> weights;
	std::vector<Matrix*> bias;
	CostFunction* cost_function;
	MiniBatchStochasticGradientDescent* mini_batch_stochastic_gradient_descent;

	Matrix* apply_hidden_activation(Matrix* linear, std::string activation);
	Matrix* apply_output_activation(Matrix* linear);
	bool validate_fit(Matrix* features, Matrix* labels);
	bool validate_predict(Matrix* features);
	bool validate_save(std::string dir);
	void serialize();
};

#endif