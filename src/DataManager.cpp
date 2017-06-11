#include "DataManager.h"
#include "Operation.h"
#include "Util.h"
#include <fstream>
#include <set>
#include <algorithm>


DataManager::DataManager(
	std::string file_name,
	int n_features,
	int n_labels,
	bool has_header,
	std::set<int> ignore_columns,
	double train_size, 
	double valid_size, 
	double test_size,
	int batch_size,
	bool normalize,
	bool shuffle):
file_name(file_name), n_features(n_features), n_labels(n_labels), has_header(has_header), ignore_columns(ignore_columns), train_size(train_size), valid_size(valid_size), test_size(test_size), batch_size(batch_size), normalize(normalize), shuffle(shuffle) {
	this->read_data();

	this->train_data_batch_ptr = 0;
	this->valid_data_batch_ptr = 0;
	this->test_data_batch_ptr = 0;
}

void DataManager::read_data() {
	std::ifstream file(this->file_name);
	int current_line_index = 0;
	std::string line;

	std::vector<std::map<std::string, int>> columns_categories_ids(this->n_features - this->ignore_columns.size());
	std::map<std::string, int> labels_categories_ids;
	std::vector<std::pair<int, int>> missing_values;

	while (std::getline(file, line)) {
		if (current_line_index++ == 0 && has_header)
			continue;

		std::vector<double> row;
		std::vector<std::string> line_tokens = Util::split(line, ',');

		for (int i = 0; i < line_tokens.size() - 1; i++) {
			if (this->ignore_columns.find(i) != this->ignore_columns.end())
				continue;

			if (line_tokens[i].empty()) {
				missing_values.push_back(std::make_pair(current_line_index, i));

				continue;
			}

			if (std::stod(line_tokens[i]) || std::stoi(line_tokens[i])) {
				row.push_back(atof(line_tokens[i].c_str()));
			} else {
				std::map<std::string, int> column_category = columns_categories_ids[i];

				if (column_category.empty()) {
					column_category[line_tokens[i]] = 1;
					row.push_back(1);
				} else {
					if (column_category.find(line_tokens[i]) != column_category.end()) {
						row.push_back(column_category[line_tokens[i]]);

						continue;
					}

					int max_value = -INT_MAX;

					for (std::map<std::string, int>::iterator it = column_category.begin(); it != column_category.end(); it++) {
						max_value = std::max(max_value, it->second);
					}

					column_category[line_tokens[i]] = max_value + 1;
					row.push_back(max_value + 1);
				}

				columns_categories_ids[i] = column_category;
			}
		}

		this->all_data_features.push_back(row);

		std::string label = line_tokens[line_tokens.size() - 1];
		std::vector<double> label_vector;

		if (std::all_of(label.begin(), label.end(), ::isdigit)) {
			label_vector.push_back(atof(label.c_str()));
		} else {
			if (labels_categories_ids.empty()) {
				labels_categories_ids[label] = 1;
				label_vector.push_back(1);
			} else {
				if (labels_categories_ids.find(label) != labels_categories_ids.end()) {
					label_vector.push_back(labels_categories_ids[label]);

					this->all_data_labels.push_back(label_vector);
					continue;
				}

				int max_value = -INT_MAX;

				for (std::map<std::string, int>::iterator it = labels_categories_ids.begin(); it != labels_categories_ids.end(); it++) {
					max_value = std::max(max_value, it->second);
				}

				labels_categories_ids[label] = max_value + 1;
				label_vector.push_back(max_value + 1);
			}
		}

		this->all_data_labels.push_back(label_vector);
	}

	int max_label_value = -INT_MAX;

	for (std::map<std::string, int>::iterator it = labels_categories_ids.begin(); it != labels_categories_ids.end(); it++) {
		max_label_value = std::max(max_label_value, it->second);
	}

	for (int i = 0; i < this->all_data_labels.size(); i++) {
		std::vector<double> one_hot_for_labels(max_label_value, 0.0);
		one_hot_for_labels[this->all_data_labels[i][0] - 1] = 1;

		this->all_data_labels[i] = one_hot_for_labels;
	}

	if (normalize) {
		for (int i = 0; i < columns_categories_ids.size(); i++) {
			if (columns_categories_ids[i].empty()) {
				double sum = 0.0;
				double mean = 0.0;
				double sigma = 0.0;

				for (int j = 0; j < this->all_data_features.size(); j++) {
					std::vector<double> row = this->all_data_features[j];

					sum += row[i];
				}

				mean = sum / this->all_data_features.size();

				for (int j = 0; j < this->all_data_features.size(); j++) {
					std::vector<double> row = this->all_data_features[j];

					sigma += pow(row[i] - mean, 2);
				}

				sigma = sqrt(sigma);

				for (int j = 0; j < this->all_data_features.size(); j++) {
					std::vector<double> row = this->all_data_features[j];

					row[i] = Operation::round((row[i] - mean) / sigma, 3);

					this->all_data_features[j] = row;
				}
			}
		}
	}

	for (int i = 0; i < columns_categories_ids.size(); i++) {
		if (!columns_categories_ids[i].empty()) {
			std::map<std::string, int> current = columns_categories_ids[i];

			int max_feature_value = -INT_MAX;

			for (std::map<std::string, int>::iterator it = current.begin(); it != current.end(); it++) {
				max_feature_value = std::max(max_feature_value, it->second);
			}

			std::vector<double> one_hot_for_feature(max_feature_value, 0.0);

			for (int j = 0; j < this->all_data_features.size(); j++) {
				std::vector<double> row = this->all_data_features[j];
				one_hot_for_feature[row[i]] = 1;
				int index = i;

				for (int k = 0; k < one_hot_for_feature.size(); k++) {
					row.insert(row.begin()+index++, one_hot_for_feature[k]);
				}

				this->all_data_features[j] = row;
			}
		}
	}

	std::vector<int> shuffled_indices(this->all_data_features.size());

	for (int i = 0; i < shuffled_indices.size(); i++) {
		shuffled_indices[i] = i;
	}

	std::random_shuffle(shuffled_indices.begin(), shuffled_indices.end());
	auto temp_data(this->all_data_features);

	for (int i = 0; i < this->all_data_features.size(); i++) {
		this->all_data_features[i] = temp_data[shuffled_indices[i]];
	}

	this->train_size = (int)(this->train_size * (double)this->all_data_features.size());
	this->valid_size = (int)(this->valid_size * this->all_data_features.size());
	this->test_size = (int)(this->test_size * this->all_data_features.size());

	this->train_features.assign(this->all_data_features.begin(), this->all_data_features.begin() + train_size);
	this->train_labels.assign(this->all_data_labels.begin(), this->all_data_labels.begin() + train_size);
	this->valid_features.assign(this->all_data_features.begin() + train_size + 1, this->all_data_features.begin() + train_size + 1 + valid_size);
	this->valid_labels.assign(this->all_data_labels.begin() + train_size + 1, this->all_data_labels.begin() + train_size + 1 + valid_size);
	this->test_features.assign(this->all_data_features.begin() + train_size + 1 + valid_size + 1, this->all_data_features.end());
	this->test_labels.assign(this->all_data_labels.begin() + train_size + 1 + valid_size + 1, this->all_data_labels.end());

	this->batchify();
}

