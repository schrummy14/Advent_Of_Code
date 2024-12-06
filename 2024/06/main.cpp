
#include "../helpers/extras.hh"
#include <array>
#include <set>

std::array<int,2> getStart(std::vector<std::string>& data)
{
    const int R = data.size();
    const int C = data[0].length();
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (data[r].c_str()[c] == '^') return std::array<int,2>{r,c};
        }
    }
    return std::array<int,2>{-1,-1};
}

std::set<std::array<int,2>> doPart1(const char* filename) // 4665
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> data;
    while (getline(file, line)) {
        stripString(line);
        data.push_back(line);
    }
    file.close();

    const int R = data.size();
    const int C = data[0].length();

    std::array<int,2> start_pos = getStart(data);
    const int sr = start_pos[0];
    const int sc = start_pos[1];

    std::set<std::array<int,2>> SEEN;

    std::array<std::array<int,2>,4> DIR; // = {{-1,0},{0,1},{1,0},{0,-1}};
    DIR[0] = {-1, 0};
    DIR[1] = { 0, 1};
    DIR[2] = { 1, 0};
    DIR[3] = { 0,-1};
    int curDir = 0;
    int cr = sr;
    int cc = sc;

    while (true) {
        SEEN.insert(std::array<int,2>{cr,cc});
        const int nr = cr+DIR[curDir][0];
        const int nc = cc+DIR[curDir][1];

        if (! (0 <= nr && nr < R && 0 <= nc && nc < C)) {
            break;
        }
        if (data[nr][nc] == '#') {
            curDir = (curDir+1)%4;
        } else {
            cr = nr;
            cc = nc;
        }
    }
    printf("%ld\n", SEEN.size());
    return SEEN;
}

void doPart2(const char* filename, std::set<std::array<int,2>>& SEEN) // 1688
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> data;
    while (getline(file, line)) {
        stripString(line);
        data.push_back(line);
    }
    file.close();

    const int R = data.size();
    const int C = data[0].length();

    std::array<std::array<int,2>,4> DIR;
    DIR[0] = {-1, 0};
    DIR[1] = { 0, 1};
    DIR[2] = { 1, 0};
    DIR[3] = { 0,-1};

    std::array<int,2> start_pos = getStart(data);
    const int sr = start_pos[0];
    const int sc = start_pos[1];

    int numLoops = 0;
    for (auto prc : SEEN) {
        const int ob_r = prc[0];
        const int ob_c = prc[1];
        int cr = sr;
        int cc = sc;
        int curDir = 0;

        std::set<std::array<int,3>> LOOP_RC;

        while (true) {
            if (LOOP_RC.find(std::array<int,3>{cr,cc,curDir})!=LOOP_RC.end()) {
                numLoops +=1;
                break;
            }
            LOOP_RC.insert(std::array<int,3>{cr,cc,curDir});
            const int nr = cr + DIR[curDir][0];
            const int nc = cc + DIR[curDir][1];

            if (! (0 <= nr && nr < R && 0 <= nc && nc < C)) {
                break;
            }
            if (data[nr][nc] == '#' || (nr == ob_r && nc == ob_c)) {
                curDir = (curDir+1)%4;
            } else {
                cr = nr;
                cc = nc;
            }
        }
    }
    printf("%d\n", numLoops);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    std::set<std::array<int,2>> SEEN = doPart1(filename.c_str());
    doPart2(filename.c_str(), SEEN);
    return 0;
}
