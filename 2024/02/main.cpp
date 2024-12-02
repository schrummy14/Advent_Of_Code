
#include "../helpers/extras.hh"

int checkSafe(std::vector<std::string>& sLine)
{
    int lastNum = -1;
    bool isIncreasing = 0;
    bool isDecreasing = 0;
    int a;
    int b;
    for (std::string c : sLine) {
        const int num = atoi(c.c_str());
        if (lastNum < 0) {
            lastNum = num;
            continue;
        }
        if (num - lastNum > 0)
            isIncreasing = 1;
        else if (num - lastNum < 0)
            isDecreasing = 1;
        else
            return 0;

        if (isIncreasing > 0 && isDecreasing > 0) {
            return 0;
        }
        if (isIncreasing) {
            a = lastNum;
            b = num;
        } else {
            b = lastNum;
            a = num;
        }
        lastNum = num;
        if (b - a > 3 || b == a) {
            return 0;
        }
    }
    return 1;
}

int isSafeFun(std::vector<std::string>& sLine)
{
    int isSafe = checkSafe(sLine);
    if (isSafe == 1) return 1;

    for (size_t k = 0; k < sLine.size(); k++) {
        std::vector<std::string> nLine;
        for (size_t k1 = 0; k1 < k; k1++) {
            nLine.push_back(sLine[k1]);
        }
        for (size_t k1 = k+1; k1 < sLine.size(); k1++) {
            nLine.push_back(sLine[k1]);
        }
        isSafe = checkSafe(nLine);
        if (isSafe == 1) return 1;
    }
    return 0;
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    int sum = 0;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        // printf("%s\n", line.c_str());
        std::vector<std::string> sLine = splitString(line, " ");
        int isSafe = checkSafe(sLine);
        sum += isSafe;
    }
    file.close();
    printf("%d\n", sum);
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    int sum = 0;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        std::vector<std::string> sLine = splitString(line, " ");
        sum += isSafeFun(sLine);
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
