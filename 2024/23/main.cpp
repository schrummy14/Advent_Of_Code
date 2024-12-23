
#include "../helpers/extras.hh"

#include <bits/stdc++.h>
#include <chrono>
#include <set>
#include <unordered_map>

inline std::vector<short> getKeys(std::unordered_map<short, std::set<short>>& GRAPH)
{
    std::vector<short> keys;
    for (auto kv : GRAPH) {
        keys.push_back(kv.first);
    }
    return keys;
}

void doPart1(std::unordered_map<short, std::set<short>>& GRAPH)
{
    // Need to get the list of keys...
    std::vector<short> keys = getKeys(GRAPH);

    size_t ans = 0;
    #pragma omp parallel for reduction(+:ans)
    for (size_t k1 = 0; k1 < keys.size(); k1++) {
        const short key1 = keys[k1];
        for (size_t k2 = k1+1; k2 < keys.size(); k2++) {
            const short key2 = keys[k2];
            if (GRAPH[key2].find(key1) == GRAPH[key2].end()) continue;
            for (size_t k3 = k2+1; k3 < keys.size(); k3++) {
                const short key3 = keys[k3];
                if (
                    GRAPH[key3].find(key1) != GRAPH[key3].end() &&
                    GRAPH[key3].find(key2) != GRAPH[key3].end()
                ) {
                    if (
                        key1/26 == 't'-'a' || key2/26 == 't'-'a' || key3/26 == 't'-'a'
                    )
                    ans++;
                }
            }
        }
    }
    printf("%lu\n", ans);
}

void doPart2(std::unordered_map<short, std::set<short>>& GRAPH)
{
    std::vector<short> keys = getKeys(GRAPH);
    std::vector<short> best;

    for (short start : keys) {
        std::vector<short> connected;
        connected.push_back(start);
        for (auto key : keys) {
            bool ok = true;
            for (auto otherKey : connected) {
                if (GRAPH[otherKey].find(key) == GRAPH[otherKey].end()) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                connected.push_back(key);
            }
        }
        if (best.size() < connected.size())
            best = connected;
    }

    std::sort(best.begin(), best.end());
    std::vector<std::string> ans;
    for (auto s : best) {
        const char c1 = s/26 + 'a';
        const char c2 = s%26 + 'a';
        std::string c = "";
        c += c1;
        c += c2;
        ans.push_back(c);
    }
    printf("%s\n", joinString(ans, ',').c_str());
}

int main(int narg, char* args[])
{
    std::string filename = "input.dat";
    if (narg > 1) filename = std::string(args[1]);
    std::ifstream file(filename);
    std::string line;
    std::unordered_map<short, std::set<short>> GRAPH;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        std::vector<std::string> sline = splitString(line,"-");
        GRAPH[(sline[0][0]-'a')*26+sline[0][1]-'a'].insert((sline[1][0]-'a')*26+sline[1][1]-'a');
        GRAPH[(sline[1][0]-'a')*26+sline[1][1]-'a'].insert((sline[0][0]-'a')*26+sline[0][1]-'a');
    }
    file.close();

    auto start1 = std::chrono::steady_clock::now();
    doPart1(GRAPH);
    auto elapsed1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start1).count();
    printf("Part 1 Elapsed Time: %lu us\n", elapsed1);
    auto start2 = std::chrono::steady_clock::now();
    doPart2(GRAPH);
    auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start2).count();
    printf("Part 2 Elapsed Time: %lu us\n", elapsed2);
    printf("Total Elapsed Time: %lu us\n", elapsed1+elapsed2);
    return 0;
}
