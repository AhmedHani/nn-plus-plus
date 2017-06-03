#include "DataManager.h"
#include <fstream>
#include <set>

DataManager::DataManager(
	std::string file_name,
	int n_features,
	int n_labels,
	bool has_header,
	std::set<int> ignore_columns,
	double train_size, 
	double valid_size, 
	double test_size,
	bool normalize):
file_name(file_name), has_header(has_header), ignore_columns(ignore_columns), train_size(train_size), valid_size(valid_size), test_size(test_size), normalize(normalize) {
	this->read_data();

	this->train_data_batch_ptr = 0;
	this->valid_data_batch_ptr = 0;
}

void DataManager::read_data() {
	std::ifstream file(this->file_name);
	int current_line_index = 0;
	std::string line;

	std::vector<std::map<std::string, int>> columns_categories_ids(this->n_features);
	std::map<std::string, int> labels_categories_ids;
	std::vector<std::pair<int, int>> missing_values;

	while (std::getline(file, line)) {
		if (current_line_index++ == 0 && has_header)
			continue;

		std::vector<std::string> line_tokens = this->split(line, ',');

		std::vector<double> row;

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

			this->all_data_features.push_back(row);
		}

		std::string label = line_tokens[line_tokens.size() - 1];
		std::vector<double> label_vector;

		if (std::stod(label) || std::stoi(label)) {
			label_vector.push_back(atof(label.c_str()));
		} else {
			if (labels_categories_ids.empty()) {
				labels_categories_ids[label] = 1;
				label_vector.push_back(1);
			} else {
				if (labels_categories_ids.find(label) != labels_categories_ids.end()) {
					label_vector.push_back(labels_categories_ids[label]);

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

	// TODO one-hot & normalize & fill empty cells by the mean
}

std::vector<std::string> DataManager::split(std::string &text, char deli) {
	std::vector<std::string> tokens;
	int start = 0;
	int end = 0;

	while ((end = text.find(deli, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}

	tokens.push_back(text.substr(start));

	return tokens;
}

