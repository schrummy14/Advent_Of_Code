#!/usr/bin/env python3

import sys

def matSolve(A,b):
    det = 1./(A[0][0]*A[1][1] - A[0][1]*A[1][0])
    ia = det*A[1][1]
    ib = -det*A[0][1]
    ic = -det*A[1][0]
    id = det*A[0][0]

    return [ia*b[0] + ib*b[1], ic*b[0] + id*b[1]]

def readSolve(solveLine:str):
    vals = solveLine.split(":")[-1].split(",")
    x = int(vals[0].strip()[2:])
    y = int(vals[1].strip()[2:])
    return (x,y)

def readButton(buttonLine:str):
    vals = buttonLine.split(":")[-1].split(",")
    x = int(vals[0].strip()[2:])
    y = int(vals[1].strip()[2:])
    return (x,y)

def solveMachine(machine:list[str], isPart2:bool):
    b1 = readButton(machine[0])
    b2 = readButton(machine[1])
    solve = readSolve(machine[2])

    A = [[b1[0],b2[0]],[b1[1],b2[1]]]
    b = [isPart2*10**13+solve[0],isPart2*10**13+solve[1]]
    x = matSolve(A,b)
    x[0] = round(x[0],3)
    x[1] = round(x[1],3)
    if x[0]%1 == 0 and x[1]%1 == 0:
        minCost = int(3*x[0] + x[1])
    else:
        minCost = 0
    return minCost

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    machines = open(filename,"r").read().strip().split("\n\n")
    ans = 0
    for machine in machines:
        ans += solveMachine(machine.split("\n"), False)
    print(ans)


def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    machines = open(filename,"r").read().strip().split("\n\n")
    ans = 0
    for machine in machines:
        ans += solveMachine(machine.split("\n"), True)
    print(ans)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
