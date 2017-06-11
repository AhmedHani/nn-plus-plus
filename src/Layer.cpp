#include <string>
#include "Layer.h"

Layer::Layer(int n_neurons, std::string activation): n_neurons(n_neurons), activation(activation) {}

int Layer::get_n_neurons() {
	return this->n_neurons;
}

std::string Layer::get_activation() {
	return this->activation;
}