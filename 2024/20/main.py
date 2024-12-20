#!/usr/bin/env python3

import sys
import heapq
import tqdm
from collections import deque

DIRS = [(-1,0),(0,1),(1,0),(0,-1)]

def doPart1(): # pypy3 -> 1:11
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRID = open(filename).read().strip().split("\n")

    R = len(GRID)
    C = len(GRID[0])

    for r in range(R):
        for c in range(C):
            if GRID[r][c] == "E":
                er,ec = r,c
            if GRID[r][c] == "S":
                sr,sc = r,c

    def runOne(cheatR=-1, cheatC=-1):
        Q = []
        SEEN = set()
        heapq.heappush(Q, (0,sr,sc,1))
        DIST = {}
        best = None
        while Q:
            d,r,c,dir = heapq.heappop(Q)
            if (r,c,dir) not in DIST:
                DIST[(r,c,dir)] = d
            if r==er and c==ec and best is None:
                best = d
            if (r,c,dir) in SEEN:
                continue
            SEEN.add((r,c,dir))
            for k in [0,1,3]:
                dr,dc = DIRS[(dir+k)%4]
                rr,cc = r+dr,c+dc
                if GRID[rr][cc] != '#' or (rr==cheatR and cc==cheatC):
                    heapq.heappush(Q, (d+1, rr,cc,(dir+k)%4))
        return best

    noCheat = runOne()
    ans = 0
    for cr in tqdm.tqdm(range(1,(R-1))):
        for cc in range(1,(C-1)):
            newTime = runOne(cr,cc)
            if noCheat - newTime >= 100:
                ans+=1
    print(ans)

def doPart1Better():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRID = open(filename).read().strip().split("\n")

    R = len(GRID)
    C = len(GRID[0])

    for r in range(R):
        for c in range(C):
            if GRID[r][c] == "S":
                sr,sc = r,c

    def runOne():
        DIST = {}
        q=deque()
        q.append((sr,sc))
        DIST[(sr,sc)] = 0
        while q:
            r,c = q.popleft()
            for dr,dc in DIRS:
                rr = r+dr
                cc = c+dc
                if GRID[rr][cc] == "#":
                    continue
                if (rr,cc) in DIST:
                    continue
                DIST[(rr,cc)] = DIST[(r,c)] + 1
                q.append((rr,cc))
        return DIST

    DIST = runOne()

    ans = 0
    for r1 in range(0,R):
        for c1 in range(0,C):
            if GRID[r1][c1] == "#":
                continue
            for r2 in range(max(0, r1-2), min(R,r1+2+1)):
                for c2 in range(max(0, c1-2), min(C,c1+2+1)):
                    if GRID[r2][c2] == "#":
                        continue
                    oneNorm = abs(r2-r1) + abs(c2-c1)
                    if oneNorm > 2:
                        continue
                    if DIST[(r2,c2)] - DIST[(r1,c1)] - oneNorm >= 100:
                        ans += 1
    print(ans)

def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRID = open(filename).read().strip().split("\n")

    R = len(GRID)
    C = len(GRID[0])

    for r in range(R):
        for c in range(C):
            if GRID[r][c] == "S":
                sr,sc = r,c

    def runOne():
        DIST = {}
        q=deque()
        q.append((sr,sc))
        DIST[(sr,sc)] = 0
        while q:
            r,c = q.popleft()
            for dr,dc in DIRS:
                rr = r+dr
                cc = c+dc
                if GRID[rr][cc] == "#":
                    continue
                if (rr,cc) in DIST:
                    continue
                DIST[(rr,cc)] = DIST[(r,c)] + 1
                q.append((rr,cc))
        return DIST

    DIST = runOne()

    ans = 0
    for r1 in range(0,R):
        for c1 in range(0,C):
            if GRID[r1][c1] == "#":
                continue
            for r2 in range(max(0, r1-20), min(R,r1+20+1)):
                for c2 in range(max(0, c1-20), min(C,c1+20+1)):
                    if GRID[r2][c2] == "#":
                        continue
                    oneNorm = abs(r2-r1) + abs(c2-c1)
                    if oneNorm > 20:
                        continue
                    if DIST[(r2,c2)] - DIST[(r1,c1)] - oneNorm >= 100:
                        ans += 1
    print(ans)

def main():
    # doPart1()
    doPart1Better()
    doPart2()

if __name__ == "__main__":
    main()
