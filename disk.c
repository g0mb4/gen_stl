#include "disk.h"
#include "error.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
    creates an axis-aligned (0, 0, 0) centered disk
*/
facet* disk(int* len, double r, double N)
{
    int max_size = N * sizeof(facet); // theoretical maximum

    facet* list = (facet*)malloc(max_size);

    check(list != NULL, "unable to allocate memory\n");

    memset(list, 0, max_size);
    int index = 0;

    vector3* ring = malloc(N * sizeof(vector3));

    check(ring != NULL, "unable to allocate ring\n");

    double angle_increment = (2 * M_PI) / (double)(N);
    for (int i = 0; i < N; ++i) {
        double x = r * cos(i * angle_increment);
        double y = r * sin(i * angle_increment);

        ring[i].x = x;
        ring[i].y = y;
    }

    for (int i = 0; i < N; ++i) {
        int pair = i == 0 ? N - 1 : i - 1;

        list[index].normal = v3(0.0, 0.0, 1.0);

        list[index].vertices[0] = v3(0.0, 0.0, 0.0);

        list[index].vertices[1].x = ring[i].x;
        list[index].vertices[1].y = ring[i].y;
        list[index].vertices[1].z = 0.0;

        list[index].vertices[2].x = ring[pair].x;
        list[index].vertices[2].y = ring[pair].y;
        list[index].vertices[2].z = 0.0;
        ++index;
    }

    *len = index;
    return list;
}