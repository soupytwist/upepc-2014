#!/usr/bin/env python
import random
import string
import sys

def hardness(h):
    numemps = int(random.expovariate(1/24))
    numemps = min(99, max(numemps,0)) + 1
    numcolors = int(random.expovariate(1/6))
    numcolors = min(15, max(numcolors,1)) + 1
    return (h, numemps, numcolors)

def shot(colors, numemps):
    return "".join([random.choice(colors) for i in range(numemps)])

def trial(h):
    numshots, numemps, numcolors = hardness(h)
    colors = random.sample(string.ascii_lowercase, numcolors)
    shots = [shot(colors, numemps) for i in range(numshots)]
    return {
        "S": numshots,
        "E": numemps,
        "shots": shots,
    }

def easy():
    levels = list(range(2,7)) * 5
    random.shuffle(levels)
    trials = [trial(h) for h in levels]
    
    print(len(trials))
    for i, t in enumerate(trials):
        print("%d %d %d" % (i+1, t['S'], t['E']))
        for s in t['shots']:
            print(s)
def hard():
    levels = list(range(2,4)) * 4    \
           + list(range(5,11)) * 14  \
           + [12] * 8 
    random.shuffle(levels)
    trials = [trial(h) for h in levels]
    
    print(len(trials))
    for i, t in enumerate(trials):
        print("%d %d %d" % (i+1, t['S'], t['E']))
        for s in t['shots']:
            print(s)

if __name__ == "__main__":
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
