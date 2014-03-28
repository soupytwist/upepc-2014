#!/usr/bin/env python
from clock import find_time
from sys import stdin

def main():
    P = int(stdin.readline().strip())

    for p in range(P):
        K, N = [int(n) for n in stdin.readline().strip().split()]
        lines = [stdin.readline().strip() for i in range(N+1)]
        clocks = [tuple(int(n) for n in line.split()) for line in lines]
        print("%d %s" % (K, find_time(clocks)))

if __name__ == '__main__':
    main()
