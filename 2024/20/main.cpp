
#include "../helpers/extras.hh"

std::vector<std::vector<int>> solveMaze(int sr, int sc, std::vector<std::string>& GRID)
{
    std::vector<std::vector<int>> DIST(GRID.size(), std::vector<int>(GRID[0].size(), -1));
    std::queue<std::array<int, 2>> queue;
    queue.push({sr, sc});
    DIST[sr][sc] = 0;
    while (!queue.empty()) {
        auto [r, c] = queue.front();
        queue.pop();
        for (auto [dr, dc] : DIRS) {
            int rr = r + dr, cc = c + dc;
            if (GRID[rr][cc] == '#') continue;
            if (DIST[rr][cc] != -1) continue;
            DIST[rr][cc] = DIST[r][c] + 1;
            queue.push({rr, cc});
        }
    }
    return DIST;
}

void doPart1(int sr, int sc, std::vector<std::string>& GRID, int cheatStep)
{
    std::vector<std::vector<int>> DIST = solveMaze(sr, sc, GRID);

    int R = GRID.size();
    int C = GRID[0].size();

    int minTime = R > 20 ? 100 : 50;

    long ans = 0;
    long best = 0;
    for (int r1 = 0; r1 < R; r1++) {
        for (int c1 = 0; c1 < C; c1++) {
            if (GRID[r1][c1] == '#') continue;
            for (int r2 = std::max(0, r1-cheatStep); r2 < std::min(R, r1+cheatStep+1); r2++) {
                for (int c2 = std::max(0, c1-cheatStep); c2 < std::min(C, c1+cheatStep+1); c2++) {
                    if (GRID[r2][c2] == '#') continue;
                    int oneNorm = std::abs(r2-r1) + std::abs(c2-c1);
                    if (oneNorm > cheatStep) continue;
                    long timeSaved = DIST[r2][c2] - DIST[r1][c1] - oneNorm;
                    if (timeSaved >= minTime) {
                        ans += 1;
                        if (timeSaved > best) {
                            best = timeSaved;
                        }
                    }
                }
            }
        }
    }
    printf("%ld, %ld\n", ans, best);
}

void doPart2(int sr, int sc, std::vector<std::string>& GRID, int cheatStep)
{
    std::vector<std::vector<int>> DIST = solveMaze(sr, sc, GRID);

    int R = GRID.size();
    int C = GRID[0].size();

    int minTime = R > 20 ? 100 : 50;

    long ans = 0;
    long best = 0;
    for (int r1 = 0; r1 < R; r1++) {
        for (int c1 = 0; c1 < C; c1++) {
            if (GRID[r1][c1] == '#') continue;
            for (int r2 = std::max(0, r1-cheatStep); r2 < std::min(R, r1+cheatStep+1); r2++) {
                for (int c2 = std::max(0, c1-cheatStep); c2 < std::min(C, c1+cheatStep+1); c2++) {
                    if (GRID[r2][c2] == '#') continue;
                    int oneNorm = std::abs(r2-r1) + std::abs(c2-c1);
                    if (oneNorm > cheatStep) continue;
                    long timeSaved = DIST[r2][c2] - DIST[r1][c1] - oneNorm;
                    if (timeSaved >= minTime) {
                        ans += 1;
                        if (timeSaved > best) {
                            best = timeSaved;
                        }
                    }
                }
            }
        }
    }
    printf("%ld, %ld\n", ans, best);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);

    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> GRID;
    while (getline(file, line)) {
        stripString(line);
        GRID.push_back(line);
    }
    file.close();

    int R = GRID.size();
    int C = GRID[0].size();

    int sr = -1, sc = -1;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (GRID[i][j] == 'S') sr = i, sc = j;
        }
    }

    doPart1(sr,sc,GRID,2);
    doPart2(sr,sc,GRID,20);
    return 0;
}
