
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

size_t shootRay(size_t r, size_t c, std::vector<std::string>& GRID, std::vector<size_t>& SEEN)
{
    static const size_t R = GRID.size();
    static const size_t C = GRID[0].length();

    if (r == R) return 1;

    if (SEEN[r*C + c] > 0) return SEEN[r*C+c];

    size_t ans = 0;
    if (r+1 < R && GRID[r+1][c] == '^'){
        ans+=shootRay(r+1, c-1, GRID, SEEN);
        ans+=shootRay(r+1, c+1, GRID, SEEN);
    } else {
        ans+=shootRay(r+1, c+0, GRID, SEEN);
    }
    SEEN[r*C + c] = ans;
    return ans;
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

    const size_t R = GRID.size();
    const size_t C = GRID[0].length();
    size_t curC = 0;
    for (size_t c = 0; c < C; c++) {
        if (GRID[0][c] == 'S') {
            curC = c;
            break;
        }
    }
    GRID[1][curC] = '|';

    std::vector<size_t> SEEN(R*C, 0);

    size_t ans = shootRay(1, curC, GRID, SEEN);
    std::cout << "Part 2: " << ans << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
