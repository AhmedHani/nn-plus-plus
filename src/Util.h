#ifndef UTIL_H
#define UTIL_H

#include <vector>

class Util {
public:
	static std::vector<std::string> split(std::string &text, char deli);
};

#endif