#include <iostream>
#include <string>
#include <vector>
#include <set>

using std::string;
using std::vector;
using std::cout, std::endl, std::cin, std::set;

struct Position {
    size_t row, col;
    bool operator<(const Position &other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
    bool operator==(const Position &other) const = default;
};

size_t checkExpansion(const set<size_t>& exset, const size_t p1, const size_t p2, size_t mult) {
    if (p1 == p2)
        return 0;

    auto l = std::min(p1, p2);
    auto r = std::max(p1, p2);

    auto diff = r - l;
    size_t galaxies = 0;
    for (auto const &p: exset) {
        if (p > l && p < r)
            galaxies++;
    }

    size_t nongalaxies = diff - galaxies - 1;
    return (galaxies + 1) + (mult * nongalaxies);
}

void readMaze(vector<Position>& pos, set<size_t>& galrows, set<size_t>& galcols) {
    string line;

    size_t row = 0;
    while (std::getline(cin, line)) {
        if (line.empty())
            break;

        for (size_t col = 0; col < line.size(); col++)
            if (line[col] == '#') {
                pos.emplace_back(row, col);
                galcols.emplace(col);
                galrows.emplace(row);
            }

        row++;
    }
}

int main() {
    vector<Position> galaxies;
    set<size_t> galaxyRows;
    set<size_t> galaxyCols;

    readMaze(galaxies, galaxyRows, galaxyCols);

    size_t part1sum = 0;
    size_t part2sum = 0;
    for (auto g1 = galaxies.cbegin(); g1 != galaxies.cend(); ++g1) {
        for (auto g2 = g1 + 1; g2 != galaxies.cend(); ++g2) {
            part1sum += checkExpansion(galaxyRows, g1->row, g2->row, 2) +
                checkExpansion(galaxyCols, g1->col, g2->col, 2);
            part2sum += checkExpansion(galaxyRows, g1->row, g2->row, 1000000) +
                checkExpansion(galaxyCols, g1->col, g2->col, 1000000);
        }
    }

    cout << "part1: " << part1sum << endl;
    cout << "part2: " << part2sum << endl;
}