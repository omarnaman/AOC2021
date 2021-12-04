#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifdef DEBUG
#define print(x) cout << #x << ": " << x << endl;
template <typename T>
void print_vector(vector<T> array) {
    for (size_t i = 0; i < array.size(); i++) {
        print(array[i]);
    }
}
#endif

int bin_string_to_int(const string &binary) {
    int mult = 1;
    int res = 0;
    for (int i = binary.size() - 1; i >= 0; i--) {
        res += (binary[i] == '1') * mult;
        mult = (mult << 1);
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
    int gamma = 0, epsilon = 0;
    int ones, zeros;
    for (size_t i = 0; i < binary.size(); i++) {
        ones = zeros = 0;
        for (size_t j = 0; j < numbers.size(); j++) {
            ones += (numbers[j] & 1);
            zeros += ((numbers[j] & 1) ^ 1);
            numbers[j] = (numbers[j] >> 1);
        }
        gamma = (gamma | ((ones > zeros) << i));
        epsilon = (epsilon | ((ones < zeros) << i));
    }

#ifdef DEBUG
    print(gamma);
    print(epsilon);
#endif
    cout << 1L * gamma * epsilon << endl;
}