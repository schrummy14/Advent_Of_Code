
#include "../../helpers/extras.hh"

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, " ");
    }
    file.close();
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
