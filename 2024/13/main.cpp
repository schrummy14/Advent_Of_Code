
#include "../helpers/extras.hh"

#include <array>
#include <cmath>

std::array<double,2> matSolve(
    const std::array<double,4>& A,
    const std::array<double,2>& b
)
{
    const double det = 1./(A[0]*A[3] - A[1]*A[2]);
    const double ia =  det*A[3];
    const double ib = -det*A[1];
    const double ic = -det*A[2];
    const double id =  det*A[0];
    const double x1 = ia*b[0] + ib*b[1];
    const double x2 = ic*b[0] + id*b[1];
    return std::array<double,2>{x1,x2};
}

std::array<double,2> readSolve(std::string solveLine)
{
    std::vector<std::string> vals = splitString(splitString(solveLine, ":")[1], ",");
    double x = std::atof(vals[0].substr(3,vals[0].length()).c_str());
    double y = std::atof(vals[1].substr(3,vals[1].length()).c_str());
    return std::array<double,2>{x,y};
}

std::array<double,2> readButton(std::string buttonLine)
{
    std::vector<std::string> vals = splitString(splitString(buttonLine, ":")[1], ",");
    double x = std::atof(vals[0].substr(2,vals[0].length()).c_str());
    double y = std::atof(vals[1].substr(2,vals[1].length()).c_str());
    return std::array<double,2>{x,y};
}

unsigned long solveMachine(std::vector<std::string>& machine, bool isPart2)
{
    std::array<double,2> b1 = readButton(machine[0]);
    std::array<double,2> b2 = readButton(machine[1]);
    std::array<double,2> solve = readSolve(machine[2]);

    std::array<double,4> A{b1[0],b2[0],b1[1],b2[1]};
    std::array<double,2> b{isPart2*pow(10,13)+solve[0], isPart2*pow(10,13)+solve[1]};
    std::array<double,2> x = matSolve(A,b);
    x[0] = round(1000*x[0])/1000;
    x[1] = round(1000*x[1])/1000;

    unsigned long minCost;
    if (fmod(x[0], 1) == 0 && fmod(x[1], 1) == 0) minCost = 3*x[0]+x[1];
    else minCost = 0;

    return minCost;
}

void doPart1(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> machine;
    unsigned long ans = 0;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;

        machine.push_back(line);
        if (machine.size() == 3) {
            ans += solveMachine(machine, false);
            machine.clear();
        }
    }
    file.close();
    printf("%ld\n", ans);
}

void doPart2(const char* filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> machine;
    unsigned long ans = 0;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;

        machine.push_back(line);
        if (machine.size() == 3) {
            ans += solveMachine(machine, true);
            machine.clear();
        }
    }
    file.close();
    printf("%ld\n", ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
