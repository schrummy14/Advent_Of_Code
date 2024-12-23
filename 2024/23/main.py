#!/usr/bin/env python3

import sys

from collections import defaultdict

def doPart1(GRAPH):
    ans = 0
    keys = sorted(GRAPH.keys())
    for k1 in range(len(keys)):
        key1 = keys[k1]
        for k2 in range(k1+1,len(keys)):
            key2 = keys[k2]
            if key1 not in GRAPH[key2]:
                continue
            for k3 in range(k2+1,len(keys)):
                key3 = keys[k3]
                if key1 in GRAPH[key3] and key2 in GRAPH[key3]:
                    if key1[0] == "t" or key2[0] == "t" or key3[0] == "t":
                        ans += 1
    print(ans)

def doPart2(GRAPH):
    best = None
    xs = sorted(GRAPH.keys())
    for start in xs:
        clique = [start]
        for x in xs:
            ok = True
            for y in clique:
                if x not in GRAPH[y]:
                    ok = False
                    break
            if ok:
                clique.append(x)
        if best is None or len(clique) > len(best):
            best = clique
    print(','.join(sorted(best)))

def main():
    filename = "input.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    GRAPH = defaultdict(set)
    with open(filename, "r") as f:
        for li in f:
            line = li.strip()
            if not line:
                continue
            a,b = line.split("-")
            GRAPH[a].add(b)
            GRAPH[b].add(a)
    doPart1(GRAPH)
    doPart2(GRAPH)

if __name__ == "__main__":
    main()
