#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Matrix.h"

class DataManager {
public:
	DataManager(
		std::string file_name,
		int n_features,
		int n_labels,
		bool has_header,
		std::set<int> ignore_columns,
		double train_size = 0.8, 
		double valid_size = 0.1, 
		double test_size = 0.1,
		int batch_size = 128,
		bool normalize = true,
		bool shuffle = true);

	void batchify();
	std::pair<Matrix*, Matrix*> next_train_batch();
	std::pair<Matrix*, Matrix*> next_valid_batch();
	std::pair<Matrix*, Matrix*> next_test_batch();

private:
	std::string file_name;
	int n_features;
	int n_labels;
	bool has_header;
	std::set<int> ignore_columns;
	double train_size;
	double valid_size;
	double test_size;
	int batch_size;
	bool normalize;
	bool shuffle;
	int train_data_batch_ptr;
	int valid_data_batch_ptr;
	int test_data_batch_ptr;

	std::map<std::string, std::vector<double>> categories_ids;

	std::vector<std::vector<double>> all_data_features;
	std::vector<std::vector<double>> all_data_labels;

	std::vector<std::vector<double>> train_features;
	std::vector<std::vector<double>> valid_features;
	std::vector<std::vector<double>> test_features;

	std::vector<std::vector<double>> train_labels;
	std::vector<std::vector<double>> valid_labels;
	std::vector<std::vector<double>> test_labels;

	std::vector<Matrix*> train_features_batches;
	std::vector<Matrix*> train_labels_batches;

	std::vector<Matrix*> valid_features_batches;
	std::vector<Matrix*> valid_labels_batches;

	std::vector<Matrix*> test_features_batches;
	std::vector<Matrix*> test_labels_batches;

	void read_data();
};

#endif