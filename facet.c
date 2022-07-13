#include "error.h"
#include "facet.h"

#include <math.h>
#include <stdio.h>

vector3 v3(double x, double y, double z)
{
    vector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

double v3_length(const vector3* v)
{
    double xx = v->x * v->x;
    double yy = v->y * v->y;
    double zz = v->z * v->z;

    return sqrt(xx + yy + zz);
}

void v3_normalise(vector3* v)
{
    double l = v3_length(v);

    v->x /= l;
    v->y /= l;
    v->z /= l;
}

void v3_scale(vector3* v, double s)
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

static void print_facet(const facet* f)
{
    printf("  facet normal %e %e %e\n", f->normal.x, f->normal.y, f->normal.z);
    printf("    outer loop\n");
    for (int i = 0; i < 3; ++i) {
        printf("      vertex %e %e %e\n", f->vertices[i].x, f->vertices[i].y, f->vertices[i].z);
    }
    printf("    endloop\n");
    printf("  endfacet\n");
}

void print_facets(const facet list[], int len)
{
    check(list != NULL && len > 0, "facet list is empty\n");

    printf("solid obj\n");

    for (int i = 0; i < len; ++i) {
        print_facet(&list[i]);
    }

    printf("endsolid\n");
}
