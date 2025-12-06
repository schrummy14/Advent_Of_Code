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

    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
