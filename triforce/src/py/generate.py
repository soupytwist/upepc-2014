#!/usr/bin/env python
import random
import math
import sys

def triangle(x, y):
    coords = [
        (x - 1, y),
        (x + 1, y),
        (x, y + math.sqrt(3)),
    ]
    random.shuffle(coords)
    return coords
    
def transform(vertices):
    scalefactor = random.randint(1, 1000)
    shiftx = (random.random() - 0.5) * 2000 + 1
    shifty = (random.random() - 0.5) * 2000 + 1
    rotation = random.random() * math.pi * 2

    sin = math.sin(rotation)
    cos = math.cos(rotation)
    return [((cos*x + sin*y)*scalefactor + shiftx, (sin*x + cos*y)*scalefactor + shifty) for x, y in vertices]

def generate_triangles():
    triangles = [\
        triangle(random.random() - 0.5, random.random() - 0.5),
        triangle(random.random() - 0.5, random.random() - 0.5),
        triangle(random.random() - 0.5, random.random() - 0.5),
    ]
    random.shuffle(triangles)
    vertices = sum(triangles, [])
    return transform(vertices)

def generate_equilaterals():
    triangles = [\
        triangle(0, 0),
        triangle(0, 0),
        triangle(0, 0),
    ]
    vertices = sum(triangles, [])
    return transform(vertices[:3]) + transform(vertices[3:6]) + transform(vertices[6:])

def generate_triforce():
    triangles = [\
        triangle(0, 0),
        triangle(-1, math.sqrt(3)),
        triangle(-1, -1 * math.sqrt(3)),
    ]
    random.shuffle(triangles)
    vertices = sum(triangles, [])
    return transform(vertices)

def generate_trapezoid():
    triangles = [\
        triangle(0, 0),
        triangle(0, 0),
        triangle(-1, -1 * math.sqrt(3)),
    ]
    vertices = sum(triangles, [])
    vertices = [(x, -y) for x, y in vertices[:3]] + vertices[3:]
    return transform(vertices)

def easy():
    numvalid = random.randint(50, 70)
    valid = [generate_triforce() for i in range(numvalid)]
    invalid = [generate_triangles() for i in range(10)] + \
              [generate_trapezoid() for i in range(10)] + \
              [generate_equilaterals() for i in range(10)]

    shapes = valid + invalid

    for p, tri in enumerate(shapes):
        print(p+1)
        for v in tri:
            print("%.2f %.2f" % v)

def hard():
    pass

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("easy or hard")
    elif sys.argv[1] == 'easy':
        easy()
    elif sys.argv[1] == 'hard':
        hard()
