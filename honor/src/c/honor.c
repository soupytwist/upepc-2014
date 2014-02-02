#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#define INBUFSZ 512
#define bool char
#define true 1
#define false 0

char inbuf[INBUFSZ];

typedef struct t_row_solution {
        unsigned long row;
        int count;
} row_solution;

int
main(void **args, int argc)
{
        int T, R, C;
        int t, r, c, i, j, s;

        bool *seats;
        int *linein;

        if (fgets(&(inbuf[0]), INBUFSZ-1, stdin) == NULL) {
                fprintf(stderr, "Failed to read number of trials\n");
		return -1;
        }
        sscanf(&(inbuf[0]), "%d", &T);
#ifdef DEBUG
        printf("Trials: %d\n", T);
#endif

        if (fgets(&(inbuf[0]), INBUFSZ-1, stdin) == NULL) {
                fprintf(stderr, "Failed to read data description\n");
		return -2;
        }
        sscanf(&(inbuf[0]), "%d %d %d", &t, &R, &C);
#ifdef DEBUG
        printf("%d: %d x %d\n", t, R, C);
#endif

        seats = malloc(C * sizeof(bool));
        linein = malloc((C + 1) * sizeof(int));

        for (r = 0; r < R; r++)
        {
                /* Reset the available seats */
                for (i = 0; i < C; i++)
                        seats[i] = false;

                /* Read in rows */
                if (fgets(&(inbuf[0]), INBUFSZ-1, stdin) == NULL) {
                        fprintf(stderr, "Failed to read data row\n");
                        return -3;
                }
                /* Read the number of seats in this row */
                sscanf(&(inbuf[0]), "%d", &i);
                
#ifdef DEBUG
                printf("Reading %d seats\n", i);
#endif

                while (--i >= 0) {
                        /* Read the next seat */
                        sscanf(&(inbuf[0]), "%d", &s);

#ifdef DEBUG
                        printf("Seat %d is open\n", s);
#endif

                        seats[s] = true;
                }
                
        }

        return 0;
}