void DataManager::batchify() {
	Matrix* features_matrix = new Matrix(this->batch_size, this->n_features, "zeros");
	Matrix* label_matrix = new Matrix(this->batch_size, this->n_labels, "zeros");

	for (int i = 0; i < this->train_features.size(); i++) {

		for (int j = 0; j < this->train_features[i].size(); j++) {
			features_matrix->set_value(i, j, this->train_features[i][j]);
		}

		for (int j = 0; j < this->train_labels[i].size(); j++) {
			label_matrix->set_value(i, j, this->train_labels[i][j]);
		}

		if (i % this->batch_size == 0) {
			this->train_features_batches.push_back(new Matrix(features_matrix->get_data(), features_matrix->get_size(0), features_matrix->get_size(1)));
			this->train_labels_batches.push_back(new Matrix(label_matrix->get_data(), label_matrix->get_size(0), label_matrix->get_size(1)));

			features_matrix = new Matrix(this->batch_size, this->n_features, "zeros");
			label_matrix = new Matrix(this->batch_size, this->n_labels, "zeros");
		}
	}

	features_matrix = new Matrix(this->batch_size, this->n_features, "zeros");
	label_matrix = new Matrix(this->batch_size, this->n_labels, "zeros");

	for (int i = 0; i < this->valid_features.size(); i++) {

		for (int j = 0; j < this->valid_features[i].size(); j++) {
			features_matrix->set_value(i, j, this->valid_features[i][j]);
		}

		for (int j = 0; j < this->valid_labels[i].size(); j++) {
			label_matrix->set_value(i, j, this->valid_labels[i][j]);
		}

		if (i % this->batch_size == 0) {
			this->valid_features_batches.push_back(new Matrix(features_matrix->get_data(), features_matrix->get_size(0), features_matrix->get_size(1)));
			this->valid_labels_batches.push_back(new Matrix(label_matrix->get_data(), label_matrix->get_size(0), label_matrix->get_size(1)));

			features_matrix = new Matrix(this->batch_size, this->n_features, "zeros");
			label_matrix = new Matrix(this->batch_size, this->n_labels, "zeros");
		}
	}

	features_matrix = new Matrix(this->batch_size, this->n_features, "zeros");
	label_matrix = new Matrix(this->batch_size, this->n_labels, "zeros");

	for (int i = 0; i < this->test_features.size(); i++) {

		for (int j = 0; j < this->test_features[i].size(); j++) {
			features_matrix->set_value(i, j, this->test_features[i][j]);
		}

		for (int j = 0; j < this->test_labels[i].size(); j++) {
			label_matrix->set_value(i, j, this->test_labels[i][j]);
		}

		if (i % this->batch_size == 0) {
			this->test_features_batches.push_back(new Matrix(features_matrix->get_data(), features_matrix->get_size(0), features_matrix->get_size(1)));
			this->test_labels_batches.push_back(new Matrix(label_matrix->get_data(), label_matrix->get_size(0), label_matrix->get_size(1)));

			features_matrix = new Matrix(this->batch_size, this->n_features, "zeros");
			label_matrix = new Matrix(this->batch_size, this->n_labels, "zeros");
		}
	}
}

std::pair<Matrix*, Matrix*> DataManager::next_train_batch() {
	if (this->train_data_batch_ptr >= train_features_batches.size())
		return std::pair<Matrix*, Matrix*>();

	return std::make_pair(
		this->train_features_batches[this->train_data_batch_ptr],
		this->train_labels_batches[this->train_data_batch_ptr++]
		);
}

std::pair<Matrix*, Matrix*> DataManager::next_valid_batch() {
	if (this->valid_data_batch_ptr >= valid_features_batches.size())
		return std::pair<Matrix*, Matrix*>();

	return std::make_pair(
		this->valid_features_batches[this->valid_data_batch_ptr],
		this->valid_labels_batches[this->valid_data_batch_ptr++]
		);
}

std::pair<Matrix*, Matrix*> DataManager::next_test_batch() {
	if (this->test_data_batch_ptr >= test_features_batches.size())
		return std::pair<Matrix*, Matrix*>();

	return std::make_pair(
		this->test_features_batches[this->test_data_batch_ptr],
		this->test_labels_batches[this->test_data_batch_ptr++]
		);
}
