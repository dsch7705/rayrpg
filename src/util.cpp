#include "util.hpp"
#include <cstdarg>
#include <cstdio>
#include <string>
#include <iostream>
#include <stdexcept>


static DebugLevel debugLevel = DebugLevel::Warning;
void SetDebugLevel(DebugLevel level)
{
	debugLevel = level;
}
void DebugPrint(DebugLevel level, const char* fmt, ...)
{
	if (level < debugLevel)
		return;

	// Header
	switch (level)
	{
	case DebugLevel::Info:
		std::cout << "[MESSAGE]: ";
		break;
	case DebugLevel::Warning:
		std::cout << "[WARNING]: ";
		break;
	case DebugLevel::Error:
		std::cout << "[ERROR]: ";
		break;
	default:
		break;
	}

	// Message
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	std::cout << '\n';
}
void ThrowException(const char* fmt, ...)
{
	char msg[512];
	va_list args;
	va_start(args, fmt);
	vsprintf(msg, fmt, args);
	va_end(args);

	std::string err = "[RUNTIME EXCEPTION]: ";
	err.append(msg);
	std::cout << err << '\n';
	throw std::runtime_error(msg);
}