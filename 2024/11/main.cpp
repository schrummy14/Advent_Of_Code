
#include "../helpers/extras.hh"
#include <unordered_map>

unsigned long countStone(
    const unsigned long stone,
    const int time,
    std::unordered_map<unsigned long, unsigned long>& csMEM
)
{
    if (csMEM.find(1000*stone + time) != csMEM.end()) {
        return csMEM[1000*stone + time];
    }
    std::string stoneString = std::to_string(stone);
    const size_t stoneStringLength = stoneString.length();
    unsigned long ans = 0;
    if (time == 0) {
        return 1;
    } else if (stone == 0) {
        ans = countStone(1, time-1, csMEM);
    } else if (stoneStringLength % 2 == 0) {
        unsigned long stone1 = std::atoi(stoneString.substr(0, stoneStringLength/2).c_str());
        unsigned long stone2 = std::atoi(stoneString.substr(stoneStringLength/2,stoneStringLength).c_str());
        ans = countStone(stone1, time-1, csMEM) + countStone(stone2, time-1, csMEM);
    } else {
        ans = countStone(2024*stone, time-1, csMEM);
    }

    csMEM[1000*stone+time] = ans;

    return ans;
}

void doPart1(const char* filename)
{
    std::vector<unsigned long> data;
    std::ifstream file(filename);
    std::string line;
    getline(file, line);
    file.close();
    stripString(line);
    std::vector<std::string> sLine = splitString(line, " ");
    for (std::string val : sLine) {
        data.push_back(std::atol(val.c_str()));
    }

    std::unordered_map<unsigned long, unsigned long> csMEM;
    unsigned long ans = 0;
    unsigned long curAnswer = 0;
    for (unsigned long v : data) {
        curAnswer = countStone(v, 25, csMEM);
        ans += curAnswer;
    }
    printf("%ld\n", ans);
}

void doPart2(const char* filename)
{
    std::vector<unsigned int> data;
    std::ifstream file(filename);
    std::string line;
    getline(file, line);
    file.close();
    stripString(line);
    std::vector<std::string> sLine = splitString(line, " ");
    for (std::string val : sLine) {
        data.push_back(std::atol(val.c_str()));
    }

    std::unordered_map<unsigned long, unsigned long> csMEM;
    unsigned long ans = 0;
    for (unsigned long v : data) {
        ans += countStone(v, 75, csMEM);
    }
    printf("%ld\n", ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
