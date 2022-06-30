#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

#define TODO() check(false, "%s:%d: TODO\n", __FILE__, __LINE__)

void check(bool ok, const char* fmt, ...);

#endif