#!/usr/bin/env python3

import sys

def isValid(target:int, vals:list[int]):
    if len(vals) == 1:
        return target == vals[0]
    if isValid(target, [vals[0]+vals[1]] + vals[2:]):
        return True
    if isValid(target, [vals[0]*vals[1]] + vals[2:]):
        return True
    return False

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    runningSum = 0
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            target = int(line.split(":")[0])
            vals = [int(x) for x in line.split(":")[1].split()]
            if isValid(target, vals):
                runningSum += target
    print(runningSum)

def isValid2(target:int, vals:list[int]):
    if len(vals) == 1:
        return target == vals[0]
    if isValid2(target, [vals[0]+vals[1]] + vals[2:]):
        return True
    if isValid2(target, [vals[0]*vals[1]] + vals[2:]):
        return True
    if isValid2(target, [int(str(vals[0])+str(vals[1]))] + vals[2:]):
        return True
    return False

def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    runningSum = 0
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            target = int(line.split(":")[0])
            vals = [int(x) for x in line.split(":")[1].split()]
            if isValid2(target, vals):
                runningSum += target
    print(runningSum)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
