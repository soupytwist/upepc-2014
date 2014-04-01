#include <stdio.h>

int
main(int argc, char **argv)
{
    int P, k, M, N, junk;
    unsigned long mask, gap, end;

    scanf("%d", &P);

    for (k = 1; k <= P; k++) {
        scanf("%d %d %d", &junk, &M, &N);

        mask = M < 64 ? (1L << M) - 1L : -1L;
        gap = mask ^ (mask >> (M-N));
        end = (1L << (M-N)) - 1L;

        printf("%d", k);
        for (; gap >= end; gap >>= 1)
            printf(" %lu", mask & ~gap);
        printf("\n");
    }

    return 0;
}
