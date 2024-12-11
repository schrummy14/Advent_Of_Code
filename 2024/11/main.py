#!/usr/bin/env python3

import sys

csMem = {}
def countStone(stone, time):
    if (stone,time) in csMem:
        return csMem[(stone,time)]

    stoneString = str(stone)
    stoneStringLength = len(stoneString)
    if time == 0:
        return 1
    elif (stone == 0):
        ans = countStone(1, time-1)
    elif len(stoneString) % 2 == 0:
        stone1 = int(stoneString[:stoneStringLength//2])
        stone2 = int(stoneString[stoneStringLength//2:])
        ans = countStone(stone1,time-1) + countStone(stone2,time-1)
    else:
        ans = countStone(2024*stone, time-1)

    csMem[(stone,time)] = ans
    return ans

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    data = [int(x) for x in open(filename,"r").read().strip().split()]

    ans = 0
    t = 25
    for d in data:
        curAnswer = countStone(d,t)
        ans += curAnswer
    print(ans)

def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    data = [int(x) for x in open(filename,"r").read().strip().split()]

    ans = 0
    t = 75
    for d in data:
        ans += countStone(d,t)
    print(ans)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
