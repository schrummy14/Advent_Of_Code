
#include "../../helpers/extras.hh"

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> GRID;
    while (getline(file, line)) {
        stripString(line);
        GRID.push_back(line);
    }
    file.close();
    int R = GRID.size();
    int C = GRID[0].length();
    size_t ans = 0;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (GRID[r][c] != '@') continue;
            int numNeighbors = 0;
            for (int dr = -1; dr <= 1; dr++) {
                const int nr = r + dr;
                if (nr < 0 || nr >= R) continue;
                for (int dc = -1; dc <= 1; dc++) {
                    const int nc = c + dc;
                    if (nc < 0 || nc >= C) continue;
                    if (GRID[nr][nc] == '@') numNeighbors++;
                }
            }
            if (numNeighbors <= 4) ans++; // <= 4 because we are counting itself...
        }
    }
    std::cout << ans << '\n';
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> GRID;
    while (getline(file, line)) {
        stripString(line);
        GRID.push_back(line);
    }
    file.close();
    int R = GRID.size();
    int C = GRID[0].length();
    size_t ans = 0;
    bool done = false;
    while (!done) {
        done = true;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (GRID[r][c] != '@') continue;
                int numNeighbors = 0;
                for (int dr = -1; dr <= 1; dr++) {
                    const int nr = r + dr;
                    if (nr < 0 || nr >= R) continue;
                    for (int dc = -1; dc <= 1; dc++) {
                        const int nc = c + dc;
                        if (nc < 0 || nc >= C) continue;
                        if (GRID[nr][nc] == '@') numNeighbors++;
                    }
                }
                if (numNeighbors <= 4) { // <= 4 because we are counting itself...
                    ans++;
                    GRID[r][c] = 'x';
                    done = false;
                }
            }
        }
    }
    std::cout << ans << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
