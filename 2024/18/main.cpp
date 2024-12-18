
#include "../helpers/extras.hh"

#define N 71

int solveMaze(std::vector<bool>& GRID)
{
    std::vector<bool> SEEN(N*N,false);
    std::queue<std::array<int,3>> queue;
    queue.push(std::array<int,3>{0,0,0});
    while (queue.size() > 0) {
        std::array<int,3> curVals = queue.front();
        queue.pop();
        const int d = curVals[0];
        const int x = curVals[1];
        const int y = curVals[2];
        if (x==(N-1) && y==(N-1))
            return d;
        if (SEEN[N*x+y])
            continue;
        SEEN[N*x+y] = true;
        for (auto dir : DIRS){
            const int yy = y+dir[0];
            const int xx = x+dir[1];
            if (0 <= xx && xx < N && 0 <= yy && yy < N && !GRID[N*xx+yy])
                queue.push(std::array<int,3>{d+1,xx,yy});
        }
    }
    return -1;
}

void doPart1(std::vector<std::array<int,2>>& memLocations)
{
    std::vector<bool> GRID(N*N,false);
    for (size_t k = 0; k < memLocations.size(); k++) {
        std::array<int,2> pos = memLocations[k];
        if (0 <= pos[0] && pos[0] < N && 0 <= pos[1] && pos[1] < N)
            GRID[N*pos[0] + pos[1]] = true;
        if (k == 1023) break;
    }
    printf("%d\n", solveMaze(GRID));
}

void doPart2(std::vector<std::array<int,2>>& memLocations)
{
    size_t a = 0;
    size_t b = memLocations.size()-1;
    while (true) {
        size_t m = (a+b)/2;
        std::vector<bool> GRID(N*N,false);
        for (size_t k = 0; k < memLocations.size(); k++) {
            std::array<int,2> pos = memLocations[k];
            if (0 <= pos[0] && pos[0] < N && 0 <= pos[1] && pos[1] < N)
                GRID[N*pos[0] + pos[1]] = true;
            if (k == m) break;
        }
        int dd = solveMaze(GRID);
        // printf("%ld %ld %ld %d\n",a,m,b,dd);
        if (dd < 0) b=m;
        else a=m;
        if (b-a == 1) break;
    }
    printf("%d,%d\n", memLocations[b][0], memLocations[b][1]);
}

int main(int narg, char* args[])
{
    std::string filename = "input.dat";
    if (narg > 1) filename = std::string(args[1]);

    std::vector<std::array<int,2>> memLocations;
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        std::vector<std::string> sLine = splitString(line, ",");
        memLocations.push_back({std::atoi(sLine[0].c_str()),std::atoi(sLine[1].c_str())});
    }
    file.close();

    doPart1(memLocations);
    doPart2(memLocations);
    return 0;
}
