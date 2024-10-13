#pragma once
#include "fstream"
#include "iostream"
// #define DEBUG
struct BufferReplacement {
public:
	std::streambuf* buf;
	std::fstream f;
};
#define ER_LOG(message) std::cerr << "ERROR: " << message << std::endl
#define INFO_LOG(message) std::cout << "INFO: " << message << std::endl
#define ER_LOG_IF(message, condition) if(condition) ER_LOG(message)
#define INFO_LOG_IF(message, condition) if(condition) INFO_LOG(message)