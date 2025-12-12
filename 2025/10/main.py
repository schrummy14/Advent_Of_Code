#!/usr/bin/env python3

import numpy as np
import os
import sys
import tqdm

from scipy.optimize import LinearConstraint, milp, Bounds

def doPart1():
    print("Compile and run main.cpp to get answer to part one...")

def solveOne(line:str):
    splitLine = line.split(' ')
    buttons = splitLine[1:-1]
    target = [ float(x) for x in splitLine[-1][1:-1].split(',') ]

    # Need to solve a linear program
    # x_i = how many times button[i] was pressed
    # A = number of buttons x number of entries matrix
    # b = target
    # minimize c*x^T where c = ones(number of buttons)
    # A*x == b

    A = np.zeros((len(target), len(buttons)))
    for k, button in enumerate(buttons):
        for b in [ int(x) for x in button[1:-1].split(',')]:
            A[b,k] = 1.0

    # Need to use milp...
    integrality = np.ones(len(buttons))
    c = np.ones(len(buttons), dtype=float)
    variable_bounds = Bounds(0.0, np.inf)
    constraints = LinearConstraint(A, target, target)
    res = milp(
        c,
        integrality=integrality,
        bounds = variable_bounds,
        constraints=constraints
    )
    return int(res.fun)

def doPart2():
    dir_path = os.path.dirname(os.path.realpath(__file__))
    filename = f"{dir_path}/example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    ans = 0
    lines = open(filename, 'r').readlines()
    for line in tqdm.tqdm(lines):
        ans += solveOne(line.strip())
    print(ans)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
