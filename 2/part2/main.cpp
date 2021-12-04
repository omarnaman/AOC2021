#include <iostream>
#include <string>

#define print(x) cout << #x << ": " << x << endl;
using namespace std;

int main() {
#ifdef TEST
    freopen("../test_input.in", "r", stdin);
#elif REAL
    freopen("../real_input.in", "r", stdin);
#endif
    string command;
    int command_value;
    int pos = 0, depth = 0, aim = 0;
    while (cin >> command >> command_value) {
        switch (command[0]) {
            case 'f':
                depth += command_value;
                pos += aim * command_value;
                break;
            case 'd':
                aim += command_value;
                break;
            case 'u':
                aim -= command_value;
                break;

            default:
                break;
        }
    }
#ifdef DEBUG
    print(depth);
    print(pos);
#endif
    cout << 1L * depth * pos << endl;
}