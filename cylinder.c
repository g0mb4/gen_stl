#include "cylinder.h"
#include "error.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
    creates a (0, 0, 0) centered cylinder
*/
facet* cylinder(int* len, double r, double h, double N, int mask)
{
    check(mask >= 0, "mask must be non-negative\n");

    int size = N * 2 * 2 * sizeof(facet); // theoretical maximum

    facet* list = (facet*)malloc(size);

    check(list != NULL, "unable to allocate memory\n");

    memset(list, 0, size);
    *len = 0;

    vector3* ring = malloc(N * sizeof(vector3));

    check(ring != NULL, "unable to allocate ring\n");

    double da = (2 * M_PI) / (double)(N - 1);
    for (int i = 0; i < N; ++i) {
        double x = r * cos(i * da);
        double y = r * sin(i * da);

        ring[i].x = x;
        ring[i].y = y;
    }

    for (int i = 0; i < N; ++i) {
        int pair = i == 0 ? N - 1 : i - 1;

        if (mask & CYLINDER_TOP) {
            list[*len].normal = v3(0.0, 0.0, 1.0);

            list[*len].vertices[0] = v3(0.0, 0.0, h / 2);

            list[*len].vertices[1].x = ring[i].x;
            list[*len].vertices[1].y = ring[i].y;
            list[*len].vertices[1].z = h / 2;

            list[*len].vertices[2].x = ring[pair].x;
            list[*len].vertices[2].y = ring[pair].y;
            list[*len].vertices[2].z = h / 2;
            ++*len;
        }

        if (mask & CYLINDER_BOTTOM) {
            list[*len].normal = v3(0.0, 0.0, -1.0);

            list[*len].vertices[0] = v3(0.0, 0.0, -h / 2);

            list[*len].vertices[1].x = ring[i].x;
            list[*len].vertices[1].y = ring[i].y;
            list[*len].vertices[1].z = -h / 2;

            list[*len].vertices[2].x = ring[pair].x;
            list[*len].vertices[2].y = ring[pair].y;
            list[*len].vertices[2].z = -h / 2;
            ++*len;
        }

        if (mask & CYLINDER_SIDE) {

            /* FIXME */
            vector3 n = v3(1.0, 0.0, 0.0);

            list[*len].normal = n;

            list[*len].vertices[0].x = ring[i].x;
            list[*len].vertices[0].y = ring[i].y;
            list[*len].vertices[0].z = h / 2;

            list[*len].vertices[1].x = ring[pair].x;
            list[*len].vertices[1].y = ring[pair].y;
            list[*len].vertices[1].z = h / 2;

            list[*len].vertices[2].x = ring[i].x;
            list[*len].vertices[2].y = ring[i].y;
            list[*len].vertices[2].z = -h / 2;

            ++*len;

            list[*len].normal = n;

            list[*len].vertices[0].x = ring[pair].x;
            list[*len].vertices[0].y = ring[pair].y;
            list[*len].vertices[0].z = h / 2;

            list[*len].vertices[1].x = ring[pair].x;
            list[*len].vertices[1].y = ring[pair].y;
            list[*len].vertices[1].z = -h / 2;

            list[*len].vertices[2].x = ring[i].x;
            list[*len].vertices[2].y = ring[i].y;
            list[*len].vertices[2].z = -h / 2;

            ++*len;
        }
    }

    return list;
}