#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void check(bool ok, const char* fmt, ...)
{
    va_list args;

    if (!ok) {
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        exit(1);
    }
}
