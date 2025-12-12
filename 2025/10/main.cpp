
#include "../../helpers/extras.hh"

size_t getMinButtons(std::string& GOAL, std::vector<std::string>& BUTTONS)
{
    int goal = 0;
    for (size_t k = 0; k < GOAL.length()-2; k++) {
        if (GOAL[k+1] == '.') continue;
        goal += 1 << k;
    }
    std::vector<int> buttons;
    for (auto& BUTTON : BUTTONS) {
        int bv = 0;
        for (auto& v : splitString(BUTTON.substr(1, BUTTON.length()-2), ",")) {
            bv += 1 << (atoi(v.c_str()));
        }
        buttons.push_back(bv);
    }
    int minPresses = __INT_MAX__;
    const int runMax = 1<<(buttons.size());
    // Try every combination of button presses
    for (int run = 1; run < runMax; run++) {
        int runVal = 0;
        int runPresses = 0;
        // Convert run into binary and presses the 1s
        for (size_t k = 0; k < buttons.size(); k++){
            if (((run>>k)%2) == 1) {
                runVal ^= buttons[k];
                runPresses += 1;
            }
        }
        // check if our button presses gave us the right answer
        if (runVal == goal) {
            // update answer if needed
            minPresses = std::min(minPresses, runPresses);
        }
    }

    return minPresses;
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    size_t ans = 0;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, " ");
        std::string GOAL = sLine[0];
        std::vector<std::string> BUTTONS;
        for (size_t k = 1; k < sLine.size()-1; k++) BUTTONS.push_back(sLine[k]);

        ans += getMinButtons(GOAL, BUTTONS);
    }
    file.close();
    std::cout << "Part 1: " << ans << '\n';
}

void doPart2(const char* filename)
{
    (void) filename;
    std::cout << "Part 2: (Run main.py as I am not implementing an integer linear program algorithm in c++)" << '\n';
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
