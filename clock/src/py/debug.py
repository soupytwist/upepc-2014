#!/usr/bin/env python
from sys import stdin
from clock import lcd

def print_ascii(face):
    print(" ".join(" %s " % ('_' if lcd(0) & face[i] else ' ') for i in range(4)))
    print(" ".join("%s%s%s" % ('|' if lcd(1) & face[i] else ' ', '_' if lcd(2) & face[i] else ' ', '|' if lcd(3) & face[i] else ' ') for i in range(4)))
    print(" ".join("%s%s%s" % ('|' if lcd(4) & face[i] else ' ', '_' if lcd(5) & face[i] else ' ', '|' if lcd(6) & face[i] else ' ') for i in range(4)))

def main():
    P = int(stdin.readline().strip())

    for p in range(P):
        K, N = [int(n) for n in stdin.readline().strip().split()]
        lines = [stdin.readline().strip() for i in range(N+1)]
        clocks = [tuple(int(n) for n in line.split()) for line in lines]
        for clock in clocks:
            print_ascii(clock)

if __name__ == '__main__':
    main()
