
#include "../helpers/extras.hh"

typedef struct QueueVal{
    size_t score;
    std::array<char,2> pad;
    std::string move;
    std::string out;

    bool operator < (const QueueVal& rhs) const
    {
        return score > rhs.score;
    }
} QueueVal;

std::vector<std::string> PAD1 = {"789", "456", "123", " 0A"};
std::vector<std::string> PAD2 = {" ^A", "<v>"};

int getPad(std::array<char,2> pad, std::vector<std::string>& PAD)
{
    char r = pad[0];
    char c = pad[1];
    const char R = PAD.size();
    const char C = PAD[0].size();
    if (!(0 <= r && r < R && 0 <= c && c < C)) return -1;
    if (PAD[r][c] == ' ') return -1;
    return PAD[r][c];
}

size_t dirPad2Int(const char val)
{
    switch (val)
    {
    case 'A':
        return 0;
    case '^':
        return 1;
    case '>':
        return 2;
    case 'v':
        return 3;
    case '<':
        return 4;
    default:
        exit(1);
        return 0;
    }
}

std::array<int,3> applyPad(std::array<char,2> pad, const char move, std::vector<std::string>& PAD1)
{
    std::array<int,3> ans{-1,-1,-1};
    switch (move) {
    case 'A':
        ans[0] = pad[0];
        ans[1] = pad[1];
        ans[2] = getPad(pad, PAD1);
        break;
    case '^':
        ans[0] = pad[0]-1;
        ans[1] = pad[1];
        break;
    case '>':
        ans[0] = pad[0];
        ans[1] = pad[1]+1;
        break;
    case 'v':
        ans[0] = pad[0]+1;
        ans[1] = pad[1];
        break;
    case '<':
        ans[0] = pad[0];
        ans[1] = pad[1]-1;
        break;
    }
    return ans;
}

std::vector<size_t>COST_MEM(5*5*25,0);
size_t cost(std::string cur, std::string last, size_t numPads)
{
    if (numPads==0) return 1;

    size_t key = dirPad2Int(cur[0]) + 5*dirPad2Int(last[0]) + 5*5*(numPads-1);
    if (COST_MEM[key] > 0) {
        return COST_MEM[key];
    }

    std::array<char,2> pad{0,0};
    switch (last[0]) {
    case 'A':
        pad[0] = 0;
        pad[1] = 2;
        break;
    case '^':
        pad[0] = 0;
        pad[1] = 1;
        break;
    case '>':
        pad[0] = 1;
        pad[1] = 2;
        break;
    case 'v':
        pad[0] = 1;
        pad[1] = 1;
        break;
    case '<':
        pad[0] = 1;
        pad[1] = 0;
        break;
    }

    QueueVal startingVal = QueueVal();
    startingVal.score = 0;
    startingVal.pad[0] = pad[0];
    startingVal.pad[1] = pad[1];
    startingVal.move = "A";
    startingVal.out = "";

    std::priority_queue<QueueVal> Q;
    Q.push(startingVal);

    std::vector<bool> SEEN(PAD2.size()*PAD2[0].size()*5,false);
    while (!Q.empty()) {
        const QueueVal curVal = Q.top(); Q.pop();
        if (getPad(curVal.pad, PAD2) < 0) continue;
        if (curVal.out == cur) {
            COST_MEM[key] = curVal.score;
            return curVal.score;
        }
        if (curVal.out.length() > 0) continue;

        size_t seenKey = curVal.pad[0] + PAD2.size()*curVal.pad[1] + PAD2.size()*PAD2[0].length()*dirPad2Int(curVal.move[0]);
        if (SEEN[seenKey]) continue;
        SEEN[seenKey] = true;

        for (std::string move : {"^", "<", "v", ">", "A"}) {
            std::array<int,3> applyPadAns = applyPad(curVal.pad, move[0], PAD2);
            size_t costMove = cost(move, curVal.move, numPads-1);
            std::string newOut = curVal.out;
            if (applyPadAns[2] > 0) {
                newOut += applyPadAns[2];
            }
            QueueVal newVal = QueueVal();
            newVal.score = curVal.score + costMove;
            newVal.pad[0] = applyPadAns[0];
            newVal.pad[1] = applyPadAns[1];
            newVal.move = move;
            newVal.out = newOut;
            Q.push(newVal);
        }
    }

    return 0;
}

size_t solve(const std::string& code, size_t numPads)
{
    size_t codeInt = std::atol(code.substr(0, code.length()-1).c_str());

    QueueVal startingVal = QueueVal();
    startingVal.score = 0;
    startingVal.pad[0] = 3;
    startingVal.pad[1] = 2;
    startingVal.move = "A";
    startingVal.out = "";

    std::priority_queue<QueueVal> Q;
    Q.push(startingVal);

    // SEEN size is PAD1.size()*PAD1[0].size()*4*4
    std::vector<bool> SEEN(PAD1.size()*PAD1[0].size()*4*5,false);

    while (!Q.empty()) {
        const QueueVal curVal = Q.top(); Q.pop();
        if (curVal.out == code) {
            return curVal.score*codeInt;
        }
        if (!startsWith(code, curVal.out)) continue;
        if (getPad(curVal.pad, PAD1) < 0) continue;
        size_t key = curVal.out.length() + 4*dirPad2Int(curVal.move[0]) + 4*5*curVal.pad[1] + 4*5*PAD1[0].length()*curVal.pad[0];
        if (SEEN[key]) continue;
        SEEN[key] = true;
        for (std::string move : {"^", "<", "v", ">", "A"}) {
            std::string newOut = curVal.out;
            std::array<int,3> applyPadAns = applyPad(curVal.pad, move[0], PAD1);
            if (applyPadAns[2] > 0) {
                newOut += applyPadAns[2];
            }
            size_t costMove = cost(move, curVal.move, numPads);

            QueueVal newVal = QueueVal();
            newVal.score = curVal.score + costMove;
            newVal.pad[0] = applyPadAns[0];
            newVal.pad[1] = applyPadAns[1];
            newVal.move = move;
            newVal.out = newOut;
            Q.push(newVal);
        }
    }
    return 0;
}

void doPart1(std::vector<std::string>& codes)
{
    size_t ans = 0;
    for (std::string code : codes) {
        ans += solve(code, 2);
    }
    printf("%ld\n", ans);
}

void doPart2(std::vector<std::string>& codes)
{
    size_t ans = 0;
    for (std::string code : codes) {
        ans += solve(code, 25);
    }
    printf("%ld\n", ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);

    std::string code;
    std::ifstream file(filename);
    std::vector<std::string> codes;
    while (getline(file, code)) {
        stripString(code);
        codes.push_back(code);
    }
    file.close();

    doPart1(codes);
    doPart2(codes);
    return 0;
}
