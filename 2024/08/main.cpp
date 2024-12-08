
#include "../helpers/extras.hh"

#include <array>
#include <set>
#include <unordered_map>

void doPart1(const char* filename) // 240
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> GRID;
    while (getline(file, line)) {
        stripString(line);
        GRID.push_back(line);
    }
    file.close();

    char R = GRID.size();
    char C = GRID[0].length();

    std::unordered_map<char,std::vector<std::array<char,2>>> ANTS;
    for (char r = 0; r < R; r++) {
        for (char c = 0; c < C; c++) {
            if (GRID[r][c] != '.') {
                ANTS[GRID[r][c]].push_back(std::array<char,2>{r,c});
            }
        }
    }

    std::set<std::array<char,2>> NODES;
    for (auto keyValue : ANTS) {
        std::vector<std::array<char,2>> vals = keyValue.second;
        for (std::array<char,2> p1 : vals) {
            const char r1 = p1[0];
            const char c1 = p1[1];
            for (std::array<char,2> p2 : vals) {
                const char r2 = p2[0];
                const char c2 = p2[1];
                if ((r1 == r2) && (c1 == c2)) {
                    continue;
                }
                for (char r = 0; r < R; r++) {
                    for (char c = 0; c < C; c++) {

                        const char d1 = abs(r-r1)+abs(c-c1);
                        const char d2 = abs(r-r2)+abs(c-c2);

                        const char dr1 = r-r1;
                        const char dr2 = r-r2;
                        const char dc1 = c-c1;
                        const char dc2 = c-c2;

                        if ((d1==2*d2 || d1*2==d2) && 0<=r && r<R && 0<=c && c<C && (dr1*dc2 == dc1*dr2)) {
                            NODES.insert(std::array<char,2>{r,c});
                        }
                    }
                }
            }
        }
    }
    printf("%ld\n", NODES.size());
}

void doPart2(const char* filename) // 955
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> GRID;
    while (getline(file, line)) {
        stripString(line);
        GRID.push_back(line);
    }
    file.close();

    char R = GRID.size();
    char C = GRID[0].length();

    std::unordered_map<char,std::vector<std::array<char,2>>> ANTS;
    for (char r = 0; r < R; r++) {
        for (char c = 0; c < C; c++) {
            if (GRID[r][c] != '.') {
                ANTS[GRID[r][c]].push_back(std::array<char,2>{r,c});
            }
        }
    }

    std::set<std::array<char,2>> NODES;
    for (auto keyValue : ANTS) {
        std::vector<std::array<char,2>> vals = keyValue.second;
        for (std::array<char,2> p1 : vals) {
            const char r1 = p1[0];
            const char c1 = p1[1];
            for (std::array<char,2> p2 : vals) {
                const char r2 = p2[0];
                const char c2 = p2[1];
                if ((r1 == r2) && (c1 == c2)) {
                    continue;
                }
                for (char r = 0; r < R; r++) {
                    for (char c = 0; c < C; c++) {

                        const char dr1 = r-r1;
                        const char dr2 = r-r2;
                        const char dc1 = c-c1;
                        const char dc2 = c-c2;

                        if (0<=r && r<R && 0<=c && c<C and (dr1*dc2 == dc1*dr2)) {
                            NODES.insert(std::array<char,2>{r,c});
                        }
                    }
                }
            }
        }
    }
    printf("%ld\n", NODES.size());
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
