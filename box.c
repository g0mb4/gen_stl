#include "box.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    creates an axis-aligned (0, 0, 0) centered box
*/
facet* box(int* len, double lx, double ly, double lz, int mask)
{
    check(mask >= 0, "mask must be non-negative\n");

    int max_size = 6 * 2 * sizeof(facet); // theoretical maximum

    facet* list = (facet*)malloc(max_size);

    check(list != NULL, "unable to allocate memory\n");

    memset(list, 0, max_size);
    int index = 0;

    double w = lx / 2;
    double h = ly / 2;
    double d = lz / 2;

    if (mask & BOX_LEFT) {
        list[index].normal = v3(-1.0, 0.0, 0.0);
        list[index].vertices[0] = v3(-w, h, d);
        list[index].vertices[1] = v3(-w, h, -d);
        list[index].vertices[2] = v3(-w, -h, d);
        ++index;

        list[index].normal = v3(-1.0, 0.0, 0.0);
        list[index].vertices[0] = v3(-w, -h, d);
        list[index].vertices[1] = v3(-w, h, -d);
        list[index].vertices[2] = v3(-w, -h, -d);
        ++index;
    }

    if (mask & BOX_RIGHT) {
        list[index].normal = v3(1.0, 0.0, 0.0);
        list[index].vertices[0] = v3(w, h, -d);
        list[index].vertices[1] = v3(w, h, d);
        list[index].vertices[2] = v3(w, -h, -d);
        ++index;

        list[index].normal = v3(1.0, 0.0, 0.0);
        list[index].vertices[0] = v3(w, -h, -d);
        list[index].vertices[1] = v3(w, h, d);
        list[index].vertices[2] = v3(w, -h, d);
        ++index;
    }

    if (mask & BOX_TOP) {
        list[index].normal = v3(0.0, 0.0, 1.0);
        list[index].vertices[0] = v3(w, h, d);
        list[index].vertices[1] = v3(-w, h, d);
        list[index].vertices[2] = v3(w, -h, d);
        ++index;

        list[index].normal = v3(0.0, 0.0, 1.0);
        list[index].vertices[0] = v3(w, -h, d);
        list[index].vertices[1] = v3(-w, h, d);
        list[index].vertices[2] = v3(-w, -h, d);
        ++index;
    }

    if (mask & BOX_BOTTOM) {
        list[index].normal = v3(0.0, 0.0, -1.0);
        list[index].vertices[0] = v3(-w, h, -d);
        list[index].vertices[1] = v3(w, h, -d);
        list[index].vertices[2] = v3(-w, -h, -d);
        ++index;

        list[index].normal = v3(0.0, 0.0, -1.0);
        list[index].vertices[0] = v3(-w, -h, -d);
        list[index].vertices[1] = v3(w, h, -d);
        list[index].vertices[2] = v3(w, -h, -d);
        ++index;
    }

    if (mask & BOX_FRONT) {
        list[index].normal = v3(0.0, -1.0, 0.0);
        list[index].vertices[0] = v3(w, -h, -d);
        list[index].vertices[1] = v3(w, -h, d);
        list[index].vertices[2] = v3(-w, -h, -d);
        ++index;

        list[index].normal = v3(0.0, -1.0, 0.0);
        list[index].vertices[0] = v3(-w, -h, -d);
        list[index].vertices[1] = v3(w, -h, d);
        list[index].vertices[2] = v3(-w, -h, d);
        ++index;
    }

    if (mask & BOX_BACK) {
        list[index].normal = v3(0.0, 1.0, 0.0);
        list[index].vertices[0] = v3(w, h, d);
        list[index].vertices[1] = v3(w, h, -d);
        list[index].vertices[2] = v3(-w, h, d);
        ++index;

        list[index].normal = v3(0.0, 1.0, 0.0);
        list[index].vertices[0] = v3(-w, h, d);
        list[index].vertices[1] = v3(w, h, -d);
        list[index].vertices[2] = v3(-w, h, -d);
        ++index;
    }

    *len = index;
    return list;
}