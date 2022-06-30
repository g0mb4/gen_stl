#ifndef BOX_H
#define BOX_H

#include "facet.h"

enum {
    BOX_TOP = (1 << 0),
    BOX_BOTTOM = (1 << 1),
    BOX_FRONT = (1 << 2),
    BOX_BACK = (1 << 3),
    BOX_LEFT = (1 << 4),
    BOX_RIGHT = (1 << 5),
};

facet* box(int* len, double lx, double ly, double lz, int mask);

#endif