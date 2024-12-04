#!/usr/bin/env python3

import sys

WORD="XMAS"
def checkSurrounding(data,k1,k2,depth,hasXmas):
    if data[k1][k2] != "X":
        return 0
    hasXmas = 0
    maxk1 = len(data)
    maxk2 = len(data[0])
    try:
        if 0 <= k1-3 < maxk1 and 0 <= k2-3 < maxk2:
            hasXmas += data[k1-1][k2-1] == "M" and data[k1-2][k2-2] == "A" and data[k1-3][k2-3] == "S"
    except IndexError:
        pass
    try:
        if 0 <= k1-3 < maxk1:
            hasXmas += data[k1-1][k2+0] == "M" and data[k1-2][k2+0] == "A" and data[k1-3][k2+0] == "S"
    except IndexError:
        pass
    try:
        if 0 <= k1-3 < maxk1 and 0 <= k2+3 < maxk2:
            hasXmas += data[k1-1][k2+1] == "M" and data[k1-2][k2+2] == "A" and data[k1-3][k2+3] == "S"
    except IndexError:
        pass
    try:
        if 0 <= k2-3 < maxk2:
            hasXmas += data[k1+0][k2-1] == "M" and data[k1+0][k2-2] == "A" and data[k1+0][k2-3] == "S"
    except IndexError:
        pass
    try:
        if 0 <= k2+3 < maxk2:
            hasXmas += data[k1+0][k2+1] == "M" and data[k1+0][k2+2] == "A" and data[k1+0][k2+3] == "S"
    except IndexError:
        pass
    try:
        if 0 <= k1+3 < maxk1 and 0 <= k2-3 < maxk2:
            hasXmas += data[k1+1][k2-1] == "M" and data[k1+2][k2-2] == "A" and data[k1+3][k2-3] == "S"
    except IndexError:
        pass
    try:
        if 0 <= k1+3 < maxk1:
            hasXmas += data[k1+1][k2+0] == "M" and data[k1+2][k2+0] == "A" and data[k1+3][k2+0] == "S"
    except IndexError:
        pass
    try:
        if 0 <= k1+3 < maxk1 and 0 <= k2+3 < maxk2:
            hasXmas += data[k1+1][k2+1] == "M" and data[k1+2][k2+2] == "A" and data[k1+3][k2+3] == "S"
    except IndexError:
        pass

    # if hasXmas:
    #     print(k1,k2,hasXmas)
    return hasXmas

def checkSurrounding2(data,k1,k2):
    if data[k1][k2] != "A":
        return 0
    hasXmas = 0
    maxk1 = len(data)
    maxk2 = len(data[0])
    if k1-1 < 0 or k1+1 >= maxk1:
        return 0
    if k2-1 < 0 or k2+1 >= maxk2:
        return 0

    check1 = 0
    check1 += data[k1-1][k2-1] == "M" and data[k1+1][k2+1] == "S"
    check1 += data[k1-1][k2-1] == "S" and data[k1+1][k2+1] == "M"

    check2 = 0
    check2 += data[k1+1][k2-1] == "M" and data[k1-1][k2+1] == "S"
    check2 += data[k1+1][k2-1] == "S" and data[k1-1][k2+1] == "M"

    if check1 and check2:
        hasXmas += 1

    # if hasXmas:
    #     print(k1,k2,hasXmas)
    return hasXmas


def hasXmas(k1,k2,d,data,N,M):
    dx = d[0]
    dy = d[1]
    for k, c in enumerate("XMAS"):
        kk1 = k1 + k*dx
        kk2 = k2 + k*dy
        if not (0 <= kk1 < N and 0 <= kk2 < M):
            return 0
        if data[kk1][kk2] != c:
            return 0
    return 1

# This is sooo much slower though...
def doPart1Clean():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        data = f.readlines()
    for k in range(len(data)):
        data[k] = data[k].strip()

    # Generate direction
    dd = []
    for d1 in range(-1,2):
        for d2 in range(-1,2):
            if d1 == 0 and d2 == 0:
                continue
            dd.append((d1,d2))

    N = len(data)
    M = len(data[0])
    numXmas = 0
    for k1 in range(N):
        for k2 in range(M):
            for d in dd:
                numXmas += hasXmas(k1,k2,d,data,N,M)
    print(numXmas)


def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        data = f.readlines()
    for k in range(len(data)):
        data[k] = data[k].strip()

    numXmas = 0
    for k1 in range(len(data)):
        for k2 in range(len(data[k1])):
            hasXmas = checkSurrounding(data,k1,k2,0,0)
            numXmas += hasXmas
    print(numXmas)

def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        data = f.readlines()
    for k in range(len(data)):
        data[k] = data[k].strip()

    numXmas = 0
    for k1 in range(len(data)):
        for k2 in range(len(data[k1])):
            hasXmas = checkSurrounding2(data,k1,k2)
            numXmas += hasXmas
    print(numXmas)

def main():
    # doPart1()
    doPart1Clean()
    doPart2()

if __name__ == "__main__":
    main()
