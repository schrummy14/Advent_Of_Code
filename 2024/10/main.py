#!/usr/bin/env python3

import sys

from collections import deque

# Why did I think about queues again...
def rollDown(sr,sc,GRID):
    queue = deque()
    queue.append((sr,sc))

    SEEN = set()
    R = len(GRID)
    C = len(GRID[0])
    DIR = [[-1,0],[0,1],[1,0],[0,-1]]
    ans = 0
    while queue:
        cr, cc = queue.popleft()
        if (cr,cc) in SEEN:
            continue
        SEEN.add((cr,cc))
        if GRID[cr][cc] == 9:
            ans += 1
        for dr,dc in DIR:
            nr = cr + dr
            nc = cc + dc
            if 0 <= nr < R and 0 <= nc < C and GRID[nr][nc] == GRID[cr][cc]+1:
                queue.append((nr,nc))
    return ans

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRID = open(filename,"r").read().strip().split("\n")
    GRID = [[int(x) for x in line] for line in GRID]

    R = len(GRID)
    C = len(GRID[0])
    ans = 0
    for r in range(R):
        for c in range(C):
            if GRID[r][c] != 0:
                continue
            ans += rollDown(r,c,GRID)
    print(ans)

# No more queues... even though all I had to do was remove the SEEN check....
# Recursion is more fun anyway...
def rollDown2(sr,sc,GRID):
    if GRID[sr][sc] == 0:
        return 1

    R = len(GRID)
    C = len(GRID[0])
    DIR = [[-1,0],[0,1],[1,0],[0,-1]]
    ans = 0
    for dr,dc in DIR:
        nr = sr + dr
        nc = sc + dc
        if 0 <= nr < R and 0 <= nc < C and GRID[nr][nc] == GRID[sr][sc]-1:
            ans += rollDown2(nr, nc, GRID)
    return ans

def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRID = open(filename,"r").read().strip().split("\n")
    GRID = [[int(x) for x in line] for line in GRID]

    R = len(GRID)
    C = len(GRID[0])
    ans = 0
    for r in range(R):
        for c in range(C):
            if GRID[r][c] != 9:
                continue
            ans += rollDown2(r,c,GRID)
    print(ans)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
