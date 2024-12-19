
#include "../helpers/extras.hh"

#include <unordered_map>

bool startsWith(std::string& str1, std::string& str2)
{
    if (str1.length() < str2.length()) return false;
    for (size_t k = 0; k < str2.length(); k++) {
        if (str1[k] != str2[k]) return false;
    }
    return true;
}

std::unordered_map<std::string, size_t> towelArrangeMEM;
size_t towelArrange(std::vector<std::string>& towels, std::string& arrangement)
{
    if (towelArrangeMEM.find(arrangement) != towelArrangeMEM.end()) {
        return towelArrangeMEM[arrangement];
    }
    size_t ans = 0;
    if (arrangement.length() == 0) {
        ans = 1;
    }

    for (std::string towel : towels) {
        if (startsWith(arrangement, towel)) {
            std::string newArrangement = arrangement.substr(towel.length(), arrangement.length());
            ans += towelArrange(towels, newArrangement);
        }
    }
    towelArrangeMEM[arrangement] = ans;
    return ans;
}

void doPart1(std::vector<std::string>& arrangements, std::vector<std::string>& towels)
{
    size_t ans = 0;
    for (std::string arrangement : arrangements) {
        if (0 < towelArrange(towels, arrangement))
            ans++;
    }
    printf("%ld\n", ans);
}

void doPart2(std::vector<std::string>& arrangements, std::vector<std::string>& towels)
{
    size_t ans = 0;
    for (std::string arrangement : arrangements) {
        ans += towelArrange(towels, arrangement);
    }
    printf("%ld\n", ans);
}

int main(int narg, char* args[])
{
    std::string filename = "input.dat";
    if (narg > 1) filename = std::string(args[1]);

    std::ifstream file(filename);
    std::string line;

    // first line is towels
    getline(file,line);
    stripString(line);
    std::vector<std::string> towels = splitString(line, ", ");

    // Next line is skipped
    getline(file,line);

    // lext lines are all arrangements
    std::vector<std::string> arrangements;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        arrangements.push_back(line);
    }
    file.close();

    doPart1(arrangements, towels);
    doPart2(arrangements, towels);
    return 0;
}
