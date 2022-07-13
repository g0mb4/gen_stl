#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "box.h"
#include "cylinder.h"
#include "disk.h"
#include "pipe.h"

#include "error.h"

static const char* usage_str = "usage: gen_stl <shape> <params>\n\n"
                               "shapes:\n"
                               "  cube l mask\n"
                               "  box lx ly lz mask\n"
                               "  cylinder r h N mask\n"
                               "  pipe r1 r2 h N mask"
                               "  disk r N\n";

bool strequ(const char* s1, const char* s2)
{
    return strcmp(s1, s2) == 0;
}

double string2double(char* s)
{
    check(s != NULL, "cannot convert NULL\n");
    double d = 0;
    char* end = s;

    d = strtod(s, &end);

    check(end != NULL, "unable to convert '%s'\n", s);

    return d;
}

int string2int(char* s)
{
    check(s != NULL, "cannot convert NULL\n");

    int i = 0;
    char* end = s;

    i = strtol(s, &end, 10);

    check(end != NULL, "unable to convert '%s'\n", s);

    return i;
}

int main(int argc, char** argv)
{
    check(argc > 2, "%s", usage_str);

    const char* shape = argv[1];
    facet* facets = NULL;
    int len = 0;

    if (strequ(shape, "cube")) {
        check(argc == 4, "%s", usage_str);

        double l = string2double(argv[2]);
        int m = string2int(argv[3]);

        facets = box(&len, l, l, l, m);
    } else if (strequ(shape, "box")) {
        check(argc == 6, "%s", usage_str);

        double lx = string2double(argv[2]);
        double ly = string2double(argv[3]);
        double lz = string2double(argv[4]);
        int m = string2int(argv[5]);

        facets = box(&len, lx, ly, lz, m);
    } else if (strequ(shape, "cylinder")) {
        check(argc == 6, "%s", usage_str);

        double r = string2double(argv[2]);
        double h = string2double(argv[3]);
        int N = string2int(argv[4]);
        int m = string2int(argv[5]);

        facets = cylinder(&len, r, h, N, m);
    } else if (strequ(shape, "pipe")) {
        check(argc == 7, "%s", usage_str);

        double r1 = string2double(argv[2]);
        double r2 = string2double(argv[3]);
        double h = string2double(argv[4]);
        int N = string2int(argv[5]);
        int m = string2int(argv[6]);

        facets = pipe(&len, r1, r2, h, N, m);
    } else if (strequ(shape, "disk")) {
        check(argc == 4, "%s", usage_str);

        double r = string2double(argv[2]);
        int N = string2int(argv[3]);

        facets = disk(&len, r, N);
    } else {
        check(false, "unknown shape: '%s'\n", shape);
    }

    print_facets(facets, len);

    return 0;
}