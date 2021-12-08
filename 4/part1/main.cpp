#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#ifdef DEBUG
#include <cassert>
#define print(x) cout << #x << ": " << x << endl;
template <typename T>
void print_vector(vector<T> array) {
    for (size_t i = 0; i < array.size(); i++) {
        print(array[i]);
    }
}
#endif

class Board {
   public:
    int numbers[5][5];
    bool visited[5][5];

    Board() {
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                numbers[i][j] = -1;
                visited[i][j] = 0;
            }
        }
    }
    pair<int, int> check_number(int num) {
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                if (numbers[i][j] == num) {
                    visited[i][j] = true;
                    return make_pair<int, int>(i, j);
                }
            }
        }
        return make_pair<int, int>(-1, -1);
    }

    int bingo(int row, int col) {
        for (size_t i = 0; i < 5; i++) {
            if (!visited[i][col]) {
                break;
            }
            if (i == 4) {
                return calculate_score();
            }
        }
        for (size_t i = 0; i < 5; i++) {
            if (!visited[row][i]) {
                break;
            }
            if (i == 4) {
                return calculate_score();
            }
        }
        return -1;
    }

    int calculate_score() {
        int sum = 0;
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                if (!visited[i][j]) {
                    sum += numbers[i][j];
                }
            }
        }
        return sum;
    }
};

vector<int> parse_generated(string s) {
    size_t next_comma = s.find(',');
    size_t cur = 0;
    vector<int> res;
    int num;
    while (next_comma != string::npos) {
        num = atoi(s.substr(cur, next_comma - cur).c_str());
        res.push_back(num);
        cur = next_comma + 1;
        next_comma = s.find(',', cur);
    }
    num = atoi(s.substr(cur).c_str());
    res.push_back(num);
    return res;
}

int main() {
#ifdef TEST
    freopen("../test_input.in", "r", stdin);
#elif REAL
    freopen("../real_input.in", "r", stdin);
#endif
    string generated;
    cin >> generated;
    vector<int> input = parse_generated(generated);
    vector<Board> boards;
    while (!cin.eof()) {
        Board board;
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                cin >> board.numbers[i][j];
            }
        }
        boards.push_back(board);
#ifdef DEBUG

        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                for (size_t y = 0; y < 5; y++) {
                    for (size_t z = 0; z < 5; z++) {
                        if (i == y && z == j) continue;
                        if (board.numbers[i][j] == board.numbers[y][z]) {
                            cout << board.numbers[i][j] << " " << board.numbers[z][j];
                        }
                        assert(board.numbers[i][j] != board.numbers[y][z]);
                    }
                }
            }
        }
#endif
    }

    for (size_t i = 0; i < input.size(); i++) {
        int& num = input[i];
        for (size_t j = 0; j < boards.size(); j++) {
            Board& board = boards[j];
            pair<int, int> coord = board.check_number(num);
            if (coord.first != -1) {
                int bingo = board.bingo(coord.first, coord.second);
                if (bingo != -1) {
#ifdef DEBUG
                    cout << num << endl;
#endif
                    cout << bingo * num << endl;
                    exit(0);
                }
            }
        }
    }

}