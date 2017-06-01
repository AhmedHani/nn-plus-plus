#ifndef LOG_H
#define LOG_H

#include <string>
#include "Matrix.h"

class Log {
public:
	static void show(int value, std::string message);
	static void show(double value, std::string message);
	static void show(Matrix* matrix, std::string message);
	static void show(std::string value, std::string message);
};

#endif