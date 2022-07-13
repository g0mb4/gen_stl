#include "error.h"
#include "pipe.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
    creates an axis-aligned (0, 0, 0) centered pipe
*/
facet* pipe(int* len, double r1, double r2, double h, double N, int mask)
{
    check(mask >= 0, "mask must be non-negative\n");
    check(r2 >= r1, "r2 mut be greather than r1\n");
    check(r1 != 0 && r2 != 0, "r1 and r2 must be positive\n");

    int max_size = 4 * N * 2 * 2 * sizeof(facet); // theoretical maximum

    facet* list = (facet*)malloc(max_size);

    check(list != NULL, "unable to allocate memory\n");

    memset(list, 0, max_size);
    int index = 0;

    vector3* inner_ring = malloc(N * sizeof(vector3));
    vector3* outer_ring = malloc(N * sizeof(vector3));

    check(inner_ring != NULL && outer_ring != 0, "unable to allocate rings\n");

    double angle_increment = (2 * M_PI) / (double)(N);
    for (int i = 0; i < N; ++i) {
        double x1 = r1 * cos(i * angle_increment);
        double y1 = r1 * sin(i * angle_increment);

        double x2 = r2 * cos(i * angle_increment);
        double y2 = r2 * sin(i * angle_increment);

        inner_ring[i].x = x1;
        inner_ring[i].y = y1;

        outer_ring[i].x = x2;
        outer_ring[i].y = y2;
    }

    for (int i = 0; i < N; ++i) {
        int pair = i == 0 ? N - 1 : i - 1;

        if (mask & PIPE_INNER_TOP) {
            list[index].normal = v3(0.0, 0.0, 1.0);

            list[index].vertices[0] = v3(0.0, 0.0, h / 2);

            list[index].vertices[1].x = inner_ring[i].x;
            list[index].vertices[1].y = inner_ring[i].y;
            list[index].vertices[1].z = h / 2;

            list[index].vertices[2].x = inner_ring[pair].x;
            list[index].vertices[2].y = inner_ring[pair].y;
            list[index].vertices[2].z = h / 2;
            ++index;
        }

        if (mask & PIPE_OUTER_TOP) {
            vector3 n = v3(0.0, 0.0, 1.0);

            list[index].normal = n;

            list[index].vertices[0].x = inner_ring[i].x;
            list[index].vertices[0].y = inner_ring[i].y;
            list[index].vertices[0].z = h / 2;

            list[index].vertices[1].x = inner_ring[pair].x;
            list[index].vertices[1].y = inner_ring[pair].y;
            list[index].vertices[1].z = h / 2;

            list[index].vertices[2].x = outer_ring[i].x;
            list[index].vertices[2].y = outer_ring[i].y;
            list[index].vertices[2].z = h / 2;

            ++index;

            list[index].normal = n;

            list[index].vertices[0].x = inner_ring[pair].x;
            list[index].vertices[0].y = inner_ring[pair].y;
            list[index].vertices[0].z = h / 2;

            list[index].vertices[1].x = outer_ring[pair].x;
            list[index].vertices[1].y = outer_ring[pair].y;
            list[index].vertices[1].z = h / 2;

            list[index].vertices[2].x = outer_ring[i].x;
            list[index].vertices[2].y = outer_ring[i].y;
            list[index].vertices[2].z = h / 2;

            ++index;
        }

        if (mask & PIPE_INNER_BOTTOM) {
            list[index].normal = v3(0.0, 0.0, -1.0);

            list[index].vertices[0] = v3(0.0, 0.0, -h / 2);

            list[index].vertices[1].x = inner_ring[i].x;
            list[index].vertices[1].y = inner_ring[i].y;
            list[index].vertices[1].z = -h / 2;

            list[index].vertices[2].x = inner_ring[pair].x;
            list[index].vertices[2].y = inner_ring[pair].y;
            list[index].vertices[2].z = -h / 2;
            ++index;
        }

        if (mask & PIPE_OUTER_BOTTOM) {
            vector3 n = v3(0.0, 0.0, -1.0);

            list[index].normal = n;

            list[index].vertices[0].x = inner_ring[i].x;
            list[index].vertices[0].y = inner_ring[i].y;
            list[index].vertices[0].z = -h / 2;

            list[index].vertices[1].x = inner_ring[pair].x;
            list[index].vertices[1].y = inner_ring[pair].y;
            list[index].vertices[1].z = -h / 2;

            list[index].vertices[2].x = outer_ring[i].x;
            list[index].vertices[2].y = outer_ring[i].y;
            list[index].vertices[2].z = -h / 2;

            ++index;

            list[index].normal = n;

            list[index].vertices[0].x = inner_ring[pair].x;
            list[index].vertices[0].y = inner_ring[pair].y;
            list[index].vertices[0].z = -h / 2;

            list[index].vertices[1].x = outer_ring[pair].x;
            list[index].vertices[1].y = outer_ring[pair].y;
            list[index].vertices[1].z = -h / 2;

            list[index].vertices[2].x = outer_ring[i].x;
            list[index].vertices[2].y = outer_ring[i].y;
            list[index].vertices[2].z = -h / 2;

            ++index;
        }

        if (mask & PIPE_INNER_SIDE) {
            double xm = (inner_ring[i].x + inner_ring[pair].x) / 2.0;
            double ym = (inner_ring[i].y + inner_ring[pair].y) / 2.0;

            vector3 n = v3(xm, ym, 0.0);
            v3_normalise(&n);
            v3_scale(&n, -1);

            list[index].normal = n;

            list[index].vertices[0].x = inner_ring[i].x;
            list[index].vertices[0].y = inner_ring[i].y;
            list[index].vertices[0].z = h / 2;

            list[index].vertices[1].x = inner_ring[pair].x;
            list[index].vertices[1].y = inner_ring[pair].y;
            list[index].vertices[1].z = h / 2;

            list[index].vertices[2].x = inner_ring[i].x;
            list[index].vertices[2].y = inner_ring[i].y;
            list[index].vertices[2].z = -h / 2;

            ++index;

            list[index].normal = n;

            list[index].vertices[0].x = inner_ring[pair].x;
            list[index].vertices[0].y = inner_ring[pair].y;
            list[index].vertices[0].z = h / 2;

            list[index].vertices[1].x = inner_ring[pair].x;
            list[index].vertices[1].y = inner_ring[pair].y;
            list[index].vertices[1].z = -h / 2;

            list[index].vertices[2].x = inner_ring[i].x;
            list[index].vertices[2].y = inner_ring[i].y;
            list[index].vertices[2].z = -h / 2;

            ++index;
        }

        if (mask & PIPE_OUTER_SIDE) {
            double xm = (outer_ring[i].x + outer_ring[pair].x) / 2.0;
            double ym = (outer_ring[i].y + outer_ring[pair].y) / 2.0;

            vector3 n = v3(xm, ym, 0.0);
            v3_normalise(&n);

            list[index].normal = n;

            list[index].vertices[0].x = outer_ring[i].x;
            list[index].vertices[0].y = outer_ring[i].y;
            list[index].vertices[0].z = h / 2;

            list[index].vertices[1].x = outer_ring[pair].x;
            list[index].vertices[1].y = outer_ring[pair].y;
            list[index].vertices[1].z = h / 2;

            list[index].vertices[2].x = outer_ring[i].x;
            list[index].vertices[2].y = outer_ring[i].y;
            list[index].vertices[2].z = -h / 2;

            ++index;

            list[index].normal = n;

            list[index].vertices[0].x = outer_ring[pair].x;
            list[index].vertices[0].y = outer_ring[pair].y;
            list[index].vertices[0].z = h / 2;

            list[index].vertices[1].x = outer_ring[pair].x;
            list[index].vertices[1].y = outer_ring[pair].y;
            list[index].vertices[1].z = -h / 2;

            list[index].vertices[2].x = outer_ring[i].x;
            list[index].vertices[2].y = outer_ring[i].y;
            list[index].vertices[2].z = -h / 2;

            ++index;
        }
    }

    *len = index;
    return list;
}