#!/usr/bin/env python3

number2number = {
    "one":1,
    "two":2,
    "three":3,
    "four":4,
    "five":5,
    "six":6,
    "seven":7,
    "eight":8,
    "nine":9,
    "1":1,
    "2":2,
    "3":3,
    "4":4,
    "5":5,
    "6":6,
    "7":7,
    "8":8,
    "9":9,
}

def convertStringNumberToNumber(line:str):
    while True:
        for numberString in ['one','two','three','four','five','six','seven','eight','nine']:
            if numberString in line:
                k = line.find(numberString)
                line = line[:k] + str(number2number[numberString]) + line[(k+len(numberString)):]
        else:
            break
    print(line)
    return line


def getCalibrationNumber(line:str):
    firstNumber = -1
    lastNumber = -1
    for l in line:
        if l in ['1','2','3','4','5','6','7','8','9','0']:
            num = int(l)
            if firstNumber < 0:
                firstNumber = num
            lastNumber = num
    combinedNumber = 10*firstNumber + lastNumber
    print(combinedNumber)
    return combinedNumber

NUMBERS = (
    '1','2','3','4','5','6','7','8','9','0',
    'one','two','three','four','five','six','seven','eight','nine'
)
def getCalibrationNumberPart2(line:str) -> int:
    kmin = 1e6
    kmax = -1

    for number in NUMBERS:
        k = line.find(number)
        if k < 0:
            continue
        if k < kmin:
            kmin = k
            firstNumber = number
        k = line.rfind(number)
        if k > kmax:
            kmax = k
            lastNumber = number
    combinedNumber = 10*number2number[firstNumber] + number2number[lastNumber]
    return combinedNumber


def main():
    totalCalibration = 0
    with open('input.dat','r') as f:
        for l in f:
            line = l.strip()
            if not line:
                continue
            totalCalibration += getCalibrationNumberPart2(line)
    print(totalCalibration)

if __name__ == "__main__":
    main()
