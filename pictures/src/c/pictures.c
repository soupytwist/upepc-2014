/*
 * UPEPC 2014 - E. Picture Day
 * Author: Nick Smith
 */
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX_S 20
#ifndef bool
#define bool char
#define false 0
#define true 1
#endif

int D[MAX_S * MAX_S];
bool used[MAX_S];

/**
 * Save the (hamming) distance between two shots
 */
void
setval(int from, int to, int w)
{
    /* Assume from < to */
    D[from * MAX_S + to] = w;
}

/**
 * The (hamming) distance between two shots
 */
int
dist(int l, int r)
{
    /* Distance to select first nodes is 0 */
    if (l == -1 || r == -1)
        return 0;

    /* Use the smaller of l, r for indexing */
    return l < r ? D[l * MAX_S + r] : D[r * MAX_S + l];
}

/**
 * Finds the first index at or after o that is
 * not marked as used.
 */
int
next_unused(int o, int n)
{
    for (; o < n; o++)
        if (used[o] == false) return o;
    return -1;
}

/**
 * Recursively solve the all-nodes ASP problem.
 * This is really an optimized verion of the TSP.
 * See https://en.wikipedia.org/wiki/Travelling_salesman_problem
 */
int
solve(int l, int r, int n, int rem)
{
    int i, j, dli, dlj, dri, drj, result, step;

    /* Check the base cases */
    if (rem == 0) {
        /* No remaining nodes, distance directly from l to r */
        return dist(l,r);

    } else if (rem == 1) {
        /*
         * Return the distance from l to r with the remaining
         * node as an intermediatry.
         */
        i = next_unused(0, n);
        return dist(l,i) + dist(i,r);
    }
    
    /*
     * There is no current path, so set the current
     * distance to an unreachably high value.
     */
    result = MAX_S * MAX_S;

    /* Iterate through the unused words which will begin the path */
    for (i = next_unused(0,n); i != -1; i = next_unused(i+1,n)) {

        /* Distances between both ends and the first word */
        dli = dist(l,i);
        dri = dist(r,i);

        /* Mark the word as used so we don't select it twice */
        used[i] = true;

        /* Iterate through the unused words which will end the path */
        for (j = next_unused(i+1,n); j != -1; j = next_unused(j+1,n)) {

            /* Distances between both ends and the second word */
            dlj = dist(l,j);
            drj = dist(r,j);

            /* Mark the second word as used so we don't select it twice */
            used[j] = true;

            /* 
             * Recursive step:
             * Now that we have selected two nodes, these will serve as
             * the two endpoints for the middle section of the path.
             * Now, the two words selected by the loops, i and j, are used
             * as the two outermost nodes in a path of length rem.
             *
             * Being as the outermost nodes are picked first, we can
             * arbitrarily flip the inner segment i...j based on the
             * values of the distances from the selected outer nodes.
             *
             * < ... (l)-dli-(i)- ... -(j)-drj-(r) ... >
             * < ... (l)-dlj-(j)- ... -(i)-dri-(r) ... >
             */
            step = MIN(dli + drj, dlj + dri) + solve(i,j,n,rem-2);

            /*
             * If the distance from l to r using i and j as the next
             * outermost nodes is minimal, save the result.
             */
            result = MIN(step, result);

            /* Mark the second word as unused so it may be selected again */
            used[j] = false;
        }
        
        /* Mark the first word as unused so it may be selected again */
        used[i] = false;
    }

    return result;
}

/**
 * Compute the Hamming distance between two strings
 * This is equivalent to the number of characters that
 * differ between the two strings.
 * e.g: hamming("hello", "jello") --> 1
 *
 * See https://en.wikipedia.org/wiki/Hamming_distance
 */
int
hamming(char *a, char *b)
{
    int d = 0;
    while (*a != '\0')
        if (*(a++) != *(b++)) d++;
    return d;
}

int
main(int argc, char **argv)
{
    int P, p, K, S, s, z, E;
    char *shots[MAX_S];

    /* P: Number of data sets 1 <= P <= 100 */
    scanf("%d", &P);

    for (p = 1; p <= P; p++) {

        /*
         * K: Data set number
         * S: Number of photos 2 <= S <= 12
         * E: Number of employees 1 <= E <= 100
         */
        scanf("%d %d %d", &K, &S, &E);

        /* Read S strings of length E into a buffer */
        for (s = 0; s < S; s++) {
            shots[s] = malloc((E+1)*sizeof(char));
            scanf("%s", shots[s]);
        }

        /* Initialization  */
        for (s = 0; s < S; s++) {
            /* Mark each shot as unused */
            used[s] = false;

            /* Compute the hamming distance between each pair of shots */
            for (z = s+1; z < S; z++)
                setval(s, z, hamming(shots[s], shots[z]));

            /* Once we have the hamming distances, discard the string */
            free(shots[s]);
        }

        /* 
         * Compute the result.
         * This uses parameters l = -1 and r = -1 to indicate
         * that no shots are chosen yet for first and last.
         */
        printf("%d %d\n", K, solve(-1, -1, S, S));
    }

    return 0;
}
