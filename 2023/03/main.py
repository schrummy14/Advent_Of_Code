#!/usr/bin/env python3

import numpy as np
import typing
import tqdm

NUMBERS = (
    '1','2','3','4','5','6','7','8','9','0',
    'one','two','three','four','five','six','seven','eight','nine'
)

def getSchematic(filename:str):
    with open(filename, 'r') as f:
        lines = f.readlines()
    data = list()
    numCols = len(lines[0])-1 + 2
    data.append(numCols*'.')
    for l in lines:
        data.append(f".{l.strip()}.")
    data.append(numCols*'.')
    return data

def partOne(data:typing.List[str]) -> typing.List[int]:
    validNumbers:typing.List[int] = list()

    posNumber = ""
    isValidNumber = False
    for k1 in tqdm.tqdm(range(1,len(data)-1)):
        for k2 in range(1,len(data[0])-1):
            curChar = data[k1][k2]
            if curChar == '.':
                posNumber = ""
                isValidNumber = False
                continue
            if curChar not in NUMBERS:
                posNumber = ""
                isValidNumber = False
                continue
            posNumber += curChar

            # Need to check around this char for a symbol
            for k3 in [-1,0,1]:
                for k4 in [-1,0,1]:
                    symbolChar = data[k1+k3][k2+k4]
                    if symbolChar not in NUMBERS and symbolChar not in ['.']:
                        isValidNumber = True
                        break
            if data[k1][k2+1] not in NUMBERS and isValidNumber:
                validNumbers.append(int(posNumber))
    return validNumbers

def partTwo(data:typing.List[str]) -> typing.List[int]:
    validNumbers:typing.List[int] = list()
    for k1 in tqdm.tqdm(range(1,len(data)-1)):
        for k2 in range(1,len(data[0])-1):
            curChar = data[k1][k2]
            if curChar not in ['*']:
                continue
            numbers = findNumbersAroundStar(data,k1,k2)
            if len(numbers) == 2:
                validNumbers.append(numbers)
    return validNumbers

def findNumbersAroundStar(data:typing.List[str], k1:int, k2:int) -> typing.List[int]:
    numbers:typing.List[int] = list()
    for k3 in [-1,0,1]:
        for k4 in [-1,0,1]:
            curChar = data[k1+k3][k2+k4]
            if curChar not in NUMBERS:
                continue
            number = int(growNumber(data,k1,k2,k3,k4))
            if number not in numbers:
                numbers.append(number)
    return numbers

def growNumber(data:typing.List[str], k1:int, k2:int, k3:int, k4:int) -> int:
    number = data[k1+k3][k2+k4]
    k = 1
    notDone = True
    validLeft = True
    validRight = True
    while notDone:
        notDone = False
        if validLeft and data[k1+k3][k2+k4-k] in NUMBERS:
            notDone = True
            number = data[k1+k3][k2+k4-k] + number
        else:
            validLeft = False

        if validRight and data[k1+k3][k2+k4+k] in NUMBERS:
            notDone = True
            number = number + data[k1+k3][k2+k4+k]
        else:
            validRight = False

        k+=1

    return number

def main():
    # data = getSchematic('example.dat')
    data = getSchematic('input.dat')
    # validNumbers = partOne(data)
    validNumbers = partTwo(data)
    validNumberSum = 0
    for n in validNumbers:
        validNumberSum += n[0]*n[1]
    print(validNumberSum)


if __name__ == "__main__":
    main()
