#!/usr/bin/env python
from clock import CLOCKS, SEGMENTS, powerset, mergebits, unmergeclocks
import random
import math

NUM_DATA_SETS = 1000

def main():
    print(NUM_DATA_SETS)
    for K in range(1, NUM_DATA_SETS + 1):
        N = random.randint(1, 10)
        print("%d %d" % (K, N))
        clocks = random.sample(CLOCKS, N+1)

        off = tuple(mergebits(random.sample(SEGMENTS, random.randint(0,2))) for i in range(4))
        displays = [unmergeclocks(clock, off) for clock in clocks]
        for display in displays:
            print(" ".join(str(d) for d in display))

if __name__ == '__main__':
    main()
