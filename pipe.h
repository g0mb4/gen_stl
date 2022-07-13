#ifndef PIPE_H
#define PIPE_H

#include "facet.h"

enum {
    PIPE_INNER_TOP = (1 << 0),
    PIPE_OUTER_TOP = (1 << 1),
    PIPE_INNER_BOTTOM = (1 << 2),
    PIPE_OUTER_BOTTOM = (1 << 3),
    PIPE_INNER_SIDE = (1 << 4),
    PIPE_OUTER_SIDE = (1 << 5),
};

facet* pipe(int* len, double r1, double r2, double h, double N, int mask);

#endif