#!/usr/bin/env python
from clock import CLOCKS, SEGMENTS, powerset, mergebits, unmergeclocks
import random
import math
import sys

def easy():
    main(100, 5)

def hard():
    main(1000, 10)

def main(datasets, maxclocks):
    print(datasets)
    for K in range(1, datasets + 1):
        N = random.randint(2, maxclocks)
        print("%d %d" % (K, N))
        clocks = random.sample(CLOCKS, N)

        off = tuple(mergebits(random.sample(SEGMENTS, random.randint(0,2))) for i in range(4))
        displays = [unmergeclocks(clock, off) for clock in clocks]
        for display in displays:
            print(" ".join(str(d) for d in display))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("missing argument")
        sys.exit(1)

    if sys.argv[1] == 'easy':
        easy()
    elif sys.argv[1] == 'hard':
        hard()
    else:
        print("unknown argument: %s" % (sys.argv[1]))
        sys.exit(1)
