#include "util.hpp"
#include <cstdarg>
#include <cstdio>
#include <iostream>


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
	case DebugLevel::All:
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
}