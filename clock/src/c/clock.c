#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef bool
#define bool char
#define false 0
#define true 1
#endif

#define MAXCLOCKS 11
#define LCD(x)  (1 << (x))
#define BLANK   0
#define ZERO    (LCD(0) | LCD(1) | LCD(3) | LCD(4) | LCD(5) | LCD(6))
#define ONE     (LCD(3) | LCD(6))
#define TWO     (LCD(0) | LCD(2) | LCD(3) | LCD(4) | LCD(5))
#define THREE   (LCD(0) | LCD(2) | LCD(3) | LCD(5) | LCD(6))
#define FOUR    (LCD(1) | LCD(2) | LCD(3) | LCD(6))
#define FIVE    (LCD(0) | LCD(1) | LCD(2) | LCD(5) | LCD(6))
#define SIX     (LCD(0) | LCD(1) | LCD(2) | LCD(4) | LCD(5) | LCD(6))
#define SEVEN   (LCD(0) | LCD(3) | LCD(6))
#define EIGHT   (LCD(0) | LCD(1) | LCD(2) | LCD(3) | LCD(4) | LCD(5) | LCD(6))
#define NINE    (LCD(0) | LCD(1) | LCD(2) | LCD(3) | LCD(5) | LCD(6))
#define NUMCLOCKS 12 * 60

int digits[11] = {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,BLANK};
int CLOCKS[NUMCLOCKS * 4];

void
unmask(int mask[4], int clock[4])
{
    int i;
    for (i = 0; i < 4; i++)
        mask[i] |= clock[i];
}

int
digitnum(int disp)
{
    int i;
    for (i = 0; i < 10; i++)
        if (digits[i] == disp)
            return i;
    return 0;
}

void
print_clock(int *clock)
{
    printf("%2d:%d%d\n",
        digitnum(clock[0]) * 10 + digitnum(clock[1]),
        digitnum(clock[2]), digitnum(clock[3]));
}

inline bool
check_digit(int disp, int lit, int num)
{
    return (lit & disp) == (lit & digits[num]);
    //return (lit & digits[num]) == (disp & digits[num]);
}

inline void
read_clock(int *clock)
{
    scanf("%d %d %d %d", &clock[0], &clock[1], &clock[2], &clock[3]);
}

int
main(int argc, char **argv)
{
    int clocks[MAXCLOCKS*4], lit[4];
    int P, p, K, N, n, i, *cl, *now;
    int d1, d2, d3, d4;
    int answer;
    
    i = 0;

    /* First digit can only be blank or 1 */
    for (d1 = 10; d1 != -1; d1 = (d1 == 10 ? 1 : -1)) {
        /*
         * Second digit can be 0-9 UNLESS first digit is 1,
         * in which case, it can only be 0-2.
         */
        for (d2 = (d1 == 10 ? 0 : 1); (d1 == 10 && d2 <= 9) || (d1 == 1 && d2 <= 2); d2++) {
            /* Third digit can be anything 0-5 */
            for (d3 = 0; d3 <= 5; d3++) {
                /* Fourth digit can be anything 0-9 */
                for (d4 = 0; d4 <= 9; d4++) {
                    CLOCKS[i++] = digits[d1];
                    CLOCKS[i++] = digits[d2];
                    CLOCKS[i++] = digits[d3];
                    CLOCKS[i++] = digits[d4];
                }
            }
        }
    }

    /* P: Number of data set 1 <= P <= 1000 */
    scanf("%d", &P);

    for (p = 1; p <= P; p++) {
        /* K: Data set number */
        /* N: Number of previous displays seen 1 <= N <= 10 */
        scanf("%d %d", &K, &N);

        /* Reset the lit segments we have seen */
        lit[0] = lit[1] = lit[2] = lit[3] = 0;

        /* Read in the N+1 clock faces- last clock face is the current time */
        for (n = 0; n <= N; n++) {
            cl = &clocks[n*4];
            read_clock(cl);

            /* Accumulate the lit segments */
            unmask(lit, cl);
        }

        /* Pointer to the last clock face- the current time */
        now = &clocks[N*4];
        answer = -1;

        /* Check against all possible clocks for 'now' */
        for (i = 0; i < NUMCLOCKS * 4; i += 4) {
            cl = &CLOCKS[i];

            if ((cl[0] & lit[0]) != now[0] ||
                (cl[1] & lit[1]) != now[1] || 
                (cl[2] & lit[2]) != now[2] || 
                (cl[3] & lit[3]) != now[3]) {
                continue;
            }

            if (answer == -1) {
                /* We found an answer; mark it */
                answer = i;
            } else {
                /* We found another answer; then we're not 100% certain */
                answer = -1;
                break;
            }
        }

        printf("%d ", K);
        if (answer != -1) {
            print_clock(&CLOCKS[answer]);
        } else {
            printf("?\n");
        }
    }

    return 0;
}
