
#include "../../helpers/extras.hh"

bool idIsValid(const std::string id)
{
    // All odd length ids are valid
    if (id.length() % 2 == 1) return true;

    // Split the id into two parts and check if they match each other
    const std::string s1 = id.substr(0, id.length()/2);
    const std::string s2 = id.substr(id.length()/2, id.length());
    return s1 != s2;
}

size_t countInvalidIdsInRange(const std::string id_1, const std::string id_2)
{
    size_t count = 0;
    for (auto k = atol(id_1.c_str()); k <= atol(id_2.c_str()); k++) {
        if (!idIsValid(std::to_string(k))) count += k;
    }
    return count;
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t ans = 0;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, ",");
        for (auto val : sLine) {
            std::vector<std::string> ids = splitString(val, "-");
            ans += countInvalidIdsInRange(ids[0], ids[1]);
        }
    }
    std::cout << ans << '\n';
    file.close();
}

bool idIsValidForK(const std::string id, size_t k)
{
    if (id.length() % k > 0) return true;

    const int numCopies = id.length() / k;
    // printf("id = %s, numCopies = %d\n", id.c_str(), numCopies);
    const std::string s1 = id.substr(0, k);
    bool isValid = false;
    for (int m = 1; m < numCopies; m++) {
        const std::string s2 = id.substr(k*m, k);
        // std::cout << s1 << ", " << s2 << '\n';
        if (s1 != s2) isValid |= true;
    }
    return isValid;
}

bool idIsValid_2(const std::string id)
{
    // Need to loop through all possible sub string lengths
    for (size_t k = 1; k <= id.length()/2; k++) {
        if (!idIsValidForK(id, k)) return false;
    }
    return true;
}

size_t countInvalidIdsInRange_2(const std::string id_1, const std::string id_2)
{
    size_t count = 0;
    for (auto k = atol(id_1.c_str()); k <= atol(id_2.c_str()); k++) {
        if (!idIsValid_2(std::to_string(k))) {
            // printf("Found Invalid: %zu\n", k);
            count += k;
        }
    }
    return count;
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t ans = 0;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, ",");
        for (auto val : sLine) {
            std::vector<std::string> ids = splitString(val, "-");
            ans += countInvalidIdsInRange_2(ids[0], ids[1]);
        }
    }
    std::cout << ans << '\n';
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
