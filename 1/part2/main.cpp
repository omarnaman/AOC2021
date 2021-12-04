#include <iostream>
#include <queue>

using namespace std;

int main()
{
#ifdef TEST
    freopen("test_input.in", "r", stdin);
#elif REAL
    freopen("real_input.in", "r", stdin);
#endif
    int depth, res = 0;
    deque<int> depths(3, 0);
    for (size_t i = 0; i < 3; i++)
    {
        cin >> depths[i];
    }

    while (cin >> depth)
    {
        depths.push_back(depth);
        if (depths.front() < depths.back())
        {
            res++;
        }
        depths.pop_front();
    }
    cout << res << endl;
}