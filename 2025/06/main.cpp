
#include "../../helpers/extras.hh"

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> DATA;
    while (getline(file, line)) {
        std::string curLine = "";
        for (auto c : line) {
            if (c != '\n') curLine += c;
        }
        DATA.push_back(curLine);
    }
    file.close();

    size_t cur = 0;
    size_t maxData = DATA.size();
    size_t maxCur = DATA[0].length();
    size_t ans = 0;
    bool done = false;
    while (!done) {
        size_t nextCur = cur+1;
        while (true) {
            if (nextCur == maxCur || DATA[maxData-1][nextCur] != ' ') {
                if (nextCur == maxCur) done = true;
                break;
            }
            nextCur++;
        }
        size_t curAns;
        if (DATA[maxData-1][cur] == '*') curAns = 1;
        else curAns = 0;
        size_t k1 = cur;
        size_t k2;
        if (done) k2 = nextCur;
        else k2 = nextCur -1;
        for (size_t i = 0; i < maxData-1; i++) {
            std::string curVal = "";
            for (size_t k = k1; k < k2; k++) {
                curVal += DATA[i][k];
            }
            if (DATA[maxData-1][cur] == '*') curAns *= atol(curVal.c_str());
            else curAns += atol(curVal.c_str());
        }
        cur = nextCur;
        ans += curAns;
    }
    std::cout << "Part 1: " << ans << '\n';
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> DATA;
    while (getline(file, line)) {
        std::string curLine = "";
        for (auto c : line) {
            if (c != '\n') curLine += c;
        }
        DATA.push_back(curLine);
    }
    file.close();

    size_t cur = 0;
    size_t maxData = DATA.size();
    size_t maxCur = DATA[0].length();
    size_t ans = 0;
    bool done = false;
    while (!done) {
        size_t nextCur = cur+1;
        while (true) {
            if (nextCur == maxCur || DATA[maxData-1][nextCur] != ' ') {
                if (nextCur == maxCur) done = true;
                break;
            }
            nextCur++;
        }
        size_t curAns;
        if (DATA[maxData-1][cur] == '*') curAns = 1;
        else curAns = 0;
        size_t k1 = cur;
        size_t k2;
        if (done) k2 = nextCur;
        else k2 = nextCur -1;
        for (size_t k = k1; k < k2; k++) {
            std::string curVal = "";
            for (size_t i = 0; i < maxData-1; i++) {
                curVal += DATA[i][k];
            }
            if (DATA[maxData-1][cur] == '*') curAns *= atol(curVal.c_str());
            else curAns += atol(curVal.c_str());
        }
        cur = nextCur;
        ans += curAns;
    }
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
