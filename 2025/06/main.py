#!/usr/bin/env python3

import os
import sys

def doPart1():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        data = list()
        for li in f:
            line = li.strip()
            if not line:
                continue
            data.append(line.split())

    ans = 0
    for i in range(len(data[0])):
        if data[-1][i] == '*':
            cum = 1
        else:
            cum = 0
        for k, d in enumerate(data):
            if k == len(data)-1:
                break
            if data[-1][i] == '*':
                cum *= int(d[i])
            else:
                cum += int(d[i])
        ans += cum

    print(ans)

def doPart2():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    DATA = []
    with open(filename, "r") as f:
        for line in f:
            thisLine = []
            for char in line:
                if char == '\n':
                    continue
                thisLine.append(char)
            DATA.append(thisLine)

    cur = 0
    maxCur = len(DATA[0])
    ans = 0
    done = False
    while not done:
        # Find next + or *
        nextCur = cur+1
        while True:
            if nextCur == maxCur or DATA[-1][nextCur] != ' ':
                if nextCur == maxCur:
                    done = True
                break
            nextCur +=1
        if DATA[-1][cur] == '*':
            curAns = 1
        else:
            curAns = 0
        k1 = cur
        if done:
            k2 = nextCur
        else:
            k2 = nextCur - 1
        for k in range(k1, k2):
            curVal = ""
            for i in range(0, len(DATA)-1):
                curVal += DATA[i][k]
            # print(curVal)
            if DATA[-1][cur] == '*':
                curAns *= int(curVal)
            else:
                curAns += int(curVal)
        cur = nextCur
        ans += curAns
    print(ans)



def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
