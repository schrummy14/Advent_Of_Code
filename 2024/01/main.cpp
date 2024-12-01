
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

#define FILENAME "input.dat"

bool isInside(std::unordered_map<int,int>& map, int key)
{
    return map.find(key) != map.end();
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<int> l1;
    std::vector<int> l2;
    while (getline(file, line)) {
        std::vector<std::string> sLine;
        boost::split(sLine, line, boost::is_any_of(" "));
        l1.push_back(std::atoi(sLine[0].c_str()));
        l2.push_back(std::atoi(sLine[3].c_str()));
    }
    file.close();

    std::sort(l1.begin(), l1.end());
    std::sort(l2.begin(), l2.end());

    size_t sum = 0;
    for (size_t k = 0; k < l1.size(); k++) {
        sum += std::abs(l1[k] - l2[k]);
    }
    printf("%ld\n", sum);

}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<int> l1;
    std::vector<int> l2;
    std::unordered_map<int,int> ls;
    while (getline(file, line)) {
        std::vector<std::string> sLine;
        boost::split(sLine, line, boost::is_any_of(" "));
        const int a = std::atoi(sLine.front().c_str());
        const int b = std::atoi(sLine.back().c_str());
        l1.push_back(a);
        l2.push_back(b);
        if (!isInside(ls, a)) {
            ls[a] = 0;
        }
    }
    file.close();

    for (auto value : l2) {
        if (!isInside(ls, value)) continue;
        ls[value]++;
    }

    int sum = 0;
    for (auto key : l1) {
        sum += key*ls[key];
    }
    printf("%d\n", sum);
}

int main(int narg, char *args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
