#include <iostream>
#include "Matrix.h"
#include "LogisticRegression.h"
#include "Log.h"
#include "DataManager.h"

using namespace std;


int main(int argc, char* argv) {
	std::string file_name = "iris.csv";
	int ignore[] = {0};

	DataManager* data_manager = new DataManager(
		file_name,
		5,
		3,
		true,
		std::set<int>(ignore, ignore + 1));


	

	return 0;
}
