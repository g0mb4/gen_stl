#ifndef FACET_H
#define FACET_H

typedef struct {
    double x, y, z;
} vector3;

typedef struct {
    vector3 normal;
    vector3 vertices[3];
} facet;

vector3 v3(double x, double y, double z);

void print_facets(const facet list[], int len);

#endif