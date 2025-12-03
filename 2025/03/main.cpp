
#include "../../helpers/extras.hh"
#include <cmath>

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t ans = 0;
    while (getline(file, line)) {
        stripString(line);
        if (line.length()==0) continue;
        // std::cout << line << '\n';
        size_t k1 = 0;
        size_t max_k1 = 0;
        size_t k2 = line.length()-1;
        // size_t max_k2 = 0;
        size_t maxV[2] = {0};

        // Find max in first n-1 digits
        for (k1 = 0; k1 < line.length()-1; k1++) {
            const size_t cv = line[k1]-'0';
            if (cv > maxV[0]) {
                maxV[0] = cv;
                max_k1 = k1;
            }
        }

        // find the max in last max_k1 to n digits
        for (k2 = max_k1+1; k2 < line.length(); k2++) {
            const size_t cv = line[k2]-'0';
            if (cv > maxV[1]) {
                maxV[1] = cv;
                // max_k2 = k2;
            }
        }

        ans += 10*maxV[0] + maxV[1];
        // printf("%zu%zu %zu\n", maxV[0], maxV[1], ans);
    }
    file.close();
    printf("%zu\n", ans);
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t ans = 0;
    while (getline(file, line)) {
        stripString(line);
        if (line.length()==0) continue;
        std::cout << line << '\n';
        size_t maxV[12] = {0};
        size_t max_k1 = 0;
        for (size_t k = 0; k < 12; k++) {
            for (size_t k1 = max_k1; k1 < line.length()-(12-k-1); k1++) {
                const size_t cv = line[k1]-'0';
                if (cv > maxV[k]) {
                    maxV[k] = cv;
                    max_k1 = k1+1;
                }
            }
        }

        size_t curAns = 0;
        for (size_t k = 0; k < 12; k++) {
            curAns += maxV[k]*std::pow(10,11-k);
            printf("%zu", maxV[k]);
        }
        printf(" %zu\n", curAns);
        ans += curAns;
    }
    file.close();
    printf("%zu\n", ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
