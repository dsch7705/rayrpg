#pragma once


enum DebugLevel
{
	Info,
	Warning,
	Error,
	None
};
void SetDebugLevel(DebugLevel level);
void DebugPrint(DebugLevel level, const char* fmt, ...);
void ThrowException(const char* fmt, ...);