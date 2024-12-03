#!/usr/bin/env python3

import re
import string
import sys

def checkLine(line:str):
    runningSum = 0
    k = 0
    lineLength = len(line)
    while True:
        if k >= lineLength:
            break
        curChar = line[k]
        k+=1
        if curChar != "m":
            continue
        if line[k] != "u":
            continue
        k+=1
        if line[k] != "l":
            continue
        k+=1
        if line[k] != "(":
            continue
        k+=1

        # This is the first number up to 3 digits
        m = 0
        firstMul = ""
        while True:
            if line[k+m] in string.digits:
                firstMul += line[k+m]
                m+=1
            else:
                break
        if line[k+m] != ",":
            continue
        k+=m+1

        # Next number
        m = 0
        secondMul = ""
        while True:
            if line[k+m] in string.digits:
                secondMul += line[k+m]
                m+=1
            else:
                break

        if line[k+m] != ")":
            continue
        k+=m+1

        # We now have firstMul and secondMul values.
        # Now we need to make sure they are up to 3 digits
        if len(firstMul) > 3 or len(secondMul) > 3:
            continue

        runningSum += int(firstMul)*int(secondMul)

    return runningSum

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        runningSum = 0
        for li in f:
            line = li.strip()
            if not line:
                continue
            curSum = checkLine(line)
            runningSum += curSum
    print(runningSum)

def checkLineDoDont(line, doMul=True):
    # Guess I'll use regex...
    runningSum = 0
    captureGroups = re.findall("do\\(\\)|don't\\(\\)|mul\\(\\d+,\\d+\\)", line)

    for captureGroup in captureGroups:
        if captureGroup == "do()":
            doMul = True
        elif captureGroup == "don't()":
            doMul = False
        else:
            if doMul:
                a,b = re.findall("\\d+", captureGroup)
                x,y = int(a), int(b)
                runningSum += x*y

    return runningSum, doMul

def doPart2():
    filename = "input.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    doMul = True
    with open(filename, "r") as f:
        runningSum = 0
        for li in f:
            line = li.strip()
            if not line:
                continue
            curSum, doMul = checkLineDoDont(line, doMul)
            runningSum += curSum
    print(runningSum)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
