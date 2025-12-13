#!/usr/bin/env python3

import os
import sys

def doPart1():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/input.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    DATA = open(filename, 'r').read().split("\n\n")

    pieces = list()
    for k in range(len(DATA)-1):
        piece = list()
        for p in DATA[k].split('\n')[1:]:
            for r in p:
                if r == "#":
                    piece.append(True)
                else:
                    piece.append(False)
        pieces.append(piece)

    ans = 0
    for r in DATA[-1].split("\n"):
        line = r.strip()
        if not line:
            continue
        areaStr, numPresentsStr = line.split(':')
        a = [int(x) for x in areaStr.strip().split('x')]
        maxArea = a[0]*a[1]
        numPresents = [int(x) for x in numPresentsStr.strip().split(' ')]
        presentArea = 0
        for k, numPresent in enumerate(numPresents):
            presentArea += sum(pieces[k]*numPresent)
        if maxArea > presentArea:
            ans += 1
    print(ans)

def doPart2():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/input.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
