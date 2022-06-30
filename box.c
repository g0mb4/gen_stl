#include "box.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    creates a (0, 0, 0) centered box
*/
facet* box(int* len, double lx, double ly, double lz, int mask)
{
    check(mask >= 0, "mask must be non-negative\n");

    int size = 6 * 2 * sizeof(facet); // theoretical maximum

    facet* list = (facet*)malloc(size);

    check(list != NULL, "unable to allocate memory\n");

    memset(list, 0, size);
    *len = 0;

    double w = lx / 2;
    double h = ly / 2;
    double d = lz / 2;

    if (mask & BOX_LEFT) {
        list[*len].normal = v3(-1.0, 0.0, 0.0);
        list[*len].vertices[0] = v3(-w, h, d);
        list[*len].vertices[1] = v3(-w, h, -d);
        list[*len].vertices[2] = v3(-w, -h, d);
        ++*len;

        list[*len].normal = v3(-1.0, 0.0, 0.0);
        list[*len].vertices[0] = v3(-w, -h, d);
        list[*len].vertices[1] = v3(-w, h, -d);
        list[*len].vertices[2] = v3(-w, -h, -d);
        ++*len;
    }

    if (mask & BOX_RIGHT) {
        list[*len].normal = v3(1.0, 0.0, 0.0);
        list[*len].vertices[0] = v3(w, h, -d);
        list[*len].vertices[1] = v3(w, h, d);
        list[*len].vertices[2] = v3(w, -h, -d);
        ++*len;

        list[*len].normal = v3(1.0, 0.0, 0.0);
        list[*len].vertices[0] = v3(w, -h, -d);
        list[*len].vertices[1] = v3(w, h, d);
        list[*len].vertices[2] = v3(w, -h, d);
        ++*len;
    }

    if (mask & BOX_TOP) {
        list[*len].normal = v3(0.0, 0.0, 1.0);
        list[*len].vertices[0] = v3(w, h, d);
        list[*len].vertices[1] = v3(-w, h, d);
        list[*len].vertices[2] = v3(w, -h, d);
        ++*len;

        list[*len].normal = v3(0.0, 0.0, 1.0);
        list[*len].vertices[0] = v3(w, -h, d);
        list[*len].vertices[1] = v3(-w, h, d);
        list[*len].vertices[2] = v3(-w, -h, d);
        ++*len;
    }

    if (mask & BOX_BOTTOM) {
        list[*len].normal = v3(0.0, 0.0, -1.0);
        list[*len].vertices[0] = v3(-w, h, -d);
        list[*len].vertices[1] = v3(w, h, -d);
        list[*len].vertices[2] = v3(-w, -h, -d);
        ++*len;

        list[*len].normal = v3(0.0, 0.0, -1.0);
        list[*len].vertices[0] = v3(-w, -h, -d);
        list[*len].vertices[1] = v3(w, h, -d);
        list[*len].vertices[2] = v3(w, -h, -d);
        ++*len;
    }

    if (mask & BOX_FRONT) {
        list[*len].normal = v3(0.0, -1.0, 0.0);
        list[*len].vertices[0] = v3(w, -h, -d);
        list[*len].vertices[1] = v3(w, -h, d);
        list[*len].vertices[2] = v3(-w, -h, -d);
        ++*len;

        list[*len].normal = v3(0.0, -1.0, 0.0);
        list[*len].vertices[0] = v3(-w, -h, -d);
        list[*len].vertices[1] = v3(w, -h, d);
        list[*len].vertices[2] = v3(-w, -h, d);
        ++*len;
    }

    if (mask & BOX_BACK) {
        list[*len].normal = v3(0.0, 1.0, 0.0);
        list[*len].vertices[0] = v3(w, h, d);
        list[*len].vertices[1] = v3(w, h, -d);
        list[*len].vertices[2] = v3(-w, h, d);
        ++*len;

        list[*len].normal = v3(0.0, 1.0, 0.0);
        list[*len].vertices[0] = v3(-w, h, d);
        list[*len].vertices[1] = v3(w, h, -d);
        list[*len].vertices[2] = v3(-w, h, -d);
        ++*len;
    }

    return list;
}