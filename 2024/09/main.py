#!/usr/bin/env pypy3

import sys

def doPart1():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    BLOCK = list()
    SPACE = list()
    data = open(filename, "r").readline().strip()
    for k,val in enumerate(data):
        if k % 2 == 0:
            BLOCK.append(int(val))
        else:
            SPACE.append(int(val))

    fileId = 0

    # Start building the new list
    val = list()
    for _ in range(BLOCK[0]):
        val.append(fileId)
    for k in range(len(SPACE)):
        for _ in range(SPACE[k]):
            val.append(None)
        for _ in range(BLOCK[k+1]):
            val.append(k+1)

    # Now we can sort
    p1 = 0
    p2 = len(val)-1
    while True:
        # Find the next None item
        while val[p1] is not None:
            p1+=1
        while val[p2] is None:
            p2 -=1
        if not (p1 < p2):
            break
        # Swap the values
        val[p1] = val[p2]
        val[p2] = None

    k = 0
    ans = 0
    while val[k] is not None:
        ans += (k+0)*val[k]
        k+=1
    print(ans)


def doPart2():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    BLOCK = list()
    SPACE = list()
    data = open(filename, "r").readline().strip()
    for k,val in enumerate(data):
        if k % 2 == 0:
            BLOCK.append(int(val))
        else:
            SPACE.append(int(val))

    fileId = 0

    # Start building the new list
    val = list()
    for _ in range(BLOCK[0]):
        val.append(fileId)
    for k in range(len(SPACE)):
        for _ in range(SPACE[k]):
            val.append(None)
        for _ in range(BLOCK[k+1]):
            val.append(k+1)

    # Now we can sort
    # Need to move whole files, if they can
    # If not, skip it...
    p1=0
    p2=len(val)-1
    p1Org = 0
    while True:
        p1=p1Org
        while val[p1] is not None:
            p1+=1
        p1Org = p1 # Cuts the time in half...
        while val[p2] is None:
            p2-=1
        if not (p1 < p2):
            break

        # Get the file size of the next file
        fileSize = 0
        while val[p2] == val[p2-fileSize]:
            fileSize += 1

        # Now need to go through p1 and see if we can find space for this file
        foundSpace = False
        while True:
            freeSpace = 0
            while val[p1+freeSpace] is None:
                freeSpace += 1
            if freeSpace >= fileSize:
                foundSpace = True
                break
            else:
                p1 += 1
            if p1 > p2:
                break
        if not foundSpace:
            p2 -= fileSize
            continue
        for k in range(fileSize):
            val[p1+k] = val[p2-k]
            val[p2-k] = None

    ans = 0
    for k,v in enumerate(val):
        if v is None:
            continue
        ans += k*v
    print(ans)

def main():
    doPart1()
    doPart2()

if __name__ == "__main__":
    main()
