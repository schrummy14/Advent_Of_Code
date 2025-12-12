#!/usr/bin/env python3

import os
import sys

def doPart1():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue

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
