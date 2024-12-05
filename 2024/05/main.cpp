
#include "../helpers/extras.hh"
#include <array>
void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    bool gettingRules = true;
    std::vector<std::array<int,2>> rules;
    std::vector<std::vector<int>> data;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) {
            gettingRules = false;
            continue;
        }

        if (gettingRules) {
            std::vector<std::string> sLine = splitString(line, "|");
            rules.push_back(
                std::array<int,2>{
                    std::atoi(sLine[0].c_str()),
                    std::atoi(sLine[1].c_str())
                }
            );
        } else {
            std::vector<std::string> sLine = splitString(line,",");
            std::vector<int> vals;
            for (auto sl : sLine) vals.push_back(std::atoi(sl.c_str()));
            data.push_back(vals);
        }
    }
    file.close();

    // Got the data and rules.
    // Time to use them...
    int sum = 0;
    for (auto line:data) {
        bool isValid = true;
        for (size_t k = 1; k < line.size(); k++) {
            bool inRules = false;
            for (size_t m = 0; m < rules.size(); m++) {
                if (line[k] == rules[m][0] && line[k-1] == rules[m][1]) {
                    inRules = true;
                    break;
                }
            }
            if (inRules) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            sum += line[line.size()/2];
        }
    }
    printf("%d\n", sum);
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    bool gettingRules = true;
    std::vector<std::array<int,2>> rules;
    std::vector<std::vector<int>> data;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) {
            gettingRules = false;
            continue;
        }

        if (gettingRules) {
            std::vector<std::string> sLine = splitString(line, "|");
            rules.push_back(
                std::array<int,2>{
                    std::atoi(sLine[0].c_str()),
                    std::atoi(sLine[1].c_str())
                }
            );
        } else {
            std::vector<std::string> sLine = splitString(line,",");
            std::vector<int> vals;
            for (auto sl : sLine) vals.push_back(std::atoi(sl.c_str()));
            data.push_back(vals);
        }
    }
    file.close();

    // Got the data and rules.
    // Time to use them...
    int sum = 0;
    for (auto line:data) {
        bool wasSorted = true;
        while (true) {
            bool isSorted = true;
            for (size_t k = 1; k < line.size(); k++) {
                bool inRules = false;
                for (size_t m = 0; m < rules.size(); m++) {
                    if (line[k] == rules[m][0] && line[k-1] == rules[m][1]) {
                        inRules = true;
                        break;
                    }
                }
                if (inRules) {
                    isSorted = false;
                    wasSorted = false;
                    const int tmp = line[k-1];
                    line[k-1] = line[k];
                    line[k] = tmp;
                    break;
                }
            }
            if (isSorted) {
                break;
            }
        }
        if (!wasSorted) {
            sum += line[line.size()/2];
        }
    }
    printf("%d\n", sum);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
