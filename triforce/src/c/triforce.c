#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef bool
#define bool char
#define false 0
#define true 1
#endif

#define SLACK 0.1

typedef struct t_vertex {
    float x, y;
} vertex;

typedef struct t_triangle {
    vertex v[3];
} triangle;

/**
 * Reads the coordinates for a triangle from stdin
 */
inline void
scan_triangle(triangle *t)
{
    scanf("%f %f %f %f %f %f", &(t->v[0].x), &(t->v[0].y),
        &(t->v[1].x), &(t->v[1].y), &(t->v[2].x), &(t->v[2].y));
}

/**
 * Calculates the Euclidean distance
 * between the two vertices
 */
inline float
dist(vertex *v1, vertex *v2)
{
    return sqrtf(powf(v1->x - v2->x, 2) + powf(v1->y - v2->y, 2));
}

/**
 * Equality comparison with tolerance for floats
 */
inline bool
close_enough(float f1, float f2)
{
    return fabs(f2 - f1) <= SLACK;
}

/**
 * Checks if a triangle is equilateral
 */
bool
is_equilateral(triangle *t)
{
    float d1_2, d2_3, d3_1;

    /* Find the distance between each pair of vertices */
    d1_2 = dist(&(t->v[0]), &(t->v[1]));
    d2_3 = dist(&(t->v[1]), &(t->v[2]));
    d3_1 = dist(&(t->v[2]), &(t->v[0]));

    /* Triangle is equilateral if all 3 distances are equal and non-zero */
    return !close_enough(d1_2, 0) && close_enough(d1_2, d2_3) && close_enough(d2_3, d3_1);
}

/**
 * Checks if two vertices are at the same point in space
 */
bool
overlap(vertex *v1, vertex *v2)
{
    return close_enough(v1->x, v2->x) && close_enough(v1->y, v2->y);
}

/**
 * Given two triangles finds the shared vertext between
 * the two triangles, if one exists. If there is more
 * than one or is no shared vertex between the two,
 * this will return NULL.
 */
vertex *
find_overlap(triangle *t1, triangle *t2)
{
    int i, j, match;

    match = -1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

            /* Check if the two vertices overlap */
            if (overlap(&t1->v[i], &t2->v[j])) {
                if (match == -1) {
                    match = i;
                } else {
                    /* If a second match is found, there is no single overlap */
                    return NULL;
                }
            }
        }
    }

    /* No overlap was found */
    if (match == -1)
        return NULL;

    return &(t1->v[match]);
}

/**
 * Ensures the following conditions are met:
 * 1. All 3 triangles are equilateral
 * 2. Each pair of triangles intersects at a single vertex
 * 3. The intersected vertices form an equilateral triangle
 */
bool
is_triforce(triangle t[3])
{
    int i;
    vertex *v;
    triangle center;

    for (i = 0; i < 3; i++) {
        if (!is_equilateral(&t[i]))
            return false;

        if ((v = find_overlap(&t[i], &t[(i+1)%3])) == NULL)
            return false;

        center.v[i].x = v->x;
        center.v[i].y = v->y;
    }

    return is_equilateral(&center);
}

int
main(int argc, char **argv)
{
    int i;
    triangle t[3];

    for (i = 0; i < 3; i++)
        scan_triangle(&t[i]);

    if (is_triforce(t))
        printf("it's a triforce!\n");
    else
        printf("no triforce here, buddy\n");

    return 0;
}
