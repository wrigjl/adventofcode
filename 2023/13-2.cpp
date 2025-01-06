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

uint32_t checkReflect(const vector<uint32_t>& bits, size_t skip) {
    if (bits.size() == 1)
        return 0;
    for (auto i = 1; i < bits.size(); i++) {
        if (i == skip)
            continue;

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

uint32_t permuteBits(vector<uint32_t> bits, const size_t width, const uint32_t oldTarget) {
    const size_t skip = oldTarget == 0 ? string::npos : oldTarget;

    for (size_t i = 0; i < bits.size(); ++i) {
        for (size_t j = 0; j < width; ++j) {
            bits[i] ^= 1 << j;
            uint32_t r = checkReflect(bits, skip);
            if (r > 0)
                return r;
            bits[i] ^= 1 << j;
        }
    }
    return 0;
}

uint32_t permuteReflect(const vector<uint32_t>& rowBits, size_t rowWidth,
    const vector<uint32_t>& colBits, size_t colWidth) {
    std::pair<uint32_t, uint32_t> reflect = {
        checkReflect(rowBits, string::npos),
        checkReflect(colBits, string::npos)};

    if (reflect.first == 0 && reflect.second == 0)
        throw std::runtime_error("no initial reflection found");

    uint32_t r = permuteBits(rowBits, rowWidth, reflect.first);
    if (r != 0)
        return 100 * r;
    return permuteBits(colBits, colWidth, reflect.second);
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
        sum += permuteReflect(rowBits, rowWidth, colBits, colWidth);
        rowBits.clear();
        colBits.clear();
    }
    std::cout << sum << std::endl;
}