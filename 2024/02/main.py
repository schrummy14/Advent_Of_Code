#!/usr/bin/env python3

import sys

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
            sLine = line.split()
            lastVal = -1
            isSafe = 0
            isPos = 0
            isNeg = 0
            canRemove = 0
            for cStr in sLine:
                val = int(cStr)
                if lastVal < 0:
                    lastVal = val
                    continue
                if val - lastVal > 0:
                    isPos = 1
                else:
                    isNeg = 1
                if isPos and isNeg:
                    if canRemove:
                        canRemove = 0
                    else:
                        break
                if (isPos):
                    a = lastVal
                    b = val
                else:
                    a = val
                    b = lastVal
                lastVal = val
                if (b-a > 3 or b==a):
                    if canRemove:
                        canRemove = 0
                    else:
                        break
            else:
                isSafe = 1
            runningSum += isSafe
        print(runningSum)

def checkSafe(sLine:list[str]) -> int:
    lastVal = -1
    isPos = 0
    isNeg = 0
    for cStr in sLine:
        val = int(cStr)
        if lastVal < 0:
            lastVal = val
            continue
        if val - lastVal > 0:
            isPos = 1
        elif val - lastVal < 0:
            isNeg = 1
        else:
            return 0
        if isPos and isNeg:
            return 0
        if (isPos):
            a = lastVal
            b = val
        else:
            a = val
            b = lastVal
        if (b-a > 3 or b==a):
            return 0
        lastVal = val

    return 1


def isSafeFun(sLine:list[str]):
    # Check if the original list is safe
    isSafe = checkSafe(sLine)
    if isSafe:
        return 1
    for k in range(len(sLine)):
        nLine = sLine[:k] + sLine[(k+1):]
        isSafe = checkSafe(nLine)
        if isSafe:
            return 1
    return 0


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
            sLine = line.split()
            isSafe = isSafeFun(sLine)
            runningSum += isSafe
        print(runningSum)

def main():
    doPart1()
    doPart2()


if __name__ == "__main__":
    main()
