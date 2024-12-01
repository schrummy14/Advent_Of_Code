#!/usr/bin/env python3

import sys

def doPart1():
    if len(sys.argv) < 2:
        filename = "example.dat"
    else:
        filename = sys.argv[1].strip()
    l1 = list()
    l2 = list()
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            sLine = line.split()
            l1.append(int(sLine[0]))
            l2.append(int(sLine[1]))

    # Sort the two lists
    l1.sort()
    l2.sort()
    runningSum = 0
    for a,b in zip(l1,l2):
        runningSum += abs(a-b)
    print(runningSum)


def doPart2():
    if len(sys.argv) < 2:
        filename = "example.dat"
    else:
        filename = sys.argv[1].strip()
    l1 = list()
    l2 = list()
    ls = dict()
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            sLine = line.split()
            a,b = int(sLine[0]),int(sLine[1])
            if a not in ls:
                ls[a] = 0
            l1.append(a)
            l2.append(b)
    for value in l2:
        if value not in ls:
            continue
        ls[value] += 1

    runningSum = 0
    for key in l1:
        runningSum += key*ls[key]
    print(runningSum)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
