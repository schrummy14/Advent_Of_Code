
#include "../../helpers/extras.hh"
#include <cmath>

size_t maxNum(const std::string line, size_t numDigits)
{
    size_t *maxV = new size_t[numDigits]{0};
    size_t max_k1 = 0;
    for (size_t k = 0; k < numDigits; k++) {
        for (size_t k1 = max_k1; k1 < line.length()-(numDigits-k-1); k1++) {
            const size_t cv = line[k1]-'0';
            if (cv > maxV[k]) {
                maxV[k] = cv;
                max_k1 = k1+1;
            }
        }
    }

    size_t curAns = 0;
    for (size_t k = 0; k < numDigits; k++) {
        curAns += maxV[k]*std::pow(10,numDigits-1-k);
    }
    delete[] maxV;
    return curAns;
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t ans = 0;
    while (getline(file, line)) {
        stripString(line);
        if (line.length()==0) continue;
        ans += maxNum(line, 2);
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
        ans += maxNum(line, 12);
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
