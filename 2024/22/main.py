#!/usr/bin/env python3

import sys

def mix(a,b):
    return a^b

def prune(x):
    return x % 16777216

def doPart1(numbers:list[int]):
    ans = 0
    for number in numbers:
        for _ in range(2000):
            number = prune(mix(number, 64*number))
            number = prune(mix(number, number//32))
            number = prune(mix(number, number*2048))
        ans += number
    print(ans)

def getSequences(prices, dp):
    sequences = {}
    for k in range(len(dp)-3):
        key = (dp[k],dp[k+1],dp[k+2],dp[k+3])
        if key not in sequences:
            sequences[key] = prices[k+4]
    return sequences

def doPart2(numbers):
    ANS = {}
    for number in numbers:
        prices = [number%10]
        for _ in range(2000):
            number = prune(mix(number, 64*number))
            number = prune(mix(number, number//32))
            number = prune(mix(number, number*2048))
            prices.append(number%10)
        dp = [prices[k+1]-prices[k] for k in range(len(prices)-1)]
        sequences = getSequences(prices, dp)
        for k,v in sequences.items():
            if k not in ANS:
                ANS[k] = v
            else:
                ANS[k] += v
    print(max(ANS.values()))

def main():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    numbers = list()
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            numbers.append(int(line))
    doPart1(numbers)
    doPart2(numbers)

if __name__ == "__main__":
    main()
