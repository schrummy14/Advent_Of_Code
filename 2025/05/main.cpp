
#include "../../helpers/extras.hh"

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

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, " ");
    }
    file.close();
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
