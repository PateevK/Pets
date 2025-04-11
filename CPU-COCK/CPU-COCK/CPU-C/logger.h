#pragma once
#include <vector>

#define LOG 0
#if LOG 1
#define PRINT_ERR(x) std::cerr << "ERROR:: " << x <<'\n';
#else
#define PRINT_ERR(x)
#endif 

typedef enum {
	ERROR_OK = 0,
	ERROR_NO_CPUID = -1,
	ERROR_FAIL_CPUID = -2,
	ERROR_NO_CPUTYPE = -3,
	ERROR_FAIL_CACHE = -4   // Failed to determine cache.

}error_t;

const struct { error_t err; const char* description; } 
error_matchtable[] = {
	{ ERROR_OK, "No error" },
	{ERROR_NO_CPUID, "CPUID instruction is not supported :("},
};

//Querry to check if any error has occurred.
// //maybe vector can be substituted
