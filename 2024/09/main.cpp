
#include "../helpers/extras.hh"

void printVal(std::vector<int>& val)
{
    if (val.size() > 45) return;
    for (auto v : val) {
        printf("%c", v+'0');
    }
    printf("\n");
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<int> BLOCK;
    std::vector<int> SPACE;
    getline(file, line);
    file.close();
    stripString(line);
    for (size_t k = 0; k < line.length(); k++) {
        const char val = line[k]-'0';
        if (k % 2 == 0) {
            BLOCK.push_back(val);
        } else {
            SPACE.push_back(val);
        }
    }
    // Start building the new list
    std::vector<int> val;
    for (int k = 0; k < BLOCK[0]; k++) {
        val.push_back(0);
    }

    for (size_t k = 0; k < SPACE.size(); k++) {
        for (int k1 = 0; k1 < SPACE[k]; k1++) {
            val.push_back(-1);
        }
        for (int k1 = 0; k1 < BLOCK[k+1]; k1++) {
            val.push_back(k+1);
        }
    }

    // Now we can sort
    size_t p1 = 0;
    size_t p2 = val.size()-1;
    printVal(val);
    while (true) {
        // Find the next None item
        while (val[p1] >= 0) p1 += 1;
        while (val[p2] < 0) p2 -= 1;

        if (!(p1 < p2)) break;

        // Swap the values
        val[p1] = val[p2];
        val[p2] = -1;
        printVal(val);
    }

    long ans = 0;
    for (size_t k = 0; k < val.size(); k++) {
        ans += val[k] < 0 ? 0 : k*val[k];
    }
    printf("%ld\n",ans);
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<int> BLOCK;
    std::vector<int> SPACE;
    getline(file, line);
    file.close();
    stripString(line);
    for (size_t k = 0; k < line.length(); k++) {
        const char val = line[k]-'0';
        if (k % 2 == 0) {
            BLOCK.push_back(val);
        } else {
            SPACE.push_back(val);
        }
    }
    // Start building the new list
    std::vector<int> val;
    for (int k = 0; k < BLOCK[0]; k++) {
        val.push_back(0);
    }

    for (size_t k = 0; k < SPACE.size(); k++) {
        for (int k1 = 0; k1 < SPACE[k]; k1++) {
            val.push_back(-1);
        }
        for (int k1 = 0; k1 < BLOCK[k+1]; k1++) {
            val.push_back(k+1);
        }
    }
    printVal(val);

    // Now we can sort
    // Need to move whole files, if they can
    // If not, skip it...
    size_t p1=0;
    size_t p2=val.size()-1;
    size_t p1Org = 0;
    while (true) {
        p1=p1Org;
        while (val[p1] >= 0) p1 += 1;
        p1Org = p1; // Cuts the time in half...
        while (val[p2] < 0) p2 -= 1;
        if (!(p1 < p2)) break;

        // Get the file size of the next file
        size_t fileSize = 0;
        while (val[p2] == val[p2-fileSize]) fileSize += 1;

        // Now need to go through p1 and see if we can find space for this file
        bool foundSpace = false;
        while (true) {
            size_t freeSpace = 0;
            while (val[p1+freeSpace] == -1) freeSpace += 1;
            if (freeSpace >= fileSize) {
                foundSpace = true;
                break;
            } else {
                p1 += 1;
            }

            if (p1 > p2) break;
        }

        if (!foundSpace) {
            p2 -= fileSize;
            continue;
        }

        for (size_t k = 0; k < fileSize; k++) {
            val[p1+k] = val[p2-k];
            val[p2-k] = -1;
        }
        printVal(val);
    }
    long ans = 0;
    for (size_t k = 0; k < val.size(); k++) {
        if (val[k] < 0) continue;
        ans += k*val[k];
    }
    printf("%ld\n",ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
