#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#ifdef DEBUG
#include <cli_colors.h>
#define print(x) cout << #x << ": " << x << endl
template <typename T>
void print_vector(vector<T> array) {
    for (size_t i = 0; i < array.size(); i++) {
        print(array[i]);
    }
}
#endif

int bin_string_to_int(const string& binary) {
    int mult = 1;
    int res = 0;
    for (size_t i = 0; i < binary.size(); i++) {
        res += (binary[i] == '1') * mult;
        mult = (mult << 1);
    }
    return res;
}

int solve(set<size_t> remaining, vector<int> numbers, size_t binary_size, bool (*condition)(const int& zeros, const int& ones)) {
    int ones, zeros;
    int res = 0;
    bool condition_value;

    for (size_t i = 0; i < binary_size; i++) {
        if (remaining.size() == 1) {
            return *(remaining.begin());
        }
        ones = zeros = 0;

        for (set<size_t>::iterator iter = remaining.begin(); iter != remaining.end(); iter++) {
            ones += (numbers[*iter] & 1);
            zeros += ((numbers[*iter] & 1) ^ 1);
        }
        condition_value = condition(zeros, ones);

        for (set<size_t>::iterator iter = remaining.begin(); iter != remaining.end();) {
            if (numbers[*iter] & 1 ^ condition_value) {
                set<size_t>::iterator temp_iter = iter;
                iter++;
                remaining.erase(temp_iter);
            } else {
                numbers[*iter] = (numbers[*iter] >> 1);
                iter++;
            }
        }
    }
    return *(remaining.begin());
}

inline int reverse_int(int number, size_t size) {
    int res = 0;
    int mul = (1 << (size - 1));
    for (size_t i = 0; i < size; i++) {
        res += (number & 1) * mul;
        mul = (mul >> 1);
        number = (number >> 1);
    }
    return res;
}

int main() {
#ifdef TEST
    freopen("../test_input.in", "r", stdin);
#elif REAL
    freopen("../real_input.in", "r", stdin);
#endif
    vector<int> numbers;
    string binary;
    while (cin >> binary) {
        numbers.push_back(bin_string_to_int(binary));
    }
#ifdef DEBUG
    print_vector(numbers);
#endif
    int oxygen = 0, co2 = 0;
    int ones, zeros;
    short most_common, least_common;
    set<size_t> remaining_oxy, remaining_co2;
    for (size_t i = 0; i < numbers.size(); i++) {
        remaining_oxy.insert(i);
        remaining_co2.insert(i);
    }
    oxygen = solve(remaining_oxy, numbers, binary.size(), 
            [](const int& zeros, const int& ones) -> bool { return ones >= zeros; });
    oxygen = reverse_int(numbers[oxygen], binary.size());

    co2 = solve(remaining_co2, numbers, binary.size(), 
            [](const int& zeros, const int& ones) -> bool { return ones < zeros; });
    co2 = reverse_int(numbers[co2], binary.size());
#ifdef DEBUG
    print(oxygen);
    print(co2);
#endif
    cout << 1L * oxygen * co2 << endl;
}