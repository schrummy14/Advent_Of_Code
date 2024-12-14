#!/usr/bin/env python3

import sys

def doPart1():
    filename = "input.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    R = 103
    C = 101
    q1 = 0
    q2 = 0
    q3 = 0
    q4 = 0
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            pv = line.split(" ")
            p = [int(p) for p in pv[0].strip().split("=")[1].split(",")]
            v = [int(v) for v in pv[1].strip().split("=")[1].split(",")]

            p[0] = (p[0] + (100*v[0])%C) % C
            p[1] = (p[1] + (100*v[1])%R) % R

            # print(p)

            inQ1 = p[1] < R//2 and p[0] < C//2
            inQ2 = R//2+1 <= p[1] and p[0] < C//2
            inQ3 = p[1] < R//2 and C//2+1 <= p[0]
            inQ4 = R//2+1 <= p[1] and C//2+1 <= p[0]
            if inQ1:
                q1 += 1
            elif inQ2:
                q2 += 1
            elif inQ3:
                q3 += 1
            elif inQ4:
                q4 += 1
    print(q1,q2,q3,q4,q1*q2*q3*q4)


def doPart2():
    filename = "input.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    R = 103
    C = 101
    pos = list()
    vel = list()
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            pv = line.split(" ")
            p = [int(p) for p in pv[0].strip().split("=")[1].split(",")]
            v = [int(v) for v in pv[1].strip().split("=")[1].split(",")]
            pos.append(p)
            vel.append(v)

    count = 0
    # YOLO
    while True:
        SEEN = set()
        for p,v in zip(pos,vel):
            p[0] = (p[0] + v[0]) % C
            p[1] = (p[1] + v[1]) % R
            SEEN.add((p[0],p[1]))
        count += 1
        if len(SEEN) == len(pos):
            break
    for y in range(R):
        cStr = ""
        for x in range(C):
            if (x,y) in SEEN:
                cStr += "*"
            else:
                cStr += " "
        print(cStr)
    print(count)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
