#!/usr/bin/env python3

import sys
import tqdm

def getStart(data):
    R = len(data)
    C = len(data[0])
    for r in range(R):
        for c in range(C):
            if data[r][c] in ["^",">","v","<"]:
                return r,c

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    data = []
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            data.append(list(line))

    sr,sc = getStart(data)
    data[sr][sc] = "X"

    R = len(data)
    C = len(data[0])
    numTraveled = 1
    DIR = ((-1,0),(0,1),(1,0),(0,-1))
    curDir = 0
    while True:
        if data[sr][sc] != "X":
            data[sr][sc] = "X"
            numTraveled += 1
        # Look ahead one space
        nr = sr + DIR[curDir][0]
        nc = sc + DIR[curDir][1]
        # Check if this has left the board
        if nr < 0 or nr == R or nc < 0 or nc == C:
            break
        nextSpace = data[nr][nc]
        if nextSpace == "#":
            curDir = (curDir + 1) % 4
        sr += DIR[curDir][0]
        sc += DIR[curDir][1]

    print(numTraveled)

# Combine part 1 and part 2 together as we need part 1 to get the set for part 2
def doPart2Again():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    data = []
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            data.append(line)

    sr,sc = getStart(data)

    numLoops = 0
    # Just try adding an obstacle in all possible locations???
    R = len(data)
    C = len(data[0])
    DIR = ((-1,0),(0,1),(1,0),(0,-1))

    cr = sr
    cc = sc
    curDir = 0

    # Lets use sets this time so I don't have to update the grid...
    PATH_RC = set()
    LOOP_RC = set()

    # "kinda" same as last time
    while True:
        if (cr,cc,curDir) in LOOP_RC:
            numLoops += 1
            break
        LOOP_RC.add((cr,cc,curDir))
        PATH_RC.add((cr,cc))

        nr = cr+DIR[curDir][0]
        nc = cc+DIR[curDir][1]

        if not (0 <= nr < R and 0 <= nc < C):
            break
        if data[nr][nc] == "#":
            curDir = (curDir+1)%4
        else:
            cr = nr
            cc = nc
    print(len(PATH_RC))

    for prc in tqdm.tqdm(PATH_RC):
        ob_r = prc[0]
        ob_c = prc[1]

        cr = sr
        cc = sc
        curDir = 0

        # Lets use sets this time so I don't have to update the grid...
        PATH_RC = set()
        LOOP_RC = set()

        # "kinda" same as last time
        while True:
            if (cr,cc,curDir) in LOOP_RC:
                numLoops += 1
                break
            LOOP_RC.add((cr,cc,curDir))
            PATH_RC.add((cr,cc))

            nr = cr+DIR[curDir][0]
            nc = cc+DIR[curDir][1]

            if not (0 <= nr < R and 0 <= nc < C):
                if data[ob_r][ob_c]=="#":
                    numPath = len(PATH_RC) # We can still get the part one answer...
                break
            if data[nr][nc] == "#" or (nr == ob_r and nc == ob_c):
                curDir = (curDir+1)%4
            else:
                cr = nr
                cc = nc
    print(numLoops)

def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    data = []
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            data.append(line)

    sr,sc = getStart(data)

    numLoops = 0
    # Just try adding an obstacle in all possible locations???
    R = len(data)
    C = len(data[0])
    DIR = ((-1,0),(0,1),(1,0),(0,-1))
    # Should just solve one maze without an ob and use the set of possible guard positions as the input instead...
    for ob_r in tqdm.tqdm(range(R)):
        for ob_c in range(C):
            cr = sr
            cc = sc
            curDir = 0

            # Lets use sets this time so I don't have to update the grid...
            PATH_RC = set()
            LOOP_RC = set()

            # "kinda" same as last time
            while True:
                if (cr,cc,curDir) in LOOP_RC:
                    numLoops += 1
                    break
                LOOP_RC.add((cr,cc,curDir))
                PATH_RC.add((cr,cc))

                nr = cr+DIR[curDir][0]
                nc = cc+DIR[curDir][1]

                if not (0 <= nr < R and 0 <= nc < C):
                    if data[ob_r][ob_c]=="#":
                        numPath = len(PATH_RC) # We can still get the part one answer...
                    break
                if data[nr][nc] == "#" or (nr == ob_r and nc == ob_c):
                    curDir = (curDir+1)%4
                else:
                    cr = nr
                    cc = nc
    print(numPath)
    print(numLoops)


def main():
    # doPart1()
    # doPart2()
    doPart2Again()

if __name__ == "__main__":
    main()
