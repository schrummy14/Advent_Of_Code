#!/usr/bin/env python3

import os
import sys
from collections import deque

def findAllPaths(DATA):
    ans = 0
    queue = deque(['you'])
    while len(queue) > 0:
        cur = queue.pop()
        if cur == 'out':
            ans += 1
            continue
        newPaths = DATA[cur]
        for np in newPaths:
            queue.append(np)
    return ans

def doPart1():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    DATA = {}
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            key, values = line.split(':')
            DATA[key.strip()] = [v.strip() for v in values.strip().split(' ')]
    ans = findAllPaths(DATA)
    print("Part 1:", ans)

def doPart2():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/example.dat"
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
