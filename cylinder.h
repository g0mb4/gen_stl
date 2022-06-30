#ifndef CYLINDER_H
#define CYLINDER_H

#include "facet.h"

enum {
    CYLINDER_TOP = (1 << 0),
    CYLINDER_BOTTOM = (1 << 1),
    CYLINDER_SIDE = (1 << 2),
};

facet* cylinder(int* len, double r, double h, double N, int mask);

#endif