
#include "../helpers/extras.hh"

#include <cmath>

void getData(const char* filename, size_t* A, size_t* B, size_t* C, std::vector<char>& program)
{
    std::ifstream file(filename);
    std::string line;

    // Register A
    getline(file, line);
    *A = std::atol(splitString(line, ":")[1].c_str());

    // Register B
    getline(file, line);
    *B = std::atol(splitString(line, ":")[1].c_str());

    // Register C
    getline(file, line);
    *C = std::atol(splitString(line, ":")[1].c_str());

    // Skip the next line
    getline(file, line);

    // Program
    getline(file, line);
    std::vector<std::string> programStr = splitString(splitString(line, ":")[1],",");

    for (auto op:programStr)
        program.push_back(std::atoi(op.c_str()));
    file.close();
}

size_t combo_operand(char value, size_t A, size_t B, size_t C)
{
    switch (value) {
        case 0:
        case 1:
        case 2:
        case 3:
            return value;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
    }
    return 0;
}

std::vector<char> run(size_t A, size_t B, size_t C, std::vector<char>& program)
{
    size_t pointer = 0;

    std::vector<char> outputs;

    while (pointer < program.size()) {
        char opcode = program[pointer];
        char operand = program[pointer+1];

        switch (opcode) {
            case 0:
                A/=std::pow(2, combo_operand(operand, A, B, C));
                break;
            case 1:
                B ^= operand;
                break;
            case 2:
                B = combo_operand(operand, A, B, C) % 8;
                break;
            case 3:
                if (A != 0) {
                    pointer = operand;
                    continue;
                }
                break;
            case 4:
                B ^= C;
                break;
            case 5:
                outputs.push_back(combo_operand(operand, A, B, C) % 8);
                break;
            case 6:
                B = A / std::pow(2, combo_operand(operand, A, B, C));
                break;
            case 7:
                C = A / std::pow(2, combo_operand(operand, A, B, C));
                break;
        }
        pointer += 2;
    }
    return outputs;
}

void doPart1(const char* filename)
{
    size_t A,B,C;
    std::vector<char> program;
    getData(filename, &A, &B, &C, program);

    std::vector<char> output = run(A, B, C, program);
    printf("%s\n", joinString(output, ',').c_str());
}

void doPart2(const char* filename)
{
    size_t A,B,C;
    std::vector<char> program;
    if (std::string(filename) == "example.dat") {
        A = 2024;
        B = 0;
        C = 0;

        program.push_back(0);
        program.push_back(3);
        program.push_back(5);
        program.push_back(4);
        program.push_back(3);
        program.push_back(0);

    } else {
        getData(filename, &A, &B, &C, program);
    }

    // Get initial A
    A = std::pow(8,(program.size()-1));

    size_t numUpdates = 0;
    while (true) {
        std::vector<char> output = run(A, B, C, program);

        // May be the same, now check values
        bool isSame = true;
        for (size_t k = 0; k < program.size(); k++) {
            isSame &= (output[k] == program[k]);
        }

        if (isSame) {
            #ifdef DEBUG
                printf("%4ld: %16ld -> %s\n", numUpdates, A, joinString(output,',').c_str());
            #else
                printf("%ld\n",A);
            #endif
            break;
        }

        size_t add = 0;
        for (size_t k = 0; k < program.size(); k++) {
            const char o = output[output.size()-1-k];
            const char p = program[program.size()-1-k];
            if (o != p) {
                add = std::pow(8, program.size()-1-k);
                #ifdef DEBUG
                    printf(
                        "%4ld: %16ld -> %s :: adding %ld(8**%ld)\n",
                        numUpdates, A, joinString(output,',').c_str(), add, program.size()-1-k
                    );
                #endif
                numUpdates++;
                A += add;
                break;
            }
        }
    }
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);
    doPart1(filename.c_str());
    doPart2(filename.c_str());
    return 0;
}
