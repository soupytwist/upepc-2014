#!/usr/bin/env python
import random

def main(P):
    print(P)
    for K in range(1, P+1):
        M = random.randint(2,64)
        N = random.randint(1,M-1)
        print(K, M, N)

if __name__ == '__main__':
    main(1000)
