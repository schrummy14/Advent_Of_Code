#!/usr/bin/env pypy3

import sys
from collections import deque

DIRS = [(-1,0),(0,1),(1,0),(0,-1)]

N = 71

def solveMaze(G):
    Q = deque([(0,0,0)])
    SEEN = set()
    while Q:
        d,r,c = Q.popleft()
        if (r,c) == (N-1,N-1):
            return d
        if (r,c) in SEEN:
            continue
        SEEN.add((r,c))
        for dr,dc in DIRS:
            rr = r+dr
            cc = c+dc
            if 0<=rr<N and 0<=cc<N and G[rr][cc] != '#':
                Q.append((d+1,rr,cc))
    return -1

def doPart1(memLocations):
    GRID = [['.' for _ in range(N)] for _ in range(N)]
    for i,line in enumerate(memLocations.split('\n')):
        x,y = [int(x) for x in line.split(',')]
        if 0<=y<N and 0<=x<N:
            GRID[y][x] = '#'
            if i==1023:
                break
    print(solveMaze(GRID))

def doPart2(memLocations):
    a = 0
    b = len(memLocations.split("\n"))-1
    while True:
        m = (a+b)//2
        GRID = [['.' for _ in range(N)] for _ in range(N)]
        for i,line in enumerate(memLocations.split('\n')):
            x,y = [int(x) for x in line.split(',')]
            if 0<=y<N and 0<=x<N:
                GRID[y][x] = '#'
                if i==m:
                    break
        dd = solveMaze(GRID)
        # print(a,m,b,dd)
        if dd < 0:
            b = m
        else:
            a = m
        if b-a == 1:
            print(memLocations.split("\n")[b])
            break

def main():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    memLocations = open(filename).read().strip()
    doPart1(memLocations)
    doPart2(memLocations)

if __name__ == "__main__":
    main()
