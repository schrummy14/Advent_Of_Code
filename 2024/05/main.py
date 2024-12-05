#!/usr/bin/env python3

# Let's try to get rid of defaultdict and deque and use a sorting algo???
# https://github.com/womogenes/AoC-2024-Solutions/blob/main/day_05/p2_day_05_v2.py

from collections import defaultdict, deque
import time
import sys

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    rules = []
    data = []

    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            if "|" in line:
                rules.append(line.split("|"))
            else:
                data.append(line.split(','))
    ruleMap = dict()
    for rule in rules:
        a,b = rule[0], rule[1]
        if b not in ruleMap:
            ruleMap[b] = list()
        ruleMap[b].append(a)

    runningSum = 0
    for line in data:
        isValid = True
        for k in range(len(line)):
            curChar = line[k]
            valsToCheck = ruleMap.get(curChar,None)
            valsToBeCheckedAgainst = line[k:]
            if valsToCheck is None:
                continue
            for vtc in valsToCheck:
                if vtc in valsToBeCheckedAgainst:
                    isValid = False
                    break
            if not isValid:
                break
        if isValid:
            runningSum += int(line[len(line)//2])
    print(runningSum)

def fixLine(line:list[str], ruleMapF, ruleMapB) -> list[str]:
    newLine = []
    goodQueue = deque([])
    numCheckEntries = dict()
    for val in line:
        numCheckEntries[val] = len(ruleMapF[val] & set(line))
    for val in line:
        if numCheckEntries[val] == 0:
            goodQueue.append(val)
    while goodQueue:
        val = goodQueue.popleft()
        newLine.append(val) # newLine is going to be built backwards
        for checkVal in ruleMapB[val]:
            if checkVal in numCheckEntries:
                numCheckEntries[checkVal] -= 1
                if numCheckEntries[checkVal] == 0:
                    goodQueue.append(checkVal)

    newLine.reverse()
    return newLine

def usingQueue(data, rules):
    ruleMapForward = defaultdict(set)
    ruleMapBackward = defaultdict(set)
    for rule in rules:
        a,b = rule[0], rule[1]
        ruleMapForward[a].add(b)
        ruleMapBackward[b].add(a)

    runningSum = 0
    for line in data:
        isValid = True
        for k in range(len(line)):
            curChar = line[k]
            valsToCheck = ruleMapBackward[curChar]
            valsToBeCheckedAgainst = line[k:]
            if valsToCheck is None:
                continue
            for vtc in valsToCheck:
                if vtc in valsToBeCheckedAgainst:
                    isValid = False
                    break
            if not isValid:
                break
        if not isValid:
            newLine = fixLine(line, ruleMapForward, ruleMapBackward)
            runningSum += int(newLine[len(line)//2])
    print(runningSum)

def usingSort(data,rules):
    runningSum = 0
    for line in data:
        was_sorted = True
        while True:
            is_sorted = True
            for k in range(1,len(line)):
                if [line[k],line[k-1]] in rules:
                    is_sorted = False
                    was_sorted = False
                    line[k-1],line[k] = line[k], line[k-1]
            if is_sorted:
                break
        if not was_sorted:
            runningSum += int(line[len(line)//2])
    print(runningSum)

def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    rules = []
    data = []

    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            if "|" in line:
                rules.append(line.split("|"))
            else:
                data.append(line.split(','))

    # start = time.time()
    # usingQueue(data,rules)
    # print(f"Time to use a queue: {time.time()-start:0.3e}")
    start = time.time()
    usingSort(data,rules)
    print(f"Time to use a sort: {time.time()-start:0.3e}")

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
