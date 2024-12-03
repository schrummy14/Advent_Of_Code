#!/usr/bin/env python3

import sys

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue

def doPart2():
    filename = "example.dat"
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
