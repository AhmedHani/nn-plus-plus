#include "Util.h"
#include <vector>

std::vector<std::string> Util::split(std::string &text, char deli) {
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