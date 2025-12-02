
#include "../../helpers/extras.hh"

int getNum(const std::string line)
{
    std::string num = line.substr(1, line.length());
    return atoi(num.c_str());
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    int dial = 50;
    int count = 0;
    while (getline(file, line)) {
        stripString(line);
        const int num = getNum(line);
        if (line[0] == 'L') {
            dial = modulo((dial - num), 100);
        } else {
            dial = modulo((dial + num), 100);
        }
        if (dial == 0) count++;
    }
    file.close();
    std::cout << count << '\n';
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    int dial = 50;
    int count = 0;
    while (getline(file, line)) {
        stripString(line);
        const int num = getNum(line);
        for (int k = 0; k < num; k++) {
            if (line[0] == 'L') {
                dial = modulo((dial - 1), 100);
            } else {
                dial = modulo((dial + 1), 100);
            }
            if (dial == 0) count++;
        }
    }
    file.close();
    std::cout << count << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
