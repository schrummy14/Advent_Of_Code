
#include "../../helpers/extras.hh"

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<int> pieceValue;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        if (line[line.length()-1] != ':') break;
        int pv = 0;
        for (int k = 0; k < 3; k++) {
            getline(file, line);
            stripString(line);
            for (auto&c : line) {
                if (c=='#') pv++;
            }
        }
        pieceValue.push_back(pv);
    }

    size_t ans = 0;
    do {
        stripString(line);
        if (line.length() == 0) continue;
        std::vector<std::string> lineValues = splitString(line, ":");
        int fullArea = 1;
        for (auto& a : splitString(lineValues[0], "x")) {
            fullArea *= atoi(a.c_str());
        }
        stripString(lineValues[1]);

        size_t k = 0;
        int pressentArea = 0;
        for (auto& v : splitString(lineValues[1], " ")) {
            pressentArea += pieceValue[k]*atoi(v.c_str());
        }
        if (pressentArea < fullArea) ans++;
    }
    while (getline(file, line));
    file.close();
    std::cout << "Part 1: " << ans << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "input.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    return 0;
}
