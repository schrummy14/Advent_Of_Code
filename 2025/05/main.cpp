
#include "../../helpers/extras.hh"
#include <bits/stdc++.h>

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> ranges;
    std::vector<std::string> ingredients;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) break;
        ranges.push_back(line);
    }
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) break;
        ingredients.push_back(line);
    }
    file.close();
    std::cout << ranges.size() << ", " << ingredients.size() << '\n';

    size_t ans = 0;
    for (auto ingredient:ingredients) {
        size_t val = atol(ingredient.c_str());
        for (auto range : ranges) {
            std::vector<std::string> vs = splitString(range, "-");
            size_t v1 = atol(vs[0].c_str());
            size_t v2 = atol(vs[1].c_str());
            if (v1 <= val && val <= v2) {
                ans++;
                break;
            }
        }
    }
    std::cout << "Part 1: " << ans << '\n';
}

// Comparator function
bool rangeComp(std::array<size_t, 2> a, std::array<size_t, 2> b) {
    return a[0] < b[0];
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> strRanges;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) break;
        strRanges.push_back(line);
    }
    file.close();

    // convert ranges into a 2d vector
    std::vector<std::array<size_t, 2>> ranges;
    for (auto range : strRanges) {
        std::vector<std::string> vs = splitString(range, "-");
        const size_t v1 = atol(vs[0].c_str());
        const size_t v2 = atol(vs[1].c_str());
        ranges.push_back({v1,v2});
    }

    // Sort ranges by the first entry
    sort(ranges.begin(), ranges.end(), rangeComp);

    size_t ans = 0;
    size_t cur = 0; // Keep track of the right hand side location
    for (std::array<size_t, 2> range : ranges) {
        // Next number starts in the middle of the current range
        if (cur >= range[0]) {
            range[0] = cur + 1;
        }

        // Make sure the end now extends from the previous range
        // If it does, add it to the interval
        if (range[0] <= range[1]) {
            ans += range[1]-range[0]+1;
        }

        // Current right hand side is either what it was, or the new range[1] value
        cur = cur > range[1] ? cur:range[1];
    }
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
