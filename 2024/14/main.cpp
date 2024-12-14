
#include "../helpers/extras.hh"
#include <array>
void doPart1(const char* filename)
{
    const long R = 103;
    const long C = 101;
    std::ifstream file(filename);
    std::string line;
    long q1 = 0;
    long q2 = 0;
    long q3 = 0;
    long q4 = 0;
    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, " ");
        std::vector<std::string> pos = splitString(sLine[0].substr(2,sLine[0].length()),",");
        std::vector<std::string> vel = splitString(sLine[1].substr(2,sLine[1].length()),",");

        long p[2] = {
            std::atol(pos[0].c_str()),
            std::atol(pos[1].c_str())
        };

        long v[2] = {
            std::atol(vel[0].c_str()),
            std::atol(vel[1].c_str())
        };

        v[0] = (v[0] + C)%C;
        v[1] = (v[1] + R)%R;

        p[0] = (p[0] + (100*v[0])) % C;
        p[1] = (p[1] + (100*v[1])) % R;

        // printf("[%ld, %ld]\n", p[0], p[1]);

        bool inQ1 = p[1] < R/2 && p[0] < C/2;
        bool inQ2 = R/2+1 <= p[1] && p[0] < C/2;
        bool inQ3 = p[1] < R/2 && C/2+1 <= p[0];
        bool inQ4 = R/2+1 <= p[1] && C/2+1 <= p[0];

        if (inQ1)
            q1 += 1;
        else if (inQ2)
            q2 += 1;
        else if (inQ3)
            q3 += 1;
        else if (inQ4)
            q4 += 1;
    }
    file.close();
    printf("%ld %ld %ld %ld %ld\n", q1, q2, q3, q4, q1*q2*q3*q4);
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;

    const long R = 103;
    const long C = 101;

    std::vector<std::array<long,2>> POS;
    std::vector<std::array<long,2>> VEL;

    while (getline(file, line)) {
        stripString(line);
        std::vector<std::string> sLine = splitString(line, " ");
        std::vector<std::string> pos = splitString(sLine[0].substr(2,sLine[0].length()),",");
        std::vector<std::string> vel = splitString(sLine[1].substr(2,sLine[1].length()),",");

        POS.push_back(
            std::array<long,2> {
                std::atol(pos[0].c_str()),
                std::atol(pos[1].c_str())
            }
        );

        VEL.push_back(
            std::array<long,2> {
                (std::atol(vel[0].c_str())+C)%C,
                (std::atol(vel[1].c_str())+R)%R
            }
        );
    }

    long count = 0;
    std::vector<bool> SEEN(R*C,false);
    while (true) {
        std::fill(SEEN.begin(), SEEN.end(), false);
        size_t numSEEN = 0;
        for (size_t k = 0; k < POS.size(); k++) {
            POS[k][0] = (POS[k][0] + VEL[k][0]) % C;
            POS[k][1] = (POS[k][1] + VEL[k][1]) % R;
            size_t hash = POS[k][0]*R + POS[k][1];
            if (SEEN[hash]) continue;
            numSEEN++;
            SEEN[hash] = true;
        }
        count++;
        if (numSEEN == POS.size()) break;
    }
    for (long y = 0; y < R; y++) {
        std::string cStr = "";
        for (long x = 0; x < C; x++) {
            if (SEEN[x*R+y])
                cStr += "*";
            else
                cStr += " ";
        }
        printf("%s\n", cStr.c_str());
    }
    printf("%ld\n",count);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
