

enum DebugLevel
{
	All,
	Warning,
	Error,
	None
};
void SetDebugLevel(DebugLevel level);
void DebugPrint(DebugLevel level, const char* fmt, ...);