
#include "../helpers/extras.hh"
#include <array>
#include <regex>

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    int sum = 0;
    while (getline(file, line)) {
        stripString(line);
        std::smatch match;
        std::smatch vals;
        std::regex r("mul\\(\\d+,\\d+\\)");
        std::regex nums("\\d+");
        while (regex_search(line, match, r)) {
            std::string valMatch = match.str(0);
            std::array<int,2> ab;
            int k = 0;
            while (regex_search(valMatch, vals, nums)) {
                std::string a = vals.str(0);
                ab[k++] = std::atoi(a.c_str());
                valMatch = vals.suffix().str();
            }
            sum += ab[0]*ab[1];
            line = match.suffix().str();
        }

    }
    file.close();
    printf("%d\n", sum);
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    int sum = 0;
    bool doMul = true;
    while (getline(file, line)) {
        stripString(line);
        std::smatch match;
        std::smatch vals;
        std::regex r("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");
        std::regex nums("\\d+");
        while (regex_search(line, match, r)) {
            std::string valMatch = match.str(0);
            if (valMatch == "do()") doMul = true;
            else if (valMatch == "don't()") doMul = false;
            else {
                if (doMul) {
                    std::array<int,2> ab;
                    int k = 0;
                    while (regex_search(valMatch, vals, nums)) {
                        std::string a = vals.str(0);
                        ab[k++] = std::atoi(a.c_str());
                        valMatch = vals.suffix().str();
                    }
                    sum += ab[0]*ab[1];
                }
            }
            line = match.suffix().str();
        }

    }
    file.close();
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
