#!/usr/bin/env python
import random
import sys

def easy():
    P = 100
    print(P)

    for k in range(1, P+1):
        A = random.randint(0, 100)
        B = random.randint(0, A)
        print(k, A, B)

def hard():
    P = 1000
    problems = []

    for k in range(int((P-6)/2)):
        A = random.randint(0, int(10000))
        B = random.randint(0, A)
        problems.append((A, B))

    for k in range(int((P-6)/2)):
        A = random.randint(0, int(5E18))
        B = random.randint(0, A)
        problems.append((A, B))

    problems.append((0, 0))
    problems.append((0, 5E18))
    problems.append((5E18, 0))
    problems.append((5E18, 5E18))
    problems.append((0, int(5E18)-1))
    problems.append((int(5E18)-1, 1))
    random.shuffle(problems)

    print(P)
    for k, tup in enumerate(problems):
        print(k+1, int(tup[0]), int(tup[1]))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("easy or hard")
    elif sys.argv[1] == 'easy':
        easy()
    elif sys.argv[1] == 'hard':
        hard()
