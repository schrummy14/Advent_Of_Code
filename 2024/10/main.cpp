
#include "../helpers/extras.hh"

#include <array>
#include <set>
#include <queue>

// I'll keep the queue this time...
unsigned int rollDown(const char sr, const char sc, std::vector<std::vector<char>>& GRID)
{
    std::queue<std::array<int,2>> queue;
    queue.push(std::array<int,2>{sr,sc});

    std::set<std::array<int,2>> SEEN;

    static const int R = GRID.size();
    static const int C = GRID[0].size();

    unsigned int ans = 0;
    while (queue.size() > 0) {
        std::array<int,2> pos = queue.front();
        queue.pop();
        if (SEEN.find(pos) != SEEN.end()) continue;
        SEEN.insert(pos);
        if (GRID[pos[0]][pos[1]] == 0) ans += 1;
        if (
            0 <= pos[0]-1 && pos[0]-1 < R &&
            0 <= pos[1]+0 && pos[1]+0 < C &&
            GRID[pos[0]-1][pos[1]+0] == GRID[pos[0]][pos[1]]-1
        ) queue.push(std::array<int,2>{pos[0]-1,pos[1]+0});
        if (
            0 <= pos[0]+0 && pos[0]+0 < R &&
            0 <= pos[1]+1 && pos[1]+1 < C &&
            GRID[pos[0]+0][pos[1]+1] == GRID[pos[0]][pos[1]]-1
        ) queue.push(std::array<int,2>{pos[0]+0,pos[1]+1});
        if (
            0 <= pos[0]+1 && pos[0]+1 < R &&
            0 <= pos[1]+0 && pos[1]+0 < C &&
            GRID[pos[0]+1][pos[1]+0] == GRID[pos[0]][pos[1]]-1
        ) queue.push(std::array<int,2>{pos[0]+1,pos[1]+0});
        if (
            0 <= pos[0]+0 && pos[0]+0 < R &&
            0 <= pos[1]-1 && pos[1]-1 < C &&
            GRID[pos[0]+0][pos[1]-1] == GRID[pos[0]][pos[1]]-1
        ) queue.push(std::array<int,2>{pos[0]+0,pos[1]-1});
    }
    return ans;
}

void doPart1(const char* filename)
{
    std::vector<std::vector<char>> GRID;
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        std::vector<char>row;
        for (size_t k = 0; k < line.length(); k++) row.push_back(line[k]-'0');
        GRID.push_back(row);
    }
    file.close();

    const size_t R = GRID.size();
    const size_t C = GRID[0].size();

    unsigned int ans = 0;
    for (size_t r = 0; r < R; r++) {
        for (size_t c = 0; c < C; c++) {
            if (GRID[r][c] != 9) continue;
            ans += rollDown(r, c, GRID);
        }
    }
    printf("%d\n",ans);
}

unsigned int rollDown2(const char sr, const char sc, std::vector<std::vector<char>>& GRID)
{
    if (GRID[sr][sc] == 0) return 1;

    static const int R = GRID.size();
    static const int C = GRID[0].size();

    unsigned int ans = 0;
    if (
            0 <= sr-1 && sr-1 < R &&
            0 <= sc+0 && sc+0 < C &&
            GRID[sr-1][sc+0] == GRID[sr][sc]-1
        ) ans += rollDown2(sr-1,sc+0, GRID);
        if (
            0 <= sr+0 && sr+0 < R &&
            0 <= sc+1 && sc+1 < C &&
            GRID[sr+0][sc+1] == GRID[sr][sc]-1
        ) ans += rollDown2(sr+0,sc+1, GRID);
        if (
            0 <= sr+1 && sr+1 < R &&
            0 <= sc+0 && sc+0 < C &&
            GRID[sr+1][sc+0] == GRID[sr][sc]-1
        ) ans += rollDown2(sr+1,sc+0, GRID);
        if (
            0 <= sr+0 && sr+0 < R &&
            0 <= sc-1 && sc-1 < C &&
            GRID[sr+0][sc-1] == GRID[sr][sc]-1
        ) ans += rollDown2(sr+0,sc-1, GRID);

    return ans;
}

void doPart2(const char* filename)
{
    std::vector<std::vector<char>> GRID;
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        std::vector<char>row;
        for (size_t k = 0; k < line.length(); k++) row.push_back(line[k]-'0');
        GRID.push_back(row);
    }
    file.close();

    const size_t R = GRID.size();
    const size_t C = GRID[0].size();

    unsigned int ans = 0;
    for (size_t r = 0; r < R; r++) {
        for (size_t c = 0; c < C; c++) {
            if (GRID[r][c] != 9) continue;
            ans += rollDown2(r, c, GRID);
        }
    }
    printf("%d\n",ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
