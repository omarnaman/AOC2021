#include <iostream>
#include <vector>

using namespace std;

int main() {
#ifdef TEST
    freopen("../test_input.in", "r", stdin);
#elif REAL
    freopen("../real_input.in", "r", stdin);
#endif
    int prev_depth = -1, cur_depth = -1;
    cin >> prev_depth;
    int res = 0;
    while (cin >> cur_depth) {
        if (cur_depth > prev_depth) {
            res++;
        }
        prev_depth = cur_depth;
    }
    cout << res << endl;
}