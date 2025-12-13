
#include "../../helpers/extras.hh"
#include <unordered_map>

std::unordered_map<std::string, std::vector<std::string>> DATA;
std::unordered_map<std::string, size_t> MEMORY;
size_t dfs(std::string cur, bool hasFFT, bool hasDAC)
{
    std::string key = cur;
    if (hasFFT) {
        key+="1";
    } else {
        key+="0";
    }
    if (hasDAC) {
        key+="1";
    } else {
        key+="0";
    }
    if (MEMORY.find(key) != MEMORY.end()) return MEMORY[key];

    if (cur == "out") {
        if (hasFFT && hasDAC) {
            return 1;
        } else {
            return 0;
        }
    }

    size_t curAns = 0;
    for (auto& np : DATA[cur]) {
        curAns += dfs(
            np,
            hasFFT || (np == "fft"),
            hasDAC || (np == "dac")
        );
    }
    MEMORY[key] = curAns;
    return curAns;
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        std::vector<std::string> sLine = splitString(line, ":");
        stripString(sLine[1]);
        for (auto val : splitString(sLine[1], " ")) {
            DATA[sLine[0]].push_back(val);
        }
    }
    file.close();

    MEMORY.clear();
    size_t ans = dfs("you", true, true);
    std::cout << "Part 1: " << ans << '\n';
}

void doPart2(const char* filename)
{
    (void)filename;
    MEMORY.clear();
    size_t ans = dfs("svr", false, false);
    std::cout << "Part 2: " << ans << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "input.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
