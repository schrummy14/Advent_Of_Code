
#include "../helpers/extras.hh"
#include <string>

bool isValid(const size_t target, std::vector<size_t>& vals)
{
    if (vals.size() == 1) return target == vals[0];

    std::vector<size_t>v1{vals[0]+vals[1]};
    std::copy(vals.begin()+2,vals.end(),std::back_inserter(v1));
    if (isValid(target, v1)) return true;
    std::vector<size_t>v2{vals[0]*vals[1]};
    std::copy(vals.begin()+2,vals.end(),std::back_inserter(v2));
    if (isValid(target, v2)) return true;
    return false;
}

void doPart1(const char* filename) // 20665830408335
{
    std::ifstream file(filename);
    std::string line;
    size_t sum = 0;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, ":");
        const size_t target = std::atoll(sLine[0].c_str());
        std::vector<size_t> vals;
        stripString(sLine[1]);
        for (auto val : splitString(sLine[1]," ")) {
            vals.push_back(std::atoll(val.c_str()));
        }
        if (isValid(target, vals)) sum+= target;
    }
    file.close();
    printf("%ld\n", sum);
}

bool isValid2(const long target, std::vector<long>& vals)
{
    if (vals.size() == 1)
        return target == vals[0];

    std::vector<long>v1;
    v1.push_back(vals[0]+vals[1]);
    for (size_t k = 2; k < vals.size(); k++) {
        v1.push_back(vals[k]);
    }
    if (isValid2(target, v1))
        return true;


    std::vector<long>v2;
    v2.push_back(vals[0]*vals[1]);
    for (size_t k = 2; k < vals.size(); k++) {
        v2.push_back(vals[k]);
    }
    if (isValid2(target, v2))
        return true;

    std::vector<long>v3;
    v3.push_back(
        std::atol(
            (
                std::to_string(vals[0]) +
                std::to_string(vals[1])
            ).c_str()
        )
    );
    for (size_t k = 2; k < vals.size(); k++) {
        v3.push_back(vals[k]);
    }
    if (isValid2(target, v3)) return true;
        return false;
}

void doPart2(const char* filename) // 354060705047464
{
    std::ifstream file(filename);
    std::string line;
    long sum = 0;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, ":");
        const long target = std::atoll(sLine[0].c_str());
        std::vector<long> vals;
        stripString(sLine[1]);
        for (auto val : splitString(sLine[1]," ")) {
            vals.push_back(std::atoll(val.c_str()));
        }
        if (isValid2(target, vals)) {
            sum += target;
        }
    }
    file.close();
    printf("%ld\n", sum);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
