
#include "../helpers/extras.hh"

#include <unordered_map>

inline long mix(long a, long b)
{
    return a^b;
}

inline long prune(long x)
{
    return x % 16777216;
}

void doPart1(std::vector<long>& numbers)
{
    long ans = 0;
    for (long number : numbers) {
        size_t k = 0;
        while (k++ < 2000) {
            number = prune(mix(number, 64*number));
            number = prune(mix(number, number/32));
            number = prune(mix(number, number*2048));
        }
        ans += number;
    }
    printf("%ld\n", ans);
}

std::unordered_map<int, long> getSequences(std::vector<signed char>& prices, std::vector<signed char>& dp)
{
    std::unordered_map<int, long> sequences;
    for (size_t k = 0; k < dp.size()-3; k++) {
        const signed char c1 = dp[k];
        const signed char c2 = dp[k+1];
        const signed char c3 = dp[k+2];
        const signed char c4 = dp[k+3];
        size_t c = 0;
        c ^= c1;
        c ^= c2<<8;
        c ^= c3<<16;
        c ^= c4<<24;
        if (sequences.find(c) == sequences.end()) sequences[c] = prices[k+4];
    }
    return sequences;
}

void doPart2(std::vector<long>& numbers)
{
    std::unordered_map<int, long> ANS;
    for (long number : numbers) {
        size_t k = 0;
        std::vector<signed char> prices;
        prices.push_back(number%10);
        while (k++ < 2000) {
            number = prune(mix(number, 64*number));
            number = prune(mix(number, number/32));
            number = prune(mix(number, number*2048));
            prices.push_back(number%10);
        }
        std::vector<signed char> dp;
        for (size_t k = 1; k < prices.size(); k++) dp.push_back(prices[k]-prices[k-1]);
        std::unordered_map<int, long> sequences = getSequences(prices, dp);
        for (auto seq : sequences) {
            size_t key = seq.first;
            long v = seq.second;
            if (ANS.find(key) == ANS.end()) {
                ANS[key] = v;
            } else {
                ANS[key] += v;
            }
        }
    }
    long ans = 0;
    for (auto entry : ANS) {
        if (ans < entry.second) ans = entry.second;
    }
    printf("%ld\n", ans);
}

int main(int narg, char* args[])
{
    std::string filename = "example.dat";
    if (narg > 1) filename = std::string(args[1]);

    std::vector<long> numbers;
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        stripString(line);
        if (line.length() == 0) continue;
        numbers.push_back(std::atol(line.c_str()));
    }
    file.close();

    doPart1(numbers);
    doPart2(numbers);
    return 0;
}
