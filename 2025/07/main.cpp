
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
    size_t R = GRID.size();
    size_t C = GRID[0].length();
    size_t ans = 0;
    // std::cout << GRID[0] << '\n';
    for (size_t r = 1; r < R; r++) {
        for (size_t c = 0; c < C; c++) {
            if (GRID[r-1][c] == 'S') {
                GRID[r][c] = '|';
                continue;
            }
            if (GRID[r][c] == '^' && GRID[r-1][c] == '|') {
                if (c > 0) GRID[r][c-1] = '|';
                if (c < C-1) GRID[r][c+1] = '|';
                ans++;
                continue;
            }
            if (GRID[r-1][c] == '|') GRID[r][c] = '|';
        }
        // std::cout << GRID[r] << '\n';
    }
    std::cout << "Part 1: " << ans << '\n';
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
