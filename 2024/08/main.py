#!/usr/bin/env python3

from collections import defaultdict
import sys

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
    ants = defaultdict(list)
    for r in range(R):
        for c in range(C):
            if GRID[r][c] != '.':
                ants[GRID[r][c]].append((r,c))

    # Could just check the points that could have a node...
    # but.... the grid is under 100x100...
    nodes = set()
    for key in ants:
        val = ants[key]
        for r1,c1 in val:
            for r2,c2 in val:
                if (r1,c1) == (r2,c2):
                    continue
                for r in range(R):
                    for c in range(C):
                        d1 = abs(r-r1)+abs(c-c1)
                        d2 = abs(r-r2)+abs(c-c2)

                        dr1 = r-r1
                        dr2 = r-r2
                        dc1 = c-c1
                        dc2 = c-c2

                        if (d1==2*d2 or d1*2==d2) and 0<=r<R and 0<=c<C and (dr1*dc2 == dc1*dr2):
                            nodes.add((r,c))
    print(len(nodes))


def doPart2():
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
    ants = defaultdict(list)
    for r in range(R):
        for c in range(C):
            if GRID[r][c] != '.':
                ants[GRID[r][c]].append((r,c))
    nodes = set()
    for r in range(R):
        for c in range(C):
            for key in ants:
                val = ants[key]
                for r1,c1 in val:
                    for r2,c2 in val:
                        if (r1,c1) == (r2,c2):
                            continue

                        dr1 = r-r1
                        dr2 = r-r2
                        dc1 = c-c1
                        dc2 = c-c2

                        if 0<=r<R and 0<=c<C and (dr1*dc2 == dc1*dr2):
                            nodes.add((r,c))
    print(len(nodes))

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
