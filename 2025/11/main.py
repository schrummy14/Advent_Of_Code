#!/usr/bin/env python3

import os
import sys

MEMORY={}
def dfs(cur:str, hasFFT:bool, hasDAC:bool, DATA:dict[str,list[str]]):
    if (cur, hasFFT, hasDAC) in MEMORY:
        return MEMORY[(cur, hasFFT, hasDAC)]
    if cur == "out":
        if hasFFT and hasDAC:
            return 1
        else:
            return 0
    curAns = 0
    for np in DATA[cur]:
        curAns += dfs(
            np,
            hasFFT or np == "fft",
            hasDAC or np == "dac",
            DATA
        )
    MEMORY[(cur, hasFFT, hasDAC)] = curAns
    return curAns

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

    MEMORY.clear()
    ans = dfs("you", True, True, DATA)
    print("Part 1:", ans)

def doPart2():
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

    MEMORY.clear()
    ans = dfs("svr", False, False, DATA)
    print("Part 2:", ans)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
