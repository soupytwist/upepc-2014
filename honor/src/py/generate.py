#!/usr/bin/env python
import random
import math
import sys
import os

def classroom(R, C, broken_ct=0):
    if broken_ct == 0:
        broken_ct = random.randint(0, R * C)

    broken = sorted(random.sample(range(R * C), broken_ct))
    res = []
    
    for row in range(R):
        br_row = [x % C for x in broken if x >= row*C and x < (row+1)*C]
        res.append([len(br_row)] + br_row)

    return (C, res)

def columns_striped(R, C):
    row = list(range(random.randint(0,1), C, 2))
    return (C, [[len(row)] + row] * R)

def rows_striped(R, C):
    pair = [[0], [C] + list(range(C))]
    res = pair * (R//2)
    if R % 2 == 0:
        res += [[0]]
    return (C, res)

def checkerboard(R, C):
    pair = [[C//2] + list(range(1, C, 2)), [(C+1)//2] + list(range(0, C, 2))]
    res = pair * (R//2)
    if R % 2 == 0:
        res += [[C//2] + list(range(1, C, 2))]
    return (C, res)

def printall(problems, **printkwargs):
    print(len(problems), **printkwargs)
    for i, roomtup in enumerate(problems):
        C, rows = roomtup
        print(i+1, len(rows), C, **printkwargs)
        for row in rows:
            print(" ".join([str(d) for d in row]), **printkwargs)

def easy():
    rooms = [classroom(random.randint(1, 6), random.randint(1, 10)) for i in range(50)]
    printall(rooms)

def hard(outputdir, howmany):
    rooms = [classroom(random.randint(1, 500), (i % 6)+1) for i in range(700)]\
          + [classroom(random.randint(300, 400), (i % 3)+8) for i in range(100)]\
          + [classroom(random.randint(900, 1000), (i % 4)+2) for i in range(50)]\
          + [columns_striped(random.randint(150, 200), (i%5)+2) for i in range(50)]\
          + [rows_striped(random.randint(150, 200), (i%5)+2) for i in range(50)]\
          + [checkerboard(random.randint(150, 200), (i%5)+2) for i in range(50)]

    for i in range(howmany):
        random.shuffle(rooms)
        path = os.path.join(outputdir, "large-" + str(i) + ".in")
        print(path)
        with open(path, "w") as f:
            printall(rooms, file=f)

if __name__ == '__main__':
    if sys.argv[1] == 'easy':
        easy()
    elif sys.argv[1] == 'hard':
        if len(sys.argv) != 4:
            print("hard requires args <outputdir> and <howmany>")
            sys.exit(1)
        hard(sys.argv[2], int(sys.argv[3]))
    else:
        print("easy or hard, please" % (sys.argv[1]))
        sys.exit(1)
