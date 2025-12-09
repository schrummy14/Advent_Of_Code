
#include "../../helpers/extras.hh"
#include <bits/stdc++.h>
#include <set>

size_t getDist2(const size_t j1, const size_t j2, std::vector<std::array<size_t, 3>>& p)
{
    const size_t dx = p[j1][0]-p[j2][0];
    const size_t dy = p[j1][1]-p[j2][1];
    const size_t dz = p[j1][2]-p[j2][2];
    return dx*dx + dy*dy + dz*dz;
}

// Comparator function
bool rangeComp(std::array<size_t, 3> a, std::array<size_t, 3> b) {
    return a[0] < b[0];
}

// Comparator function
bool setComp(std::set<size_t> a, std::set<size_t> b) {
    return a.size() > b.size();
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::array<size_t, 3>> positions;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, ",");
        const size_t v1 = atol(sLine[0].c_str());
        const size_t v2 = atol(sLine[1].c_str());
        const size_t v3 = atol(sLine[2].c_str());
        positions.push_back({v1,v2,v3});
    }
    file.close();

    size_t maxConnections = 0;
    if (strcmp(filename, "example.dat")==0) {
        maxConnections = 10;
    } else {
        maxConnections = 1000;
    }

    std::vector<std::array<size_t,3>> values;
    for (size_t j1 = 0; j1 < positions.size()-1; j1++) {
        for (size_t j2 = j1+1; j2 < positions.size(); j2++) {
            const size_t dist2 = getDist2(j1, j2, positions);
            // printf("%zu, %zu, %zu\n", dist2, j1, j2);
            values.push_back({dist2, j1, j2});
        }
    }

    sort(values.begin(), values.end(), rangeComp);

    size_t connections = 0;
    std::vector<std::set<size_t>> clusters;
    for (size_t k1 = 0; k1 < maxConnections; k1++) {
        const size_t id1 = values[k1][1];
        const size_t id2 = values[k1][2];
        // Need to loop through clusters and see if we can find
        bool foundConnection = false;
        for (size_t k2 = 0; k2 < clusters.size(); k2++) {
            const bool t1 = clusters[k2].find(id1) != clusters[k2].end();
            const bool t2 = clusters[k2].find(id2) != clusters[k2].end();

            if (t1 || t2) {
                foundConnection = true;
                if (t1 && t2) break; // skip
                connections++;
                clusters[k2].insert(id1);
                clusters[k2].insert(id2);

                while (true) {
                    bool didMerge = false;
                    for (size_t k3 = k2+1; k3 < clusters.size(); k3++) {
                        const bool tt1 = clusters[k3].find(id1) != clusters[k3].end();
                        const bool tt2 = clusters[k3].find(id2) != clusters[k3].end();
                        if (tt1 || tt2) {
                            didMerge = true;
                            clusters[k2].merge(clusters[k3]);
                            clusters[k3].clear();
                            break;
                        }
                    }
                    if (!didMerge) break;
                }
                break;
            }
        }
        if (! foundConnection) {
            connections++;
            clusters.push_back({id1, id2});
        }
    }

    sort(clusters.begin(), clusters.end(), setComp);
    size_t ans = 1;
    for (size_t k = 0; k < 3; k++) {
        std::cout << clusters[k].size() << '\n';
        ans *= clusters[k].size();
    }
    std::cout << ans << '\n';
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, " ");
    }
    file.close();
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
