#include <stdio.h>
#include <stdlib.h>

#ifndef bool
#define bool char
#define false 0
#define true 1
#endif

#define MAXCLOCKS 10
#define LCD(x)  (1 << (x))
#define BLANK   0
#define ZERO    LCD(0) | LCD(1) | LCD(3) | LCD(4) | LCD(5) | LCD(6)
#define ONE     LCD(3) | LCD(6)
#define TWO     LCD(0) | LCD(2) | LCD(3) | LCD(4) | LCD(5) | LCD(6)
#define THREE   LCD(0) | LCD(2) | LCD(3) | LCD(5) | LCD(6)
#define FOUR    LCD(0) | LCD(1) | LCD(2) | LCD(3) | LCD(6)
#define FIVE    LCD(0) | LCD(1) | LCD(2) | LCD(5) | LCD(6)
#define SIX     LCD(0) | LCD(1) | LCD(2) | LCD(4) | LCD(5) | LCD(6)
#define SEVEN   LCD(0) | LCD(3) | LCD(6)
#define EIGHT   LCD(0) | LCD(1) | LCD(2) | LCD(3) | LCD(4) | LCD(5) | LCD(6)
#define NINE    LCD(0) | LCD(1) | LCD(2) | LCD(3) | LCD(5) | LCD(6)

int digits[11] = {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,BLANK};

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
print_clock(int clock[4])
{
    printf("%d:%d%d\n",
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
    int clocks[MAXCLOCKS*4], lit[4] = {0,0,0,0};
    int P, p, i, d, *cl, *now;
    bool *possible[4], certain;
    int counts[4], known[4];

    for (i = 0; i < 4; i++)
        possible[i] = malloc(10 * sizeof(bool));

    for (d = 0; d < 10; d++) {
        printf("Digit %d  -->  %d\n", d, digits[d]);
        possible[0][d] = d < 2;
        possible[1][d] = possible[3][d] = true;
        possible[2][d] = d < 6;
    }

    for (i = 0; i < 4; i++) {
        possible[i][10] = i == 0;
    }
    
    P = 3;

    for (p = 0; p < P; p++) {
        cl = &clocks[p*4];
        read_clock(cl);
        print_clock(cl);
        unmask(lit, cl);
        print_clock(lit);
    }

    now = &clocks[(P-1)*4];

    for (i = 0; i < 4; i++) {
        counts[i] = 0;
        for (d = 0; d <= 10; d++) {
            possible[i][d] &= check_digit(now[i], lit[i], d);
            if (possible[i][d]) {
                counts[i]++;
                printf("%d digit can be %d\n", i, d);
            }
        }
    }

    /* If the second digit can only be zero then the first digit must be 1 */
    if (counts[1] == 1 && possible[1][0]) {
        printf("1 digit can only be zero, 0 digit must be 1\n");
        possible[0][0] = false;
        possible[0][10] = false;
        counts[0] = 1;
    }

    certain = true;
    for (i = 0; i < 4; i++) {
        if (counts[i] != 1) {
            printf("Not certain about %d digit\n", i);
            certain = false;
            break;
        }
    }

    if (certain) {
        for (i = 0; i < 4; i++) {
            for (d = 0; d <= 10; d++) {
                if (possible[i][d])
                    known[i] = digits[d];
            }
        }
        print_clock(known);

    } else {
        printf("?");
    }

    return 0;
}
