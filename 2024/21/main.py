#!/usr/bin/env python3

import heapq
import sys

PAD1 = ['789', '456', '123', ' 0A']
PAD2 = [' ^A', '<v>']
START_POS = {'A': (0,2), '^': (0,1), '>': (1,2), 'v': (1,1), '<': (1,0)}

def getPad(pad:list[str], PAD:list[str]):
    r,c = pad
    if not (0<=r<len(PAD) and 0<=c<len(PAD[r])):
        return None
    if PAD[r][c]==' ':
        return None
    return PAD[r][c]

def applyPad(pad:list[str], move:str, PAD:list[str]):
    if move == 'A':
        return (pad, getPad(pad,PAD))
    elif move=='<':
        return ((pad[0], pad[1]-1), None)
    elif move=='^':
        return ((pad[0]-1, pad[1]), None)
    elif move=='>':
        return ((pad[0], pad[1]+1), None)
    elif move=='v':
        return ((pad[0]+1, pad[1]), None)

COST_MEM={}
def cost(curPos:str, lastPad:str, numPads:int):
    key = (curPos, lastPad, numPads)
    if key in COST_MEM:
        return COST_MEM[key]
    if numPads==0:
        return 1

    Q = []
    start_pos = START_POS[lastPad]
    heapq.heappush(Q, [0, start_pos, 'A', ''])
    SEEN = {}
    while Q:
        score,p,prev,out = heapq.heappop(Q)
        if getPad(p,PAD2) is None:
            continue
        if out == curPos:
            COST_MEM[key] = score
            return score
        if len(out)>0:
            continue
        seenKey = (p,prev)
        if seenKey in SEEN:
            continue
        SEEN[seenKey] = score
        for newMove in ['A', '^', '>', 'v', '<']:
            new_p, output = applyPad(p, newMove, PAD2)
            cost_move = cost(newMove, prev, numPads-1)
            new_d = score + cost_move
            new_out = out
            if output is not None:
                new_out = new_out + output
            heapq.heappush(Q, [new_d, new_p, newMove, new_out])

def solve(code:str, pads:int):
    codeInt = int(code[:-1])

    startingPosition = [0, (3,2), "A", ""]
    Q = []
    heapq.heappush(Q, startingPosition)
    SEEN = {}
    while Q:
        score,pad1,pad2,out = heapq.heappop(Q)
        if out==code:
            return score*codeInt
        if not code.startswith(out):
            continue
        if getPad(pad1, PAD1) is None:
            continue
        key = (pad1,pad2,out)
        if key in SEEN:
            continue
        SEEN[key] = score
        for move in ['A', '^', '>', 'v', '<']:
            new_out = out
            new_dp, output = applyPad(pad1, move, PAD1)
            if output is not None:
                new_out += output
            cost_move = cost(move, pad2, pads)
            heapq.heappush(Q, [score+cost_move, new_dp, move, new_out])
    return 0

def doPart1(codes:list[str]):
    ans = 0
    for code in codes:
        ans += solve(code, 2)
    print(ans)

def doPart2(codes:list[str]):
    ans = 0
    for code in codes:
        ans += solve(code, 25)
    print(ans)

def main():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    codes = open(filename).read().strip().split("\n")
    doPart1(codes)
    doPart2(codes)

if __name__ == "__main__":
    main()
