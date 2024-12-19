#!/usr/bin/env python3

import sys

towelArrangeMEM = {}
def towelArrange(towels:list[str], arrangement:str):
    if arrangement in towelArrangeMEM:
        return towelArrangeMEM[arrangement]
    ans = 0
    if not arrangement:
        ans = 1
    for towel in towels:
        if arrangement.startswith(towel):
            ans += towelArrange(towels, arrangement[len(towel):])
    towelArrangeMEM[arrangement] = ans
    return ans

def doPart1(towels, arrangements):
    ans = 0
    for arrangement in arrangements:
        numWays = towelArrange(towels, arrangement)
        if numWays > 0:
            ans += 1
    print(ans)

def doPart2(towels, arrangements):
    ans = 0
    for arrangement in arrangements:
        numWays = towelArrange(towels, arrangement)
        if numWays > 0:
            ans += numWays
    print(ans)

def main():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    DATA = open(filename).read().strip()
    towels, arrangements = DATA.split('\n\n')
    towels = towels.split(', ')

    arrangements = arrangements.split("\n")
    doPart1(towels, arrangements)
    doPart2(towels, arrangements)

if __name__ == "__main__":
    main()
