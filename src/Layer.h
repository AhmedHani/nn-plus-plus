#ifndef LAYER_H
#define LAYER_H

#include <string>

class Layer {
public:
	Layer(int n_neurons, std::string activation);
	
	int get_n_neurons();
	std::string get_activation();

private:
	int n_neurons;
	std::string activation;
}; 

#endif