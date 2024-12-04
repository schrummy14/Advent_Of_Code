
#include "../helpers/extras.hh"
#include <array>

int hasXmas(int k1, int k2, std::array<int,2>& d, std::vector<std::string>& data)
{
    const int N = data.size();
    const int M = data[0].length();

    const std::string WORD = "XMAS";
    for (size_t k = 0; k < WORD.length(); k++) {
        const int kk1 = k1 + k*d[0];
        const int kk2 = k2 + k*d[1];
        if (! (0 <= kk1 && kk1 < N && 0 <= kk2 && kk2 < M)) {
            return 0;
        }
        if (data[kk1][kk2] != WORD[k]) {
            return 0;
        }
    }
    return 1;
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> data;
    while (getline(file, line)) {
        stripString(line);
        data.push_back(line);
    }
    file.close();

    // Generate Direction
    std::vector<std::array<int,2>> dd;
    for (int k1 = -1; k1 < 2; k1++) {
        for (int k2 = -1; k2 < 2; k2++) {
            if (k1 == 0 && k2 == 0) {
                continue;
            }
            dd.push_back(std::array<int,2>{k1,k2});
        }
    }

    const int N = data.size();
    const int M = data[0].length();
    int numXmas = 0;
    for (int k1 = 0; k1 < N; k1++)
        for (int k2 = 0; k2 < M; k2++)
            for (auto d : dd)
                numXmas += hasXmas(k1,k2,d,data);
    printf("%d\n", numXmas);
}

int hasXmas(const int k1, const int k2, const std::vector<std::string>& data)
{
    if (data[k1][k2] != 'A') return 0;

    // No need to check bounds as the parent guarantees correctness
    const bool check1 = (data[k1-1][k2-1] == 'M' && data[k1+1][k2+1] == 'S') ||
                        (data[k1-1][k2-1] == 'S' && data[k1+1][k2+1] == 'M');

    const bool check2 = (data[k1+1][k2-1] == 'M' && data[k1-1][k2+1] == 'S') ||
                        (data[k1+1][k2-1] == 'S' && data[k1-1][k2+1] == 'M');

    if (check1 && check2) return 1;
    return 0;
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> data;
    while (getline(file, line)) {
        stripString(line);
        data.push_back(line);
    }
    file.close();

    const int N = data.size();
    const int M = data[0].length();
    int numXmas = 0;
    for (int k1 = 1; k1 < N-1; k1++)
        for (int k2 = 1; k2 < M-1; k2++)
            numXmas += hasXmas(k1,k2,data);
    printf("%d\n", numXmas);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
