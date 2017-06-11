#include "Log.h"
#include "Layer.h"
#include "Operation.h"
#include "CostFunction.h"
#include "MeanSquaredError.h"
#include "MeanAbsoluteError.h"
#include "MultiLayerPerceptron.h"
#include "MiniBatchStochasticGradientDescent.h"


MultiLayerPerceptron::MultiLayerPerceptron(
	double n_features,
	double n_labels,
	std::vector<Layer*> layers,
	double learning_rate,
	double momentum,
	int batch_size,
	std::string loss_type,
	std::string optimizer):
n_features(n_features), n_labels(n_labels), layers(layers), learning_rate(learning_rate), momentum(momentum), batch_size(batch_size), loss_type(loss_type), optimizer(optimizer) {
	Matrix* input_to_hidden_weights = new Matrix(this->n_features, this->layers[0]->get_n_neurons(), "normal");
	Matrix* input_to_hidden_bias = new Matrix(this->batch_size, this->layers[0]->get_n_neurons(), "ones");

	this->weights.push_back(input_to_hidden_weights);
	this->bias.push_back(input_to_hidden_bias);

	for (int i = 1; i < this->layers.size(); i++) {
		Matrix* hidden_to_hidden_weights = new Matrix(this->layers[i - 1]->get_n_neurons(), this->layers[i]->get_n_neurons(), "normal");
		Matrix* hidden_to_hidden_bias = new Matrix(this->batch_size, this->layers[i]->get_n_neurons(), "ones");

		this->weights.push_back(new Matrix(hidden_to_hidden_weights->get_data(), hidden_to_hidden_weights->get_size(0), hidden_to_hidden_weights->get_size(1)));
		this->bias.push_back(new Matrix(hidden_to_hidden_bias->get_data(), hidden_to_hidden_bias->get_size(0), hidden_to_hidden_bias->get_size(1)));

	}

	Matrix* hidden_to_output_weights = new Matrix(this->layers[this->layers.size() - 1]->get_n_neurons(), this->n_labels, "normal");
	Matrix* hidden_to_output_bias = new Matrix(this->batch_size, this->n_labels, "ones");

	this->weights.push_back(hidden_to_output_weights);
	this->bias.push_back(hidden_to_output_bias);

	if (loss_type == "mse") {
		MeanSquaredError* mse = new MeanSquaredError();
		this->cost_function = mse;
	} else if (loss_type == "mae") {
		MeanAbsoluteError* mae = new MeanAbsoluteError();
		this->cost_function = mae;
	} else if (loss_type == "mce") {

	}

	if (optimizer == "sgd") {
		this->mini_batch_stochastic_gradient_descent = new MiniBatchStochasticGradientDescent(learning_rate, momentum);
	} else if (optimizer == "adam") {

	}
}

MultiLayerPerceptron::~MultiLayerPerceptron() {
	for (int i = 0; i < this->weights.size(); i++) {
		delete[] this->weights[i];
	}

	for (int i = 0; i < this->bias.size(); i++) {
		delete[] this->bias[i];
	}

	for (int i = 0; i < this->layers.size(); i++) {
		delete[] this->layers[i];
	}
	
	delete[] this->cost_function;
	delete[] this->mini_batch_stochastic_gradient_descent;
}

void MultiLayerPerceptron::fit(Matrix* features, Matrix* labels) {

}

Matrix* MultiLayerPerceptron::predict(Matrix* features) {
	
}

void MultiLayerPerceptron::save(std::string dir) {

}

bool MultiLayerPerceptron::validate_fit(Matrix* features, Matrix* labels) {
	if (features->get_size(0) != labels->get_size(0)) {
		throw "The number of items should be equal!";
	}

	return true;
}

bool MultiLayerPerceptron::validate_predict(Matrix* features) {
	return true;
}

void MultiLayerPerceptron::serialize() {

}