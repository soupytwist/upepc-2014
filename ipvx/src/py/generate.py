#!/usr/bin/env python
import random
import sys

def easy():
    main(100, 16)

def hard():
    main(1000, 64)

def main(P, maxM):
    print(P)
    for K in range(1, P+1):
        M = random.randint(2,maxM)
        N = random.randint(1,M-1)
        print(K, M, N)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("easy or hard")
    elif sys.argv[1] == 'easy':
        easy()
    elif sys.argv[1] == 'hard':
        hard()
