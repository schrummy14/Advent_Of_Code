#!/usr/bin/env python3

import sys
from collections import deque, defaultdict

DIRS = ((-1,0),(0,1),(1,0),(0,-1))

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRID = list()
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            GRID.append(line)
    R = len(GRID)
    C = len(GRID[0])

    REGIONS = list()
    SEEN = set()
    ans = 0
    for r in range(R):
        for c in range(C):
            if (r,c) in SEEN:
                continue
            area = 0
            perimeter = 0
            curVal = GRID[r][c]
            Q = deque()
            Q.append((r,c))
            curRegion = list()
            while Q:
                sr,sc = Q.popleft()
                if (sr,sc) not in curRegion:
                    curRegion.append((sr,sc))
                if (sr,sc) in SEEN:
                    continue
                SEEN.add((sr,sc))
                area+=1
                numNeighbors = 0
                for dir in DIRS:
                    nr = sr + dir[0]
                    nc = sc + dir[1]
                    if 0 <= nr < R and 0 <= nc < C and GRID[nr][nc] == curVal:
                        numNeighbors += 1
                        Q.append((nr,nc))
                perimeter += (4-numNeighbors)
            if len(curRegion) > 0:
                REGIONS.append(list(curRegion))
            ans += perimeter*area
    print(ans)
    return REGIONS

def doPart2(REGIONS:list[list[tuple[int,int]]]):

    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRID = list()
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            GRID.append(line)

    ans = 0
    for region in REGIONS:
        if len(region) == 1:
            ans += 4
            continue
        onEdge = set()
        neighbors = defaultdict(list)
        for sr,sc in region:
            numNeighbors = 0
            for dir in DIRS:
                if (sr+dir[0], sc+dir[1]) in region:
                    numNeighbors += 1
                    neighbors[(sr,sc)].append((sr+dir[0], sc+dir[1]))
            if numNeighbors < 4:
                onEdge.add((sr,sc))

        sides = 0
        for key in neighbors:
            numNeighbors = len(neighbors[key])
            if numNeighbors == 1:
                sides += 2
            elif numNeighbors == 2:
                # Cannot be north-south or east-west neighbors
                if ((key[0]+1, key[1]+0) in region and (key[0]-1, key[1]+0) in region) or \
                   ((key[0]+0, key[1]+1) in region and (key[0]+0, key[1]-1) in region):
                    continue
                sides += 1

        # Now need to count corners
        for key in neighbors:
            # Can be one of the four different options of the form
            # x x or x x or x 0 or 0 x
            # x 0    0 x    x x    x x
            # Where x is part of the group and 0 is not

            cr, cc = key[0], key[1]
            if (cr+0,cc+1) in region and (cr+1,cc+0) in region and (cr+1,cc+1) not in region:
                sides += 1

            if (cr+0,cc-1) in region and (cr+1,cc+0) in region and (cr+1,cc-1) not in region:
                sides += 1

            if (cr+0,cc+1) in region and (cr-1,cc+0) in region and (cr-1,cc+1) not in region:
                sides += 1

            if (cr+0,cc-1) in region and (cr-1,cc+0) in region and (cr-1,cc-1) not in region:
                sides += 1

        ans += len(region) * sides
    print(ans)

def main():
    REGIONS = doPart1()
    doPart2(REGIONS)

if __name__ == "__main__":
    main()
