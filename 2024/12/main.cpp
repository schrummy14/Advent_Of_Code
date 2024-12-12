
#include "../helpers/extras.hh"

#include <array>
#include <queue>
#include <set>
#include <unordered_map>

int DIRS[4][2]={
    {-1, 0},
    { 0, 1},
    { 1, 0},
    { 0,-1}
};

bool findInList(std::array<size_t,2>& pos, std::vector<std::array<size_t,2>>& list)
{
    for (auto v : list) {
        if (v == pos) return true;
    }
    return false;
}

std::vector<std::vector<std::array<size_t,2>>> doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> GRID;
    while (getline(file, line)) {
        stripString(line);
        GRID.push_back(line);
    }
    file.close();

    const size_t R = GRID.size();
    const size_t C = GRID[0].size();

    std::vector<std::vector<std::array<size_t,2>>> REGIONS;
    std::vector<bool> SEEN(R*C, false);

    unsigned long ans = 0;
    for (size_t r = 0; r < R; r++) {
        for (size_t c = 0; c < C; c++) {
            if (SEEN[r*R+c]) continue;
            unsigned long area = 0;
            unsigned long perimeter = 0;
            const char curVal = GRID[r][c];

            std::queue<std::array<size_t,2>> Q;
            Q.push(std::array<size_t,2>{r,c});
            std::vector<std::array<size_t,2>> curRegion;
            while (Q.size() > 0) {
                std::array<size_t,2> pos = Q.front();
                Q.pop();

                size_t sr = pos[0];
                size_t sc = pos[1];
                if (!findInList(pos, curRegion)) {
                    curRegion.push_back(pos);
                }

                if (SEEN[sr*R+sc]) continue;
                SEEN[sr*R+sc] = true;

                area++;
                size_t numNeighbors = 0;
                for (auto dir : DIRS) {
                    size_t nr = sr + dir[0];
                    size_t nc = sc + dir[1];
                    if (0 <= nr && nr < R && 0 <= nc && nc < C && GRID[nr][nc] == curVal) {
                        numNeighbors++;
                        Q.push(std::array<size_t,2>{nr,nc});
                    }
                }
                perimeter += (4-numNeighbors);
            }
            if (curRegion.size() > 0) {
                REGIONS.push_back(curRegion);
            }
            ans += perimeter*area;
        }
    }
    printf("%ld\n",ans);
    return REGIONS;
}

void doPart2(std::vector<std::vector<std::array<size_t,2>>>& REGIONS)
{
    unsigned long ans = 0;
    for (auto region : REGIONS) {
        if (region.size() == 1) {
            ans += 4;
            continue;
        }
        std::set<std::array<size_t,2>>onEdge;
        std::unordered_map<size_t, std::vector<std::array<size_t,2>>> neighbors;
        for (auto pos : region) {
            size_t sr = pos[0];
            size_t sc = pos[1];
            size_t numNeighbors = 0;
            for (auto dir : DIRS) {
                const size_t nr = sr + dir[0];
                const size_t nc = sc + dir[1];
                std::array<size_t,2> nPos {nr,nc};
                if (findInList(nPos, region)) {
                    numNeighbors++;
                    neighbors[sr*1000+sc].push_back(std::array<size_t,2>{sr+dir[0], sc+dir[1]});
                }
            }
            if (numNeighbors < 4) onEdge.insert(pos);
        }

        unsigned long sides = 0;
        for (auto key : neighbors) {
            const unsigned long numNeighbors = key.second.size();
            if (numNeighbors == 1)
                sides += 2;
            else if (numNeighbors == 2) {
                // Cannot be north-south or east-west neighbors
                const size_t r = key.first/1000;
                const size_t c = key.first%1000;
                std::array<size_t,2> pos1 {r+1, c+0};
                std::array<size_t,2> pos2 {r-1, c+0};
                std::array<size_t,2> pos3 {r+0, c+1};
                std::array<size_t,2> pos4 {r+0, c-1};
                if (
                    (findInList(pos1, region) && findInList(pos2, region)) ||
                    (findInList(pos3, region) && findInList(pos4, region))
                ) continue;
                sides++;
            }
        }

        // Now need to count corners
        for (auto key : neighbors) {
            // Can be one of the four different options of the form
            // x x or x x or x 0 or 0 x
            // x 0    0 x    x x    x x
            // Where x is part of the group and 0 is not

            const size_t r = key.first/1000;
            const size_t c = key.first%1000;

            std::array<size_t,2> pos1 {r+0, c+1};
            std::array<size_t,2> pos2 {r+1, c+0};
            std::array<size_t,2> pos3 {r+1, c+1};

            std::array<size_t,2> pos4 {r+0, c-1};
            std::array<size_t,2> pos5 {r+1, c+0};
            std::array<size_t,2> pos6 {r+1, c-1};

            std::array<size_t,2> pos7 {r+0, c+1};
            std::array<size_t,2> pos8 {r-1, c+0};
            std::array<size_t,2> pos9 {r-1, c+1};

            std::array<size_t,2> pos10 {r+0, c-1};
            std::array<size_t,2> pos11 {r-1, c+0};
            std::array<size_t,2> pos12 {r-1, c-1};

            if (findInList(pos1, region) && findInList(pos2, region) && !findInList(pos3,region)) sides++;
            if (findInList(pos4, region) && findInList(pos5, region) && !findInList(pos6,region)) sides++;
            if (findInList(pos7, region) && findInList(pos8, region) && !findInList(pos9,region)) sides++;
            if (findInList(pos10, region) && findInList(pos11, region) && !findInList(pos12,region)) sides++;
        }


        ans += region.size() * sides;
    }
    printf("%ld\n", ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    std::vector<std::vector<std::array<size_t,2>>> REGIONS = doPart1(filename.c_str());
    doPart2(REGIONS);
    return 0;
}
