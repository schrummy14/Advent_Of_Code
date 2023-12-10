#!/usr/bin/env python3

def getNextValue(values,doPart2):
    if all([x == 0 for x in values]):
        return 0
    vv = [values[i]-values[i-1] for i in range(1, len(values))]
    if doPart2:
        return values[0] - getNextValue(vv,doPart2)
    else:
        return values[-1] + getNextValue(vv,doPart2)

def doPart_1(filename:str,doPart2=False) -> int:
    answer = 0
    with open(filename,'r') as f:
        for l in f:
            line = l.strip()
            values = [int(x) for x in line.split()]
            v = getNextValue(values,doPart2)
            answer += v
    return answer

def main():
    # filename = 'example.dat'
    filename = 'input.dat'
    answer = doPart_1(filename,False)
    print(answer)
    answer = doPart_1(filename,True)
    print(answer)

if __name__ == "__main__":
    main()
