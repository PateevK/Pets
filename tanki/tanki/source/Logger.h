#pragma once

#define LOG_ERROR 
#define LOG_WARNING

#ifdef LOG_ERROR
#define ERROR(x) x
#else 
#define ERROR(x)
#endif

#ifdef LOG_WARNING
#define WARNING(x) x
#else
#define WARNING(x)
#endif

enum ERROR{
	ERROR_BUFFER_SZ = -1, // Number of verticis is < or == 0.
	WARNING_BUFFER_ACCES = -2, // vertices out of bounds;
	WARNING_WRITING_VIOLATION = -3, // Tried to write at position more then Screen x\y or < 0;
};
