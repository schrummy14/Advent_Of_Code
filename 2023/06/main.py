#!/usr/bin/env python3
import math

def getData_1(filename:str):
    data = {'time': [], 'distance': []}
    with open(filename, 'r') as f:
        times = list(map(int, f.readline().strip().split(':')[1].split()))
        distances = list(map(int, f.readline().strip().split(':')[1].split()))
    data['time'] = times
    data['distance'] = distances
    return data

def getData_2(filename:str):
    data = []
    with open(filename,'r') as f:
        data.append(int(f.readline().strip().split(':')[1].replace(' ', '')))
        data.append(int(f.readline().strip().split(':')[1].replace(' ', '')))
    return data

def getSolutions(t,d):
    a,b,c = 1,-t,d
    x1 = int((-b + math.sqrt(b*b - 4*a*c))/(2*a) - 0.1)
    x2 = int((-b - math.sqrt(b*b - 4*a*c))/(2*a) + 1.1)
    return x1,x2

def doPart_1(data):
    answer = 1
    for t,d in zip(data['time'], data['distance']):
        x1, x2 = getSolutions(t, d)
        curAns = 1 + x1-x2
        answer *= curAns
    return answer

def doPart_2(data):
    x1, x2 = getSolutions(data[0], data[1])
    curAns = 1 + x1-x2
    return curAns

def main():
    # filename = 'example.dat'
    filename = 'input.dat'
    answer = doPart_1(getData_1(filename))
    print(answer)
    answer = doPart_2(getData_2(filename))
    print(answer)

if __name__ == "__main__":
    main()
