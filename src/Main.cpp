#include <iostream>
#include "Matrix.h"
#include "LogisticRegression.h"
#include "Log.h"

using namespace std;


int main(int argc, char* argv) {
	int epochs = 50;
	int n_features = 2;
	int n_labels = 1;
	double learning_rate = 0.01;
	int batch_size = 4;
	double momentum = 0.2;
	std::string loss_type = "mse";

	Matrix* input_batch = new Matrix(4, 2, "zeros");
	input_batch->set_value(0, 0, 0.0);
	input_batch->set_value(0, 1, 0.0);

	input_batch->set_value(1, 0, 0.0);
	input_batch->set_value(1, 1, 1.0);

	input_batch->set_value(2, 0, 1.0);
	input_batch->set_value(2, 1, 0.0);

	input_batch->set_value(3, 0, 1.0);
	input_batch->set_value(3, 1, 1.0);

	Matrix* output = new Matrix(4, 1, "zeros");
	output->set_value(0, 0, 0.0);
	output->set_value(1, 0, 1.0);
	output->set_value(2, 0, 1.0);
	output->set_value(3, 0, 0.0);

	Log::show(epochs, "epochs");
	Log::show(batch_size, "batch size");
	Log::show(learning_rate, "learning rate");
	Log::show(momentum, "momentum");
	Log::show(loss_type, "loss function");

	LogisticRegression* lr = new LogisticRegression(n_features, batch_size, learning_rate, momentum, loss_type, "sgd");

	for (int i = 0; i < epochs; i++)
		lr->fit(input_batch, output);	
	

	return 0;
}
