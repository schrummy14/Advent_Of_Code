#!/usr/bin/env python3

from math import gcd

def getData(filename:str):
    maps = {}
    numEndWithA = 0
    with open(filename, 'r') as f:
        directionStr = f.readline().strip()
        directions = list()
        for d in directionStr:
            if d == 'L':
                directions.append(0)
            else:
                directions.append(1)
        f.readline()
        for l in f:
            line = l.strip().split('=')
            location = line[0].strip()
            ab = line[1].strip().split(',')
            a = ab[0][1:].strip()
            b = ab[1][:-1].strip()
            maps[location] = (a,b)
            if location[-1] == 'A':
                numEndWithA += 1

    print(numEndWithA)

    return directions, maps

def doPart(directions, maps):
    starts = list()
    for map in maps:
        if map[-1] == 'A':
            starts.append(map)
    # starts = ['AAA'] # Uncomment to get part 1

    numDirections = len(directions)
    timeToDone = list()
    for start in starts:
        dirCount = 0
        totCount = 0
        while True:
            start = maps[start][directions[dirCount]]
            dirCount += 1
            totCount += 1
            if start[-1] == 'Z':
                timeToDone.append(totCount)
                break
            if dirCount == numDirections:
                dirCount = 0
    print(timeToDone)
    ans = 1
    for t in timeToDone:
        ans = (t*ans)//gcd(t,ans)
    return ans

def main():
    # filename = 'example.dat'
    filename = 'input.dat'
    dirs, maps = getData(filename)
    answer = doPart(dirs, maps)
    print(answer)

if __name__ == "__main__":
    main()
