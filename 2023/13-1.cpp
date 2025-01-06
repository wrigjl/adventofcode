#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <deque>

using std::string;
using std::vector;
using std::cout, std::endl, std::cin, std::set, std::deque, std::unordered_set;

struct Position {
    size_t row, col;
    bool operator<(const Position &other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
    bool operator==(const Position &other) const = default;
};

template<>
struct std::hash<Position>
{
    std::size_t operator()(const Position& s) const noexcept {
        return (s.row << 16) | s.col;
    }
};

enum Direction {
    North = '^',
    South = 'v',
    West = '<',
    East = '>',
};

struct PosDir {
    Position pos;
    Direction dir;
    bool operator==(const PosDir &other) const = default;
};

template<>
struct std::hash<PosDir>
{
    std::size_t operator()(const PosDir& s) const noexcept {
        return (std::hash<Position>{}(s.pos) << 8) | static_cast<int>(s.dir);
    }
};

bool readMaze(vector<uint32_t>& rowBits, vector<uint32_t>& colBits, size_t& rowWidth, size_t& colWidth) {
    vector<string> maze;
    string line;

    while (std::getline(cin, line)) {
        if (line.empty())
            break;
        maze.push_back(line);
    }

    if (maze.empty())
        return false;

    rowWidth = maze[0].size();
    colWidth = maze.size();
    for (auto row = 0; row < maze.size(); ++row) {
        uint32_t rowBit = 0;
        for (auto col = 0; col < maze[row].size(); ++col) {
            if (row == 0)
                colBits.push_back(0);
            if (maze[row][col] == '#') {
                rowBit |= 1 << col;
                colBits[col] |= 1 << row;
            }
        }
        rowBits.push_back(rowBit);
    }
    return true;
}

uint32_t checkReflect(const vector<uint32_t>& bits) {
    if (bits.size() == 1)
        return 0;
    for (auto i = 1; i < bits.size(); i++) {
        if (bits[i-1] == bits[i]) {
            // potential reflection, try it.
            bool isReflect = true;
            for (auto off = 0; ; off++) {
                if (i - 1 - off >= bits.size() || i + off >= bits.size())
                    break;
                if (bits[i - 1 - off] != bits[i + off]) {
                    isReflect = false;
                    break;
                }
            }
            if (isReflect)
                return i;
        }
    }
    return 0;
}

void printBits(const vector<uint32_t>& bits) {
    for (auto const& b: bits) {
        cout << std::bitset<16>(b) << endl;
    }
}

int main() {
    vector<string> maze;
    vector<uint32_t> rowBits;
    size_t rowWidth;
    vector<uint32_t> colBits;
    size_t colWidth;

    u_long sum = 0;
    while (readMaze(rowBits, colBits, rowWidth, colWidth)) {
        sum += 100 * checkReflect(rowBits);
        sum += 1 * checkReflect(colBits);
        rowBits.clear();
        colBits.clear();
    }
    std::cout << sum << std::endl;
}